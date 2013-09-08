# coding=utf-8

import android
a = android.Android()
message = "我换手机号了: 1862******7 旧号月内只短信。请更新通讯录。礼--Eluli"
atts = [u'number']
for cid in a.contactsGetIds().result:
    c = a.contactsGetById(cid, atts)
    if c.result:
        number=c.result[u'number']
        if number:
            if len(number) > 10:
                a.smsSend(number, message)
                print 'send message to #', number
        else:
            print 'contact dont have an invalid number'
    else:
        print 'done'
