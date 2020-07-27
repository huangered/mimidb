add_executable (server "server.c")

target_link_libraries(server cbtree heap port storage util)