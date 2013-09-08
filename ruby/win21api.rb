# require 'Win32API'

# title ="My Application"
# text ="Hello World!"
# dialog =Win32API.new('user32','MessageBox','LPPL','I')
# result =dialog.call(0,text,title,1)
# case result
# 	when 1;
# 		puts "Clicked OK"
# 	when 2;
# 		puts "Clicked Cancel"
# 	else
# 		puts "Clicked something else!"
# end
			
require 'win32ole'		

web_browser =WIN32OLE.new('InternetExplorer.Application')	#InternetExplorer
web_browser.visible =true
web_browser.navigate('http://localhost/')

while web_browser.ReadyState !=4
	sleep 1
end
puts "Page is loaded"