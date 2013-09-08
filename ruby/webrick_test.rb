require 'webrick'


# server =WEBrick::GenericServer.new(:Port =>2000)

# trap("INT"){server.shutdown}

# server.start do |socket|
# 	socket.puts Time.now
# end

class MyServlet <WEBrick::HTTPServlet::AbstractServlet
	def do_GET(request,response)
		response.status =200
		response.content_type ="text/plain"
		# response.body ="Hello,World!"
		response.body ="You are trying to load #{request.path}"

	end
end

server =WEBrick::HTTPServer.new(:Port =>2000)
server.mount "/",MyServlet
trap("INT"){server.shutdown}
server.start