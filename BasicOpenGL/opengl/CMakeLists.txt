add_executable(MyProgram "main.cpp")

target_compile_definitions(MyProgram PUBLIC -DGLEW_STATIC)

set(GLFW_HOME "E:/Projects/glfw3")
set(GLEW_HOME "E:/Projects/glew-2.1.0")

target_link_libraries(MyProgram
  "${GLFW_HOME}/lib-vc2019/glfw3.lib"
  "${GLEW_HOME}/lib/Release/x64/glew32s.lib"
  "OpenGL32.lib")
target_include_directories(MyProgram PUBLIC
  "${GLFW_HOME}/include"
  "${GLEW_HOME}/include")
