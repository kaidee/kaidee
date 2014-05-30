# -*- coding: utf-8 -*-

import os, sys
#import time
import csv
import json
from xlrd import open_workbook, cellname
#import exceptions
import wx
import wx.grid
import wx.lib.scrolledpanel as wxs
#from wx.lib.pubsub import setupkwargs  # new pubsub
#from wx.lib.pubsub import pub

# ！！Windows中文系统注意：.py源代码必须以ANSI格式保存，默认编码设置为cp936
# 虽然在eclipse pydev的工程配置中会自动进行这种设置，但是脱离eclipse后则必须在程序中进行设置
#reload(sys) # 动态加载sys模块
#sys.setdefaultencoding('cp936') 
#print "current default encodign:", sys.getdefaultencoding()

AppName = u'策划助手'

class MapInfo(dict):
    """副本地图信息"""
    pass
#     def __init__(self, description, taskID, taskType, rewards, mapID, startNPC, endNPC, targetType, targetNum, targetID, preTaskID, posX, posY, dialogIndex):
#         self['dungeonName'] = description
#         self['dungeonID'] = taskID
#         self['taskType'] = taskType
#         self['rewards'] = rewards
#         self['mapID'] = mapID
#         self['startNPC'] = startNPC
#         self['endNPC'] = endNPC
#         self['targetType'] = targetType
#         self['targetNum'] = targetNum
#         self['targetID'] = targetID
#         self['preTaskID'] = preTaskID
#         self['posX'] = posX
#         self['posY'] = posY
#         self['dialogIndex'] = dialogIndex
            
class MapGrid(wx.grid.Grid):
    columns = ['副本名', '副本ID', '小地图', '地图ID', '怪物名', '怪物ID', '经验', '职业', '技能', '技能ID', 
               '血量系数', '防御系数', '攻击系数', '掉落ID']
    
    def __init__(self, parent):
        wx.grid.Grid.__init__(self, parent, -1)

    def updateView(self, data):
        #print 'Sheet:', sheet.name
        #for sheet in data:
        sheet = data[0]
        print 'Sheet:', sheet.name
        self.CreateGrid(sheet.nrows, sheet.ncols)
        self.BeginBatch()
        for col in range(sheet.ncols):
            for row in range(sheet.nrows):
                #self.SetColLabelValue(col, cellname(row, col))
                self.SetCellValue(row, col, str(sheet.cell_value(row, col)))
        self.EndBatch() # 改变数据时时避免闪烁，也无需调用Grid.ForceRefresh
        
#         pos = 0
#         for i in MapGrid.columns: 
#             self.SetColLabelValue(pos, i)
#             pos += 1
#         self.SetRowLabelValue(4, "RF") 
#         self.SetCellValue(4, 0, "Keith") 
#         self.SetCellValue(4, 1, "Moreland") 
#         self.SetRowLabelValue(5, "3B") 
#         self.SetCellValue(5, 0, "Ron") 
#         self.SetCellValue(5, 1, "Cey") 
#         self.SetRowLabelValue(6, "C") 
#         self.SetCellValue(6, 0, "Jody") 
#         self.SetCellValue(6, 1, "Davis") 
#         self.SetRowLabelValue(7, "SS") 
#         self.SetCellValue(7, 0, "Larry") 
#         self.SetCellValue(7, 1, "Bowa") 
#         self.SetRowLabelValue(8, "P") 
#         self.SetCellValue(8, 0, "Rick") 
#         self.SetCellValue(8, 1, "Sutcliffe")

class Task(dict):
    """任务信息"""
    def __init__(self, description, taskID, taskType, rewards, mapID, startNPC, endNPC, targetType, targetNum, targetID, preTaskID, posX, posY, dialogIndex):
        self['description'] = description
        self['taskID'] = taskID
        self['taskType'] = taskType
        self['rewards'] = rewards
        self['mapID'] = mapID
        self['startNPC'] = startNPC
        self['endNPC'] = endNPC
        self['targetType'] = targetType
        self['targetNum'] = targetNum
        self['targetID'] = targetID
        self['preTaskID'] = preTaskID
        self['posX'] = posX
        self['posY'] = posY
        self['dialogIndex'] = dialogIndex
    
