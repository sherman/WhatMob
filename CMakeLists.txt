
PROJECT(deviceatlas)

#if you don't want the full compiler output, remove the following line
SET(CMAKE_VERBOSE_MAKEFILE ON)

#add definitions, compiler switches, etc.
ADD_DEFINITIONS(-Wall -O2)

#list all source files here
ADD_EXECUTABLE(deviceatlas main.cpp Trie.cpp Server.cpp Connection.cpp RequestHandler.cpp HttpResponse.cpp HttpRequestParser.cpp)

TARGET_LINK_LIBRARIES(deviceatlas boost_system boost_thread)
