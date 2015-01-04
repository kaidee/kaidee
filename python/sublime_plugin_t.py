
# class save_file(sublime_plugin.EventListener):
#     def on_post_save(self, view):
#         file_name = view.file_name() or ""
#         cmd = "touch " + file_name
#         print("xxx"+file_name)
#         subprocess.call(cmd, shell=True)