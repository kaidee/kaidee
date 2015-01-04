# -*- coding: cp936 -*-
import websocket
import exceptions
import traceback
import os
import sys
import time
import random
import threading
import struct
import socket
import hashlib
import base64
import EasyDialogs

import lychee.base_pb2 as base
import lychee.equips_pb2 as equips
import lychee.item_pb2 as item
import lychee.login_pb2 as login
import lychee.map_pb2 as realm
import lychee.message_pb2 as message
import lychee.msgid_pb2 as msgid
import lychee.role_pb2 as role
import lychee.social_pb2 as social
import lychee.task_pb2 as quest

#reload(sys) # 动态加载sys模块
#sys.setdefaultencoding('utf-8')

def ustr(u):
    #s = u.encode('utf-8')
    s = u.encode('GB18030')
    return s

def server_log(text):
    def func(inner):
        print '[server log]', text
        return inner
    return func

def encrypt(pw, count, salt, ckey, skey):
    # haskell实现的服务器加密算法有问题
    # 它会总是重新创建新的hash对象进行计算
    for i in range(count):
        h = hashlib.sha1()
        h.update(pw+salt+ckey+skey)
        pw = h.digest()
    return pw

def packMsg(id, msg):
    data = struct.pack('!II', id, len(msg))
    data += msg
    return data

def unpackMsg(data):
    s = struct.calcsize('!II')
    id, size = struct.unpack('!II', data[:s])
    msg = data[s:]
    return (id, size, msg)

def randomChineseName():  
    str = ''
    for i in range(3):
        head = random.randint(0xB0, 0xDF)  
        body = random.randint(0xA, 0xF)  
        tail = random.randint(0, 0xF)
        val = ( head << 0x8 ) | (body << 0x4 ) | tail  
        str += "%x" % val  
    return str.decode('hex').decode('GB18030') 

text = {
    login.LoginServerAuthFailed.UserNameNotExist:'用户名不存在',
    login.LoginServerAuthFailed.UserAlreadyOnline:'用户已经在线', # NOTE 服务器还没有实现
    login.LoginServerAuthFailed.WrongPassword:'密码错误',
    login.LoginServerAuthFailed.UnsupportedVersion:'版本错误',
    login.LoginServerAuthFailed.InternalServerError:'服务器内部错误'
}


def register_account(addr, username, password, imei):
    ws = websocket.create_connection(addr)
    req = login.RegisterUserReq()
    req.username = username
    req.password = password
    req.imei = imei
    data = packMsg(msgid.MSG_REGISTER_USER, req.SerializePartialToString())
    ws.send_binary(data)
    id, size, msg = unpackMsg(ws.recv())
    assert id == msgid.MSG_REGISTER_USER
    res = login.RegisterUserRes()
    res.ParseFromString(msg)
    return res
    