class TaskPanel(wxs.ScrolledPanel):

    def __init__(self, parent, controller):
        wxs.ScrolledPanel.__init__(self, parent, -1, style=wx.BORDER_SUNKEN)
        self.SetupScrolling() # 打开滚动条
        self._controller = controller
        self._pos = -1  # 当前显示的任务在配置文件(如json)中的位置
        self._ismodified = False # 数据是否被修改
        self._isediting = False  # 是否处于修改状态

        self.keys = ['taskID', 'description', 'taskType', 'rewards', 'mapID', 'startNPC', 'endNPC', 'targetType', 'targetNum', 'targetID', 'preTaskID', 'posX', 'posY', 'dialogIndex']
        strings = ["任务ID", "描述", "类型", "奖励", "地图ID", "起始NPC", "结束NPC", "目标类型", "目标数量", "目标ID", 
                   "前置任务ID", "X坐标", "Y坐标", "对话索引"]
        self.labels = []    # 标签控件
        self.inputs = []    # 输入控件
        
        # 分组
        group = wx.StaticBox(self, wx.ID_ANY, u"任务配置")
        box = wx.BoxSizer(wx.HORIZONTAL)
        staticBox = wx.StaticBoxSizer(group)
        boxBottom = wx.FlexGridSizer(0, 1)
        
        # 标签
        for i in range(len(strings)):
            self.labels.append(wx.StaticText(self, label=strings[i]+":"))
            self.labels[i].Wrap(-1)

        # 输入控件
        for i in range(len(self.keys)):
            if self.keys[i] == 'description':
                style = wx.TE_READONLY | wx.TE_MULTILINE
            else:
                style = wx.TE_READONLY
            ctrl = wx.TextCtrl(self, style=style)
            self.inputs.append(ctrl)
            self.Bind(wx.EVT_TEXT, self.OnTextChange, ctrl)
        
        # 布局
        fgSizer = wx.FlexGridSizer(0, 2, hgap=10, vgap=10)
       
        for i in range(len(self.labels)):
            fgSizer.Add(self.labels[i])
            fgSizer.Add(self.inputs[i])
        staticBox.Add(fgSizer, 0, wx.ALL, 10)
  
        # 修改按钮
        button = wx.Button(self, wx.ID_ANY, "修改")
        self.Bind(wx.EVT_BUTTON, self.OnEdit, button)
        self.Bind(wx.EVT_UPDATE_UI, self.OnCheckCanEdit, button)
        boxBottom.Add(button, 1, wx.ALL, 10)
        # 更新按钮
        button = wx.Button(self, wx.ID_ANY, u"更新")
        self.Bind(wx.EVT_BUTTON, self.OnUpdate, button)
        self.Bind(wx.EVT_UPDATE_UI, self.OnCheckCanUpdate, button)
        boxBottom.Add(button, 1, wx.ALL, 10)

        box.Add(staticBox, 1, wx.ALL, 10)
        box.Add(boxBottom, 1, wx.ALL, 10)
        self.SetSizer(box)

    def OnTextChange(self, event):
        if self._isediting:
            self._ismodified = True

    def OnEdit(self, event):
        for i in range(len(self.inputs)):
            if isinstance(self.inputs[i], wx.TextCtrl):
                self.inputs[i].SetEditable(True)
        self._isediting = True
        
    def OnUpdate(self, event):
        try:
            data = self.getData()
        except:
            print '数据读取异常'
            return
        # 禁用编辑框
        for i in range(len(self.inputs)):
            if isinstance(self.inputs[i], wx.TextCtrl):
                self.inputs[i].SetEditable(False)
        self._controller.OnUpdateTaskItem(data, self._pos)
        self._isediting = self._ismodified = False
    
    def OnCheckCanEdit(self, event):
        event.Enable(not self._isediting)
        
    def OnCheckCanUpdate(self, event):
        event.Enable(self._ismodified)
    
    def getData(self):
        """读取控件中的数据"""
        data = {}
        for i in range(len(self.keys)):
            if isinstance(self.inputs[i], wx.ComboBox):
                value = self.inputs[i].GetStringSelection()
            else:
                value = self.inputs[i].GetValue()
                
            if self.keys[i] == 'rewards':
                value = list(value)
            elif self.keys[i] == 'description':
                value = value
            else:
                value = int(value)
            data[self.keys[i]] = value
        return data
    
    def setData(self, data, pos):
        # 只有当选择不同的任务时候才设置数据
        if pos != self._pos:
            if self._ismodified:
                result = wx.MessageBox('数据已经改变，是否更新？', '更新', wx.YES_NO)
                if result == wx.YES:
                    self.OnUpdate(None)
            # 离开编辑和修改状态
            if self._isediting or self._ismodified:
                self._isediting = self._ismodified = False
                for i in range(len(self.inputs)):
                    if isinstance(self.inputs[i], wx.TextCtrl):
                        self.inputs[i].SetEditable(False)
            # 设置新数据  
            self._pos = pos
            for i in range(len(self.keys)):
                value = str(data[pos][self.keys[i]])
                if isinstance(self.inputs[i], wx.ComboBox):
                    self.inputs[i].Clear()
                    self.inputs[i].Append(value)
                    self.inputs[i].SetSelection(0)
                if value == '[]':
                    self.inputs[i].SetValue('')
                else:
                    self.inputs[i].SetValue(value)
    
    def OnChildFocus(self, event):
        """覆盖这个函数以阻止将panel滚动到获得焦点的子窗口区域  """
        pass
    
