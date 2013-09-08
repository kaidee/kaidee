# coding:utf-8
# Author:kaidee

#导入我们需要用到的包和类并且起别名
import sys
from com.android.monkeyrunner import MonkeyRunner as mr
from com.android.monkeyrunner import MonkeyDevice as md
from com.android.monkeyrunner import MonkeyImage as mi
  #connect device 连接设备
  #第一个参数为等待连接设备时间
  #第二个参数为具体连接的设备ID
device = mr.waitForConnection(1.0,'device_id')
if not device:
    print >> (sys.stderr,"fail")
    sys.exit(1)
 #定义要启动的Activity
componentName='com.android.mms/.ui.BootActivity'
 #启动特定的Activity
device.startActivity(component = componentName)
 #等待时间，防止操作太快，设备反应不及时
mr.sleep(1.0)
 #do someting 进行我们的操作
 #新建短信
 #参数是屏幕上坐标值，最后一个参数是动作
device.touch(57,747,'DOWN_AND_UP')
mr.sleep(1.0)
 #输入收件人号码
device.type('10086')
 #发送短信条数
for i in range(0,10):
    #输入短信内容
    device.touch(187,402,'DOWN_AND_UP')
    device.type('Hello')
    mr.sleep(1.0)
     #发送短信
    device.touch(432,380,'DOWN_AND_UP')
    mr.sleep(1.0)
    device.touch(51,752,'DOWN_AND_UP')
    mr.sleep(1.0)
#takeSnapshot截图
mr.sleep(1.0)
result = device.takeSnapshot()
 #save to file 保存到文件，D盘的根目录下
result.writeToFile('d:\\result2.png','png');