def login_game(addr, username, password):
    ws = websocket.create_connection(addr)
    print "Connection to Prelude Server"
    msg = login.LoginClientFirstMessage()
    msg.username = username
    msg.clientNonce = clientNonce
    msg.version = loginServerVersion
    data = packMsg(msgid.MSG_LOGIN_CLIENT_FIRST_MESSAGE, msg.SerializeToString())
    ws.send_binary(data)
    id, size, msg = unpackMsg(ws.recv())
    if id == msgid.MSG_LOGIN_SERVER_FIRST_MESSAGE:
        print 'received login server first message'
        srvfirst = login.LoginServerFirstMessage()
        srvfirst.ParseFromString(msg)
        #assert serverNonce == clientNonce
        msg = login.LoginClientFinalMessage()
        msg.username = username
        msg.password = encrypt(password, srvfirst.iterationCount,
                                srvfirst.salt, clientNonce, srvfirst.serverNonce)
        msg.serverNonce = srvfirst.serverNonce
        msg.gateway = 1
        data = packMsg(msgid.MSG_LOGIN_CLIENT_FINAL_MESSAGE, msg.SerializeToString())
        ws.send_binary(data)
        id, size, msg = unpackMsg(ws.recv())    
        if id == msgid.MSG_LOGIN_SERVER_FINAL_MESSAGE:
            print 'received login server final message'
            srvfinal = login.LoginServerFinalMessage()
            srvfinal.ParseFromString(msg)
            ws.close()
            return (srvfinal.userId, srvfinal.sessionId, srvfinal.serverList)
        elif id == msgid.MSG_LOGIN_SERVER_AUTH_FAILED:
            print text[failed.cause]
        else:
            print '未知的服务器消息'
    elif id == msgid.MSG_LOGIN_SERVER_AUTH_FAILED:
        print '授权失败'
        failed = login.LoginServerAuthFailed()
        failed.ParseFromString(msg)
        print text[failed.cause]
        if failed.cause == login.LoginServerAuthFailed.UserNameNotExist:
            ws.close()
            res = register_account(addr, username, password, imei)
            if res.status == login.RegisterUserRes.SUCCESS:
                print '注册账号成功'
                ws.close()
                return login_game(addr, username, password)
            elif res.status == login.RegisterUserRes.ILLEGAL_NAME:
                print '注册账号失败：无效的用名'
            elif res.status == login.RegisterUserRes.ILLEGAL_PASSWORD:
                print '注册账号失败：无效的密码'
            else:
                print '注册账号失败：未知的错误'  
    else:
        print '未知的服务器消息'
    ws.close()

def on_auth_failed():
    print '授权失败'
    failed = login.LoginServerAuthFailed()
    failed.ParseFromString(msg)
    print text[failed.cause]
    if failed.cause == login.LoginServerAuthFailed.UserNameNotExist:
        res = register_account(addr, username, password, imei)
        if res.status == login.RegisterUserRes.SUCCESS:
            print '注册账号成功'
            ws.close()
            return login_game(addr, username, password)
        elif res.status == login.RegisterUserRes.ILLEGAL_NAME:
            print '注册账号失败：无效的用名'
        elif res.status == login.RegisterUserRes.ILLEGAL_PASSWORD:
            print '注册账号失败：无效的密码'
    else:
        print '注册账号失败：未知的错误'   

class MapState:
    def __init__(self, roles, npcs, mobs, teleport):
        self.roles = roles
        self.npcs = npcs
        self.mobs = mobs
        self.teleport = teleport

    def render(self):
        for k in self.teleport:
            if k.isHidden:
                print '隐藏的传送点 %s 位置(%s, %s), 传送目标 %s'%(k.id, k.x, k.y, k.t)
            else:
                print '可见的传送点 %s 位置(%s, %s), 传送目标 %s'%(k.id, k.x, k.y, k.t)
                
        for r in self.roles:
            print '玩家 %s(%s) 进入地图, 位置(%s, %s),'%(ustr(r.dp.dp_name), r.id, r.x, r.y), '挂饰等级%s'%(r.dp.dp_dc)
                
        for k in self.npcs:
            print 'NPC %s(%s) 进入地图, 位置(%s, %s),'%(ustr(k.dp.dp_name), k.id, k.x, k.y), '挂饰等级%s'%(k.dp.dp_dc)

        for k in self.mobs:
            print 'Mob %s(%s) 进入地图, 位置(%s, %s),'%(ustr(k.dp.dp_name), k.group_id, k.x, k.y), '挂饰等级%s'%(k.dp.dp_dc)
            
class GameServer:
    def __init__(self):
        self._me = None # 当前游戏角色
        self._ws = None # websocket连接
        self.mapState = None

    def recv(self):
        """接收消息 返回值是(消息id, 消息体大小, 消息体)"""
        return unpackMsg(self._ws.recv())

    def send(self, ident, message):
        """发送二进制消息 message是消息id data是消息体"""
        data = packMsg(ident, message.SerializeToString())
        self._ws.send_binary(data)

    def disconnect(self):
        if self._ws is not None:
            self._ws.close()
            self._ws = None

    def connect(self, url, userId, sessionId):
        print "连接到游戏服务器", url
        self._ws = websocket.create_connection(url)
        req = role.CheckRoleReq()
        req.user_id = userId
        req.cookie = sessionId
        self.send(msgid.MSG_CHECK_ROLE, req)
        print '选择角色'
        id, size, msg = self.recv()
        roleres = role.CheckRoleRes()
        roleres.ParseFromString(msg)
        if roleres.res == role.CheckRoleRes.Okay:
            self.enter_game(roleres.role_id)
        elif roleres.res == role.CheckRoleRes.CreateRole:
            print '没有创建角色'
            newrole = self.create_role(userId, randomChineseName(), base.Female) #女角法伤高
            if newrole.res == role.CreateRoleRes.Okay:
                print '创建角色成功'
                self.enter_game(newrole.roleId)
            else:
                # TODO 重名后重新生成角色名字
                print '创建角色失败：重名或者超过最大角色数量'  
        elif roleres.res == role.CheckRoleRes.AuthFailed:
            print '校验失败'
        elif roleres.res == role.CheckRoleRes.Maintenance:
            print '服务器维护'
        else:
            print '未知错误：进入游戏失败'
        self._ws.close()

    def create_role(self, userId, name, gender):
        req = role.CreateRoleReq()
        req.userId = userId
        req.name = name
        req.gender = gender
        data = packMsg(msgid.MSG_CREATE_ROLE, req.SerializeToString())
        self._ws.send_binary(data)   
        id, size, msg = self.recv()
        assert id == msgid.MSG_CREATE_ROLE
        res = role.CreateRoleRes()
        res.ParseFromString(msg)
        return res
        
    def enter_game(self, roleId):
        print '角色', roleId, '进入游戏'
        req = role.EnterWorldReq()
        req.role_id = roleId
        data = packMsg(msgid.MSG_ENTER_WORLD, req.SerializePartialToString())
        self._ws.send_binary(data)
        id, size, msg = self.recv()
        assert id == msgid.MSG_ENTER_WORLD
        res = role.EnterWorldRes()
        res.ParseFromString(msg)
        self.update_role(res.init_role)
        self._me = res.init_role # 角色信息
        self.enter_realm()      

    def enter_realm(self):
        init_map_id = 0
        self.switch_realm(init_map_id)
        t = UserInput(self)
        t.start()
        self.message_loop()
        
    def switch_realm(self, mapId):
        print '尝试切换地图', mapId
        req = realm.EnterMapReq()
        req.mapid = mapId
        data = packMsg(msgid.MSG_ENTER_MAP, req.SerializePartialToString())
        self._ws.send_binary(data)

    def update_realm(self, mapattr):
        """地图状态更新"""
        self.mapState = MapState(mapattr.rolesAdd, mapattr.npcAdd, mapattr.monsterAdd, mapattr.entrances)
        self.mapState.render() # 显示地图状态

    def update_role(self, role):
        """人物状态更新"""
        for k in role.pets:
            print "宠物 %s"%ustr(k.dp.dp_name)
            
    def on_move(self, moves):
        """玩家移动"""
        for a in moves:
            print '玩家%s移动到(%s, %s)'%(a.role_id, a.x, a.y)

    def move(self, x, y):
        """移动角色"""
        req = realm.MoveReqO()
        req.role_id = self._me.role_id
        req.x = x
        req.y = y
        data = packMsg(msgid.MSG_MOVE_REQO, req.SerializePartialToString())
        self._ws.send_binary(data)

    def fight(self, gid):
        print '对怪物%s发起战斗' % gid
        req = realm.FightMonsterReq()
        req.group_id = gid
        data = packMsg(msgid.MSG_FIGHT_MONSTER, req.SerializePartialToString())
        self._ws.send_binary(data)
    
    def on_fight(self, fight, loot):
        print '战斗回放'
        
        for k in fight.members:
            print '%s 位置：%s 生命值：%s' % (ustr(k.dp.dp_name), k.pos, k.hp)
            
        for k in fight.actions:
            print '角色%s发起第%s回合' % (k.actionId, k.currentRound)
            if k.actionType == 1:
                if not k.plainResult.isMiss:
                    print '普通攻击: 目标%s 伤害%s' % (k.plainResult.targetId, k.plainResult.plainHurt.phDamage)
            elif k.actionType == 2:
                for h in k.spellResult.spellHurt:
                    if h.hpDelta > 0:
                        print '技能%s攻击: 目标%s HP减少%s' % (k.spellResult.spellId, h.targetId, h.hpDelta)
                
            elif k.actionType == 3:
                print '眩晕'
            else:
                print '其他攻击类型'
            
        if fight.win:
            print '战斗胜利'
        else:
            print '战斗失败'
            
    def message_loop(self):
        while True:
            # 提取新消息
            id, size, msg = self.recv()
           
            if id == msgid.MSG_MAP_UPDATE:
                #print '地图状态更新'
                res = realm.MapAttr()
                res.ParseFromString(msg)
                self.update_realm(res)
            elif id == msgid.MSG_ENTER_MAP:
                # 玩家进入地图
                res = realm.EnterMapRes()
                res.ParseFromString(msg)
                if res.isOK:
                    print '进入地图成功'
                    self.update_realm(res.mapAttr)
                else:
                    print '进入地图失败'
                    return
            elif id == msgid.MSG_MOVE_RESO:
                # 玩家移动广播
                res = realm.MoveResO()
                res.ParseFromString(msg)
                self.on_move(res.move)
            elif id == msgid.MSG_FIGHT_MONSTER:
                # 战斗响应
                res = realm.FightMonsterRes()
                res.ParseFromString(msg)
                if res.have_fight:
                    self.on_fight(res.fight_data, res.loot)
                else:
                    print '无法与怪物%s进行战斗' % res.group_id
            elif id == msgid.MSG_PET_UPDATE:
                res = role.RoleAttr()
                res.ParseFromString(msg)
                self.update_role(res)
            else:
                print '收到未处理的消息', id

class Actor:
    def __init__(self, controller):
        self._controller = controller
        
    def move(self, x, y):
        self._controller.move(x, y)
   
    def fight(self, gid):
        self._controller.fight(gid)

    def getPet(self):
        req = role.IWantPandaReq()
        req.dummy = 0
        data = packMsg(msgid.MSG_I_WANT_PANDA, req.SerializePartialToString())
        self._controller._ws.send_binary(data)
    
class UserInput(threading.Thread):
    def __init__(self, server):
        threading.Thread.__init__(self)
        self._server = server
        
    def run(self):
        actor = Actor(self._server)
        lastcmd = ''
        while True:
            lastcmd = EasyDialogs.AskString('命令', lastcmd)
            if lastcmd is None:
                lastcmd = '' 
            if len(lastcmd) > 0:
                try:
                    x = eval('actor.' + lastcmd, globals(), locals())
                except:
                    continue

def main():
    try:
        userId, sessionId, servers = login_game(loginServerAddress, username, password)
        game = GameServer()
        for s in servers:
            game.connect(s.addr, userId, sessionId)
            break # 默认选择第一个服务器
    except websocket.WebSocketConnectionClosedException, ex:
        print '服务器崩溃，请重新连接'

#loginServerAddress = 'ws://223.4.32.165:52000'
#loginServerAddress = 'ws://192.168.1.99:52000'
loginServerAddress = 'ws://192.168.1.204:52000'
#loginServerAddress = 'ws://192.168.1.187:52000'
#loginServerAddress = 'ws://192.168.1.201:52000'
#loginServerAddress = 'ws://192.168.1.201:2222'
loginServerVersion = '1.0'
username = 'yfbot'
password = '123456'
imei = 'imei123'
clientNonce = 'nonce123'

if __name__ == '__main__':
    main()
    print 'program exit'