class MyFrame(wx.Frame):
    newFileName = u'新的任务配置'     # 用于新建的文件名
    newFileCount = 0
    
    @staticmethod
    def GetNewFileName():
        """构造一个新的文件名，这个函数应该只在创建新文件的时候调用"""
        MyFrame.newFileCount += 1
        return MyFrame.newFileName + str(MyFrame.newFileCount)
        
    def __init__(self):
        wx.Frame.__init__(self, None, id = wx.ID_ANY, title = AppName, style = wx.DEFAULT_FRAME_STYLE|wx.TAB_TRAVERSAL)
        
        self.config = None          # 配置文档
        self.location = ''          # 文件路径 
        self._newfile = ''

        self.InitUI()
    
    def InitUI(self):
        self.MakeMenuBar()
        #self.MakeToolBar()
        self.MakeStatusBar()
        self.MakePanel()
        #self.ShowMapPanel(None) # only for test / debug

    def MakeMenuBar(self):
        fileMenu = wx.Menu()    # 文件菜单
        taskMenu = wx.Menu()    # 任务菜单 
        mapMenu = wx.Menu()     # 地图菜单
        helpMenu = wx.Menu()    # 帮助菜单
        
        item = fileMenu.Append(wx.ID_NEW, '新建(&N)\tCtrl+N')
        self.Bind(wx.EVT_MENU, self.OnNewFile, item)
        item = fileMenu.Append(wx.ID_OPEN, "打开(&O)...\tCtrl+O")
        self.Bind(wx.EVT_MENU, self.OnOpenFile, item)
        item = fileMenu.Append(wx.ID_SAVE, "保存(&S)\tCtrl+S")
        self.Bind(wx.EVT_MENU, self.OnSaveFile, item)
        self.Bind(wx.EVT_UPDATE_UI, self.OnCheckCanSave, item)
        item = fileMenu.Append(wx.ID_SAVEAS, "另存为(&A)...")
        self.Bind(wx.EVT_MENU, self.OnSaveAsFile, item)
        self.Bind(wx.EVT_UPDATE_UI, self.OnCheckCanSaveAs, item)
        fileMenu.AppendSeparator()
        item = fileMenu.Append(-1, "退出(&X)")
        self.Bind(wx.EVT_MENU, self.OnExit, item)
        self.Bind(wx.EVT_CLOSE, self.OnClose)

        item = taskMenu.Append(-1, '任务配置')
        self.Bind(wx.EVT_MENU, self.ShowTaskPanel, item)
        #item.Enable(False)
        
        item = mapMenu.Append(-1, '副本地图')
        self.Bind(wx.EVT_MENU, self.ShowMapPanel, item)

        item = helpMenu.Append(wx.ID_ABOUT, "关于 " + AppName + "(&A)")
        self.Bind(wx.EVT_MENU, self.OnAbout, item)
        
        # 设置菜单栏
        mbar = wx.MenuBar()
        mbar.Append(fileMenu, "文件(&F)")
        mbar.Append(taskMenu, '任务(&Q)')
        mbar.Append(mapMenu, "地图(&A)")
        mbar.Append(helpMenu, "帮助(&H)")
        self.SetMenuBar(mbar)
    
    def MakeToolBar(self):
        toolbar = self.CreateToolBar(style=wx.TB_HORZ_TEXT)
        toolbar.AddLabelTool(wx.ID_NEW, "新建", wx.ArtProvider.GetBitmap(wx.ART_NEW), shortHelp=u"新建配置")
        toolbar.AddLabelTool(wx.ID_OPEN, "打开", wx.ArtProvider.GetBitmap(wx.ART_FILE_OPEN), shortHelp=u"打开配置")
        toolbar.AddLabelTool(wx.ID_SAVE, "保存", wx.ArtProvider.GetBitmap(wx.ART_FILE_SAVE), shortHelp=u"保存配置")
        #saveastool = toolbar.AddLabelTool(wx.ID_SAVEAS, "另存为", wx.ArtProvider.GetBitmap(wx.ART_FILE_SAVE_AS), shortHelp=u"配置另存为")
        #closetool = toolbar.AddTool(wx.ID_ANY, u"关闭", wx.ArtProvider.GetBitmap(wx.ART_NEW))
        #newtool = toolbar.AddTool(wx.ID_ANY, u"新建", wx.ArtProvider.GetBitmap(wx.ART_NEW))
        toolbar.Realize()    # Windows平台必须调用这个方法

    def MakeStatusBar(self):
        self.sbar = self.CreateStatusBar(1, wx.ST_SIZEGRIP, wx.ID_ANY)
      
    # 初始化面板    
    def MakePanel(self):
        self._task_list_panel = ListPanel(self) # 左面板
        self._task_list_panel.Hide()
        self._task_panel = TaskPanel(self, self._task_list_panel)     # 右面板
        self._task_panel.Hide()

        # 表格面板
        self._grid = MapGrid(self)
        self._grid.Hide()
        
    def ChangeTitle(self, text, star=''):
        self.SetTitle(star + text + ' - ' + AppName)
     
    def OnConfigDataChanged(self):
        if self.location == '':
            self.ChangeTitle(self._newfile, '*')
        else:
            self.ChangeTitle(self.location, '*')
   
    def OnViewTask(self, pos):
        self._task_panel.setData(self.config.data, pos)
        self.ShowTaskEditPanel()

    def OnAddTaskItem(self, desc):
        task = Task(desc, self.config.Count(), 0, [], 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
        self.config.append(task)
        
    def OnDeleteTaskItem(self, items):
        for i in items:
            self.config.delete(i)

    def OnUpdateTaskItem(self, task, pos):
        self.config.update(task, pos)

    def ShowTaskPanel(self, event):
        self.MakeToolBar()
        box = wx.BoxSizer(wx.HORIZONTAL)
        box.AddMany([(self._task_list_panel, 0, wx.EXPAND), (self._task_panel, -1, wx.EXPAND)])
        self.SetSizer(box)
        self._task_list_panel.Show()
        self._task_list_panel.Enable(False)
        self.Layout()
    
    def ShowTaskEditPanel(self):
        self._task_panel.Show()
        self.Layout()
        
    # TODO 当有文档还未保存时， 应该提示用户保存后再新建
    # TODO 让用户选择文件类型
    def OnNewFile(self, event):
        self._newfile = self.GetNewFileName()
        self.ChangeTitle(self._newfile, '*')
        self.config = CreateConfig(self, '.cfg')
        self._task_list_panel.Enable(True)
        #self.ShowTaskListPanel()

    def OnOpenFile(self, event):
        wildfilter = "All files (*.*)|*.*|CFG files (*.cfg)|*.cfg|JSON files (*.json)|*.json|XML files (*.xml)|*.xml|CSV files (*.csv)|*.csv"
        openFileDialog = wx.FileDialog(self, "Open config file", "", "", wildfilter, wx.FD_OPEN | wx.FD_FILE_MUST_EXIST)
        if wx.ID_CANCEL == openFileDialog.ShowModal():
            return
        self.location = openFileDialog.GetPath()
        fn = os.path.basename(self.location)
        fileName, fileExtension = os.path.splitext(fn)
        if self.config is None:
            self.config = CreateConfig(self, fileExtension)
        try:
            self.config.load(self.location)
        except IOError, e:
            wx.MessageBox(e.message, '提示', wx.OK | wx.ICON_ERROR)
            self.config = None
            return
        self.ChangeTitle(self.location)
        #self.ShowTaskListPanel()
        if self._task_list_panel.IsShown():
            self._task_list_panel.Enable(True)
            self._task_list_panel.updateView(self.config.data)
        elif self._grid.IsShown():
            self._grid.Enable(True)
            self._grid.updateView(self.config.data)

    def OnSaveFile(self, event):
        # 新建的文件
        if self.location == '':
            self.OnSaveAsFile(None)
        else:
            self.config.store(self.location)
            self.ChangeTitle(self.location)

    def OnSaveAsFile(self, event):
        defaultFileName = ''
        if self.location == '':
            defaultFileName = self._newfile
        saveFileDialog = wx.FileDialog(self, "Save As", "", defaultFileName , 
                                           "JSON files (*.json)|*.json", wx.FD_SAVE | wx.FD_OVERWRITE_PROMPT)
        if wx.ID_CANCEL == saveFileDialog.ShowModal():
            return
        self.location = saveFileDialog.GetPath()
        print "另存为" + self.location
        if self.config is None:
            raise IOError('没有打开的配置数据对象')
        self.config.store(self.location)
        self.ChangeTitle(self.location)
        
    def OnCheckCanSave(self, event):
        # 当配置数据对象存在的时候，可以保存到文件
        event.Enable(self.config is not None and self.config.IsChanged());
    
    def OnCheckCanSaveAs(self, event):
        event.Enable(self.config is not None)

#     def ShowTaskPanel(self, event):
#         self.MakeToolBar()
#         self.MakePanel()

    def ShowMapPanel(self, event):
        self.MakeToolBar()
        box = wx.BoxSizer(wx.VERTICAL)
        box.Add(self._grid, 1, wx.EXPAND)
        self.SetSizer(box)
        self._grid.Show()
        self._grid.Enable(False)
        self.Layout()

    def OnAbout(self, event):
        wx.MessageBox('版本 0.0.1\n当你凝视深渊时，深渊也在凝视着你。', '关于 ' + AppName, wx.OK | wx.ICON_INFORMATION)  

    def OnExit(self, event):
        self.Close()

    def OnClose(self, event):
        if self.config is not None and self.config.IsChanged():
            if self.location == '':
                fileName = self._newfile
            else:
                fileName = os.path.basename(self.location)
            dlg = wx.MessageDialog(self, '保存文件 "' + fileName + '"?', '保存 ', 
                          style=wx.YES_NO | wx.CANCEL | wx.ICON_QUESTION | wx.CENTRE)
            result = dlg.ShowModal()
            dlg.Destroy()
            if result == wx.ID_YES:
                self.OnSaveFile(None)
                self.Destroy()
            if result == wx.ID_NO:
                self.Destroy() 
        else:
            self.Destroy()
          
class ListPanel(wx.Panel):

    def __init__(self, parent):
        wx.Panel.__init__(self, parent, style=wx.BORDER_SUNKEN)
        self._controller = parent
        self._can_delete = False
        self.InitUI()

    def InitUI(self):
        box = wx.BoxSizer(wx.VERTICAL)
        boxTop = wx.BoxSizer(wx.VERTICAL)
        boxBottom = wx.FlexGridSizer(0, 2)
        
        # 
        self.checkList = wx.CheckListBox(self, choices=[], style=wx.LB_HSCROLL)
        self.checkList.Bind(wx.EVT_LISTBOX, self.OnListBox)
        self.checkList.Bind(wx.EVT_CHECKLISTBOX, self.OnCheckListBox)
        boxTop.Add(self.checkList, 1, wx.EXPAND)
        
        # 按钮
        button = wx.Button(self, wx.ID_ANY, "全选")
        self.Bind(wx.EVT_BUTTON, self.OnSelectAll, button)
        self.Bind(wx.EVT_UPDATE_UI, self.OnCheckCanSelectAll, button)
        boxBottom.Add(button, 1)
        
        button = wx.Button(self, wx.ID_ANY, "反选")
        self.Bind(wx.EVT_BUTTON, self.OnUnSelectAll, button)
        self.Bind(wx.EVT_UPDATE_UI, self.OnCheckCanUnSelectAll, button)
        boxBottom.Add(button, 1)
        
        button = wx.Button(self, wx.ID_ANY, "添加")
        self.Bind(wx.EVT_BUTTON, self.OnAdd, button)
        #self.Bind(wx.EVT_UPDATE_UI, self.OnCheckCanAdd, button)
        boxBottom.Add(button, 1)
        button = wx.Button(self, wx.ID_ANY, "删除")
        self.Bind(wx.EVT_BUTTON, self.OnDelete, button)
        self.Bind(wx.EVT_UPDATE_UI, self.OnCheckCanDelete, button)
        boxBottom.Add(button, 1)

        box.Add(boxTop, 1, wx.ALL|wx.EXPAND, 3)
        box.Add(boxBottom, 0, wx.ALL|wx.EXPAND, 3)
        self.SetSizerAndFit(box)
    
    def OnUpdateTaskItem(self, task, pos):
        self.checkList.Delete(pos)
        self.checkList.Insert(task['description'], pos)
        self._controller.OnUpdateTaskItem(task, pos)

    def OnSelectAll(self, event):
        # TODO 封装到CheckListBox派生类中
        for i in range(self.checkList.GetCount()):
            self.checkList.Check(i)
    
    def OnUnSelectAll(self, event):
        # TODO 封装到CheckListBox派生类中
        for i in range(self.checkList.GetCount()):
            self.checkList.Check(i, False)
            
    def OnAdd(self, event):
        desc = u'未命名任务' + str(self.checkList.Count) # 注意保存到文件中的中文字符串必须用unicode编码，否则json.dump会出错
        self.checkList.Append(desc)
        self.checkList.SetFirstItem(self.checkList.Count - 1) # 使添加的项目总是可见
        self._controller.OnAddTaskItem(desc)
        
    def OnDelete(self, event):
        items = self.checkList.GetChecked()[::-1] # 翻转tuple
        for i in items:
            self.checkList.Delete(i)
        #self.checkList.SetFirstItem(max(items))
        self._controller.OnDeleteTaskItem(items)
        self._can_delete = False
    
    # 考虑把这些方法放入派生的CheckListBox类中
    def OnCheckCanSelectAll(self, event):
        for i in range(self.checkList.GetCount()):
            if not self.checkList.IsChecked(i):
                event.Enable(True)
                return
        event.Enable(False)

    def OnCheckCanUnSelectAll(self, event):
        for i in range(self.checkList.GetCount()):
            if self.checkList.IsChecked(i):
                event.Enable(True)
                return
        event.Enable(False)
        
    def OnCheckCanDelete(self, event):
        event.Enable(self._can_delete)
    
    def OnCheckListBox(self, event):
        checklist = event.GetEventObject()
        for i in xrange(checklist.Count):
            if checklist.IsChecked(i):
                self._can_delete = True
                return
        self._can_delete = False
    
    def OnListBox(self, event):
        """用户点击列表项时调用"""
        (pos,) = event.GetEventObject().GetSelections()
        self._controller.OnViewTask(pos)
    
    def updateView(self, data):
        self.checkList.Clear()
        pos = 0
        for t in data:
            self.checkList.Insert(t['description'], pos)
            pos += 1
 
    def Count(self):
        self.checkList.Count

###############################################################################
#
# 配置数据模型
#
###############################################################################

class ConfigData:
#     def loadCSV(self, f):
#         """解析csv文件"""
#         reader = csv.reader(file(f, 'rb'))
#         for line in reader:
#             print line
#             self.data.append(line)

    def __init__(self, controller):
        self._controller = controller
        self.data = []
        self._ischanged = True

    def IsEmpty(self):
        """是否是空配置"""
        return self.data == []
    
    def IsChanged(self):
        return self._ischanged

    def SetDataChange(self, flag=True):
        self._ischanged = flag

    def load(self, filePath):
        pass

    def append(self, elem):
        self.data.append(elem)
        self._ischanged = True
        self._controller.OnConfigDataChanged()

    def delete(self, pos):
        del self.data[pos]
        self._ischanged = True
        self._controller.OnConfigDataChanged()

    def update(self, data, pos):
        self.data[pos] = data
        self._ischanged = True
        self._controller.OnConfigDataChanged()
        
    def store(self, filePath):
        pass
    
    def Count(self):
        return len(self.data)

def CreateConfig(controller, ext):
    if ext in ('.xls', '.xlsx'):
        return ExcelConfig(controller)
    elif ext in ('.cfg', '.json'):
        return JsonConfig(controller)
    elif ext == '.csv':
        print 'create csv config'
        return None
        #CsvConfig(controller)
    else:
        raise IOError(u"不支持的配置文件格式")

class JsonConfig(ConfigData):
    def __init__(self, controller):
        ConfigData.__init__(self, controller)

    def load(self, filePath):
        """解析json文件"""
        # 空文件json.load会抛出异常
        if os.path.getsize(filePath) > 0:
            self.data = json.load(file(filePath, 'rb'))
        self.SetDataChange(False)

    def store(self, filePath):
        f = open(filePath, 'wb+')
        if self.data != []:
            f.write(json.dumps(self.data))
        f.close()
        self.SetDataChange(False)
           
class ExcelConfig(ConfigData):
    def __init__(self, controller):
        ConfigData.__init__(self, controller)

    def load(self, filePath):
        wb = open_workbook(filePath)
        for sheet in wb.sheets():
            self.data.append(sheet)
        self.SetDataChange(False)

    def store(self, filePath):
        print 'store excel'
        self.SetDataChange(False)
        
if __name__ == '__main__':
    print "应用程序启动"
    app = wx.App()
    frm = MyFrame()
    appico = wx.Icon('small.ico', wx.BITMAP_TYPE_ICO, 16, 16)
    frm.SetIcon(appico)
    frm.SetSize((630, 400))
    frm.Centre()
    frm.Show()
    app.SetTopWindow(frm)
    app.MainLoop()
    print "应用程序退出"
