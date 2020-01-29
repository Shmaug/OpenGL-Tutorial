# Creating a Window
Now that we have a way to compile some code, we can dive into the fun stuff. Naturally, the first step to making things appear on the screen is to ask the operating system for a piece of the screen for us to use, such as a window.

## The normal way: platform specific window managers
The normal way to create a window in C++ is to use the platform-specific API provided by the operating system. On Windows, simply `#include <Windows.h>` and [call a few functions](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowexa) to create a window. On Linux, it is a little more complicated, as you can use X11 or XCB and you must have the development header files installed in order to do so. Regardless, there is a much easier way to do this, that doesn't involve any platform-specific code: just use another library!

# Wait, how do I use another library with my code?
Before we dive into actually using another library, it is important to understand what a "library" really *is*. When you compile a C or C++ file, you end up with an "object" file (`.obj` or `.o`) which contains the compiled code as well as some metadata such as symbols describing names of functions and such. For example, consider the `main.obj` file produced by compiling `main.cpp` from the previous section, running `objdump -t main.obj` shows all the symbols stored within it:

![objdump -t](https://raw.githubusercontent.com/Shmaug/OpenGL-Tutorial/master/_images/objdump_t.png)

Additionally, we can see the compiled assembly code by running `objdump -d main.obj`:

![objdump -d](https://raw.githubusercontent.com/Shmaug/OpenGL-Tutorial/master/_images/objdump_d.png)

Additionally, if compile a bunch of `.cpp` files into a bunch of `.obj` files, and then combine then into a *library* of compiled code, you would use a tool called a *linker* to *link* all the `.obj` files into one `.lib` file (or, on Linux, the `.cpp` files compile into `.o` files and combine into a single `.a` library)! This is known as a *library* of code, because it not only contains the compiled assembly instructions, but also a table of function names and other metadata which allows us to actually use it.

# Example
Say someone made a library called `my_library` which was composed of three C++ files: `functions.cpp`, `math.cpp`, and `blah.cpp`. First, they would compile it into a library (in CMake this is as simple as changing `add_executable` to `add_library`) which would compile the `.cpp` files into `.obj` files, then link them into a `.lib` file which contains all the compiled C++ code from all the source files:

![objdump -d](https://raw.githubusercontent.com/Shmaug/OpenGL-Tutorial/master/_images/compile_link.png)

Now, say we wanted to call one of these functions from our `main.cpp`. We would have to *link against* `my_library.lib`. This simply means that when we compile our `main.cpp` into `main.obj`, we include `my_library.lib` as if it was part of the same codebase. In other words, we just include `my_library.lib` directly into our program:

![objdump -d](https://raw.githubusercontent.com/Shmaug/OpenGL-Tutorial/master/_images/compile_link_exe.png)

In order to do this, we have to tell our compiler to include `my_library.lib` in the compilation/linking process. Fortunately, this is very easy to do with CMake, we just have to add another line:
```CMake
add_executable(MyProgram "main.cpp")
target_link_libraries(MyProgram "my_library.cpp")
```
We also have to tell our C++ program that the function is defined *somewhere*, which we can do just by declaring the function normally, but without a function body:
```C++
#include <stdio.h>

// Declare this function (but don't actually define the code for it)
int DoStuff();

int main(int argc, char** argv) {
  int x = DoStuff();
  printf("Hello\n");
  return 0;
}
```
Now, when the linker goes to produce the final result (the `.exe` or `.lib` for our code), it will search the linked code files and libraries for the definition of `DoStuff()` and find it in `my_library.lib`.

## Do I really have to declare every function I want to use in my own code?
If the library you are linking against doesn't come with any header files which declare the functions for you, then yes. Fortunately, you will likely never see a library without any header files. This brings us back to the `#include` statement. In practice, C++ code is designed by declaring (but not defining) functions and variables in header files. These header files just lay out what functions exist, what their names are, and what their arguments are. For example, the developer of `my_library.lib` also would give us `my_library.h` which we could use like so:
```C++
#include <stdio.h>

#include "my_library.h"

int main(int argc, char** argv) {
  int x = DoStuff(); // Declared in "my_library.h"
  printf("Hello\n");
  return 0;
}
```

## How does my program know where the header files are?
Recall that using regular quotes with the `#include` directive tells the compiler to search the same folder as the file that the `#include` appeared in for the file, and using `<>` brackets tells the compiler to search *global include directories* for the file. These global include directories can be configured with CMake like so:
```CMake
target_include_directories(MyProgram PUBLIC "/path/to/include/folder")
```
This allows us to write:
```C++
#include <my_library.h>
```
as long as the file `/path/to/include/folder/my_library.h` exists.

## A quick summary
If this was confusing, don't worry. You don't actually have to know the details of how libraries and linking actually *works*, you just have to know how to use them (which I will describe below). In practice, think of it this way:

Your code is composed of a bunch of header files which declare classes and functions (but does not actually define the code for them), and then a bunch of C++ files that actually define the code for them. These C++ files are what *actually* get compiled, the header files basically just say what's inside. If you want to use someone else's compiled code, you have to have their header files (or theoretically make them yourself), and then tell your compiler to link their compiled code (the `.lib` files) into your code (via `target_link_libraries` in CMake).

# GLFW
GLFW is a cross-platform window and input API that handles creating and destroying a window, as well as handling a few other OpenGL specific things. Additionally, it also provides a way to access user input via a mouse and keyboard (or even a joystick) - all without having to interact with any Windows or Linux-specific platforms (which can be a massive pain).

## Installing GLFW
To install GLFW, you simply need to download the source and build it, or download precompiled binaries with headers, [both of which can be found here](https://www.glfw.org/download.html). On Windows, simply download the "64-bit Windows binaries" package and extract the zip file to a folder of your choice (I usually put it in my projects folder or something). It might also be useful to rename the folder from `glfw-3.3.2.bin.WIN64` to `glfw3`. On Linux, you can find "glfw" via your package manager (make sure to get the developer package as well, usually "glfw-devel" or "glfw-dev").

## Linking GLFW into your project
Now that we have the files for GLFW, we just need to tell CMake where they are. 

### Linking GLFW - Windows
In order to make things easier, we can defined a variable within CMakeLists.txt to store the folder that points to GLFW (I extracted the folder to `E:/Projects/glfw3`)
```CMake
set(GLFW_HOME "E:/Projects/glfw3")
```
Now, we need to tell CMake to link the GLFW library with our program. Recall we can do this with `target_link_libraries`:
```CMake
target_link_libraries(MyProgram "${GLFW_HOME}/lib-vc2019/glfw3.lib")
```
Note that there are a lot of libraries that come with GLFW, corresponding to different versions of Visual Studio. Make sure you select the right one (lib-vc2019 for VS2019, lib-vc2017 for VS2017, etc.).

Now we just have to tell CMake to add the GLFW `include` folder to the list of places to search when trying to find files using `#include <>`:
```CMake
target_include_directories(MyProgram PUBLIC "${GLFW_HOME}/include")
```
#### CMakeLists.txt Overview
Your CMakeLists.txt should look something like this now:
```CMake
add_executable(MyProgram "main.cpp")

set(GLFW_HOME "E:/Projects/glfw3")

target_link_libraries(MyProgram "${GLFW_HOME}/lib-vc2019/glfw3.lib")
target_include_directories(MyProgram PUBLIC "${GLFW_HOME}/include")
```

### Linking GLFW - Linux
Since the package manager installs it to the global include and library folders, all we have to do is tell CMake to link the glfw library:
```CMake
target_link_libraries(MyProgram "libglfw.so")
```

## Initializing GLFW
The first thing we need to do is include GLFW into our C++ file. Since we have told CMake where to look, we can simply add `#include <GLFW/glfw3.h>`. Then, we need to initialize and terminate GLFW at the beginning and end of our program, [using `glfwInit` and `glfwTerminate`](https://www.glfw.org/docs/latest/group__init.html):
```C++
#include <stdio.h>
#include <GLFW/glfw3.h>

int main(int argc, char** argv) {
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		return 1;
	}

	glfwTerminate();

	return 0;
}
```
Note that if GLFW fails to initialize, `glfwInit()` returns a nonzero error code, and we can simply exit the program.

## Creating a Window

At this point, we have included GLFW into our program and successfully initialized and terminated it, but we still haven't created a window. To create a window, we simply need to call [glfwCreateWindow](https://www.glfw.org/docs/latest/group__window.html#ga5c336fddf2cbb5b92f65f10fb6043344). This returns a pointer to a `GLFWwindow`, which we can later use to reference our window. If `glfwCreateWindow` fails, then it returns `nullptr` and we can exit the program (I default the window to 1600x900 pixels):
```C++
GLFWwindow* window = glfwCreateWindow(1600, 900, "MyProgram", nullptr, nullptr);
if (!window) {
  fprintf(stderr, "Failed to create window\n");
  return 1;
}
```
At the end of our program, we need to destroy the window as well:
```C++
glfwDestroyWindow(window);
```

Your program should now look something like this:
```C++
#include <stdio.h>
#include <GLFW/glfw3.h>

int main(int argc, char** argv) {
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		return 1;
	}
	
	GLFWwindow* window = glfwCreateWindow(1600, 900, "MyProgram", nullptr, nullptr);
	if (!window) {
		fprintf(stderr, "Failed to create window\n");
		return 1;
	}


	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
```
Running the program, you should see a window pop up for a split second and then disappear. This is because we call `glfwDestroyWindow` immediately after we call `glfwCreateWindow`. In reality, we should wait for the operating system to tell us to close the window, which might happen when the user presses the X button, or the system shuts off.

## The Event Loop
When a user presses a key or moves the mouse, the operating system generates *events*. These events are added into an *event queue*, which we tell GLFW to read by calling `glfwPollEvents()`. When this function is called, GLFW empties the operating system's event queue and handles all the events that have occurred (more on this later). We also need to know whether or not the operating system wants our window to close, by calling `glfwWindowShouldClose(window)`. These two functions allow us to set up a basic window lifecycle:
```C++
#include <stdio.h>
#include <GLFW/glfw3.h>

int main(int argc, char** argv) {
  if (!glfwInit()) {
    fprintf(stderr, "Failed to initialize GLFW\n");
    return 1;
  }

  GLFWwindow* window = glfwCreateWindow(1600, 900, "MyProgram", nullptr, nullptr);
  if (!window) {
    fprintf(stderr, "Failed to create window\n");
    return 1;
  }

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
```

Now we have a window that stays open and receives events until we close it by pressing the X button!

## [Next up: using OpenGL](https://github.com/Shmaug/OpenGL-Tutorial/blob/master/ProjectSetup/README.md)