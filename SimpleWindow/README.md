# Creating a Window
Now that we have a way to compile some code, we can dive into the fun stuff. Naturally, the first step to making things appear on the screen is to ask the operating system for a piece of the screen for us to use, such as a window.

## The normal way: platform specific window managers
The normal way to create a window in C++ is to use the platform-specific API provided by the operating system. On Windows, simply `#include <Windows.h>` and [call a few functions](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowexa) to create a window. On Linux, it is a little more complicated, as you can use X11 or XCB and you must have the development header files installed in order to do so. Regardless, there is a much easier way to do this, that doesn't involve any platform-specific code: just use another library!

# GLFW
GLFW (GL Framework) is a common cross-platform window and input API that handles creating and destroying a window, as well as handling a few other OpenGL specific things. Additionally, it also provides a way to access user input via a mouse and keyboard (or even a joystick) - all without having to interact with any Windows or Linux-specific platforms (which can be a massive pain).

# Wait, how do I use another library with my code?
Before we dive into actually using another library, it is important to understand what a "library" really *is*. When you compile a C or C++ file, you end up with an "object" file (`.obj` or `.o`) which contains the compiled code as well as some metadata such as symbols describing names of functions and such. For example, consider the `main.obj` file produced by compiling `main.cpp` from the previous section, running `objdump -t main.obj` shows all the symbols stored within it:

![objdump -t](https://raw.githubusercontent.com/Shmaug/OpenGL-Tutorial/master/_images/objdump_t.png)

Additionally, we can see the compiled assembly code by running `objdump -d main.obj`:

![objdump -d](https://raw.githubusercontent.com/Shmaug/OpenGL-Tutorial/master/_images/objdump_d.png)

Additionally, if compile a bunch of `.cpp` files into a bunch of `.obj` files, and then combine then into a *library* of compiled code, you would use a tool called a *linker* to *link* all the `.obj` files into one `.lib` file (or, on Linux, the `.cpp` files compile into `.o` files and combine into a single `.a` library)! This is known as a *library* of code, because it not only contains the compiled assembly instructions, but also a table of function names and other metadata which allows us to actually use it.

# Example
Say someone made a library called `my_library` which was composed of three C++ files: `functions.cpp`, `math.cpp`, and `blah.cpp`. First, they would compile it into a library (in CMake this is as simple as changing `add_executable` to `add_library`) which would compile the `.cpp` files into `.obj` files, then link them into a `.lib` file which contains all the compiled C++ code from all the source files: