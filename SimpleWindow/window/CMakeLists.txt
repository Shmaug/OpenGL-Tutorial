add_executable(MyProgram "main.cpp")

set(GLFW_HOME "E:/Projects/glfw3")

target_link_libraries(MyProgram "${GLFW_HOME}/lib-vc2019/glfw3.lib")
target_include_directories(MyProgram PUBLIC "${GLFW_HOME}/include")
