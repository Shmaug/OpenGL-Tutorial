# OpenGL: From the Beginning
Now that we have use GLFW to get our very own part of the screen from the operating system, we can begin to actually use it. For this, we will need to initialize an *OpenGL Context*

## What even *is* OpenGL?
In the days when computers were *just* powerful enough to make things show up on screens (other than a terminal window), the capabilities were extremely limited and specialized. Many different devices were created supporting various graphical capabilities ([some didn't even use pixels!](https://en.wikipedia.org/wiki/Vectrex)) and there was no real standard for any common graphical support. Eventually, raster graphics took over as the dominant way of drawing things on a screen.

*Raster graphics?*

The word *raster* merely refers to "a rectangular pattern," and to *rasterize* means to put something into this rectangular pattern. Thus, *raster graphics* refers to pixel-based graphics, where the screen is a rectangular grid of pixels, and *rasterization* refers to the process of turning things into pixels on a screen.

This method was incredibly versatile, however it required hefty computational power to be able to process all the pixels on the screen in a reasonable amount of time. To solve this, the first ***graphics processing units*** (GPUs) were created, which connected to the physical screen and received commands called from code in order to make things appear on the screen. The first GPUs were incredibly limited and specialized, providing only *fixed-function* support for certain algorithms and routines.

In 1991, OpenGL 1.0 was released, describing itself as:
>OpenGL is a set of commands that allow the specification of geometric objects in two or three dimensions together with commands that control how these objects are rendered into the framebuffer.

In order to actually use this state machine, the programmer creates a *context* which tracks values and parameters, allowing the programmer to specify things such as shapes and colors as well as issuing *draw calls*. A *draw call* merely refers to the act of telling the computer to draw something.

In short, OpenGL is an API that programmers can use to talk to the graphics hardware. It specifies functions and features, however it leaves the *implementation* up to the operating system or hardware manufacturer (these are what "drivers" are: implementations of OpenGL/DirectX/etc for a specific piece of hardware, written by the hardware manufacturer). Because of this, OpenGL implementations vary between systems and graphics hardware manufacturers (primarily AMD, Nvidia and Intel).

## A note on OpenGL Extensions
Because of the nature of how OpenGL is implemented, it requires rapid extensibility so that new hardware features are accessible to OpenGL programmers. In order to provide this, OpenGL provides *extensions* which are optional features and functions that might not exist on all hardware setups. As a trivial example, if a new piece of hardware came out that allowed drawing of some new shape, and OpenGL programmers wanted to use it, the hardware manufacturer could develop an OpenGL *extension* which implements this special functionality.

Over the decades that OpenGL has been around, hundreds of extensions have been developed, and modern hardware implements most of them. Additionally, Modern graphics programs leverages and require of countless of them as well.

# Using OpenGL
Keeping what OpenGL *is* in mind (a giant state machine that manages talking to the graphics hardware in your computer), we can finally start to actually use it. All we need to do is link the OpenGL library (which comes with most operating system developer packages such as Visual Studio these days) and include the OpenGL header. 

Fortunately, the required files we need are (typically) already in our system folders, we just have to tell CMake to use them. To do this, we simply append `"OpenGL32.lib"` to the `target_link_libraries` command in our `CMakeLists.txt`:
```CMake
target_link_libraries(MyProgram "${GLFW_HOME}/lib-vc2019/glfw3.lib" "OpenGL32.lib")
```
In order to do many of the things modern harware requires, we just have to make sure see that the few dozens of extensions we need are available, and then find out the names and addresses of a hundreds of function pointers are...

At least, that's the *pure OpenGL* way of doing things. As you might have guessed, OpenGL extensions are difficult to manage when there are so many to implement, and this has been known for quite some time. Fortunately, the [OpenGL Extension Wrangler (GLEW)](http://glew.sourceforge.net/) exists to take care of extension management for us.

# Using OpenGL - With GLEW
## GLEW Setup - Windows
Download and extract the GLEW binaries and place them somewhere (I place it next to GLFW), then tell CMake to link to it and include it. For simplicity, make a variable that stores the install location of GLEW:
```CMAKE
set(GLEW_HOME "E:/Projects/glew-2.1.0")
```
Then tell CMake to link against the GLEW and GLU libraries, as well as to use the GLEW include folder to resolve global includes:
```CMake
target_include_directories(MyProgram PUBLIC
  "${GLFW_HOME}/include"
  "${GLEW_HOME}/include")
target_link_libraries(MyProgram
  "${GLFW_HOME}/lib-vc2019/glfw3.lib"
  "${GLEW_HOME}/lib/Release/x64/glew32s.lib"
  "OpenGL32.lib")
```
Lastly, we want to tell GLEW that we are linking statically, so we must define the `GLEW_STATIC` compiler macro. We can do this with CMake:
```CMake
target_compile_definitions(MyProgram PUBLIC -DGLEW_STATIC)
```
After this step, we are done with linking libraries.

### Static linking? Compiler macros? What??
In the previous page, I described how to link someone else's compiled code into your project. What I described is called *static linking*. There is another way of linking external code, called *dynamic linking*. This is where you use other compiled code libraries - but instead of compiling that into your program, you reference it at runtime. These compiled code files you reference are called *dynamically linked libraries* and come with the `.dll` suffix on Windows. These can reduce the size of your program, since it doesn't have external code included within it, however it requires the program to be able to find these `dll` files or else it will not work.

Since the GLEW and GLFW libraries are small (a few kilobytes), it is simpler to just link them statically.

#### So what about compiler macros?
While a compiler is compiling a code file, it can keep track of many things that might change the resulting assembly. One of these features is the ability to define *macros*. Macros are just tokens that can be expanded at compile-time into real code. They are defined with the `#define` directive, like so:
```C++
#define MyMacro printf("Hello World");
```
This defines a macro called `MyMacro` and means that the compiler will simply replace the string `MyMacro` with the string `printf("Hello World");` within your code. Additionally, you can check if a macro is defined or not with the `#ifdef` macro:
```C++
#ifdef GLEW_STATIC
// <code that is compiled if GLEW_STATIC is defined>
#endif
```
This code causes the compiler to compile the code between the `#ifdef` and `#endif` statements ONLY if the `GLEW_STATIC` macro is defined. This is why we must tell CMake to define `GLEW_STATIC` for us, since the `glew.h` header file uses this macro to choose which code to use, depending on whether or not GLEW is statically linked. Specifically, if GLEW_STATIC is *not* defined, GLEW will find and link against `glew32.dll` when GLEW is initialized at runtime.
***
## GLEW Setup - Linux
Simply install `glew` with your package manager, then append `"libGLEW.so" "libGL.so"` (in that order!) to the `target_link_libraries` line to link against GLEW and OpenGL:
```CMake
target_link_libraries(MyProgram "libglfw.so" "libGLEW.so" "libGL.so")
```