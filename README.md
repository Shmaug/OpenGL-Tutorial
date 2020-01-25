# Learning Modern OpenGL (and C++)
OpenGL is a powerful and extensible graphics platform, but can be incredibly confusing to set up. The step between engines such as Unity and OpenGL is daunting and confusing for many, which this tutorial aims to bridge.

## What this tutorial covers
This tutorial aims to bridge the gap between conventional high-level engines such as Unity and low-level graphics in C++ and OpenGL. This tutorial assumes intermediate knowledge of Unity (GameObject heirarchies, basic material setup, etc), and will cover how to set up a C++ OpenGL project from scratch, and how to implement basic rendering functionality.

# Recommended Tools
Unity provides a nice interface to creating a project, and handles the intricacies of compiling your code and organizing dependencies. In C++, you must handle these yourself. *This is the most common part I've seen people get stuck on, so I will go through it in detail*.

## Recommended Tools - Windows
On Windows, Visual Studio is the way to go. If you come from a Unity background, you probably already have it installed, however there are certain "workflows" required to make Visual Studio play nice with C++. These *should* have come installed already, but just in case, launch the "Visual Studio Installer" program (it comes with Visual Studio, so you should already have it) and click "Modify" on the version of Visual Studio you intend to use:

![Modify Visual Studio](https://raw.githubusercontent.com/Shmaug/OpenGL-Tutorial/master/images/vs_modify.png)

Now, we will select a few components to install. I use the following workloads:

![Visual Studio Workloads](https://raw.githubusercontent.com/Shmaug/OpenGL-Tutorial/master/images/vs_workloads.png)

Additionally, I recommend using CMake (described later). Visual Studio 2019 has integrated CMake support, which you can enable by going to the "Individual Components" tab and enabling:

![Visual Studio CMake](https://raw.githubusercontent.com/Shmaug/OpenGL-Tutorial/master/images/vs_cmake.png)

## Recommended Tools - Linux
On Linux, `g++` is a good tool to compile C++ projects. Most distributions of Linux come with it, so you should be good to go. Additionally, I recommend using CMake as a build system, which again comes with most distributions of Linux.

# So, where do I start?
At the end of the day, we want to write and compile a bunch of C++ code, across a bunch of `.cpp` files. Let's start simple, with a single C++ file. Make a new folder somewhere, and make a file called `main.cpp` inside of it. We will start with a classic Hello World program (try to use a simple text editor instead of an IDE like Visual Studio for this step):
```C++
#include <stdio.h>

int main(int argc, char** argv) {
  printf("Hello\n");
  return 0;
}
```
## A note on `#include`
I think it is important to understand what is going on under the hood of Unity real quick before diving into C++. Lets think about what it takes to go from readable C# code to instructions executing on a physical processor. C# "compiles" to an intermediate language (IL) which is then interpreted at runtime by the Microsoft Common Language Runtime (CLR). The CLR is only available on Windows, however Unity uses a version of the CLR called Mono which is cross-platform. These interpreters interpret the IL produced by the C# compiler *at runtime*, producing machine code (assembly) which is then read by a processor (this is called just-in-time compilation). This allows the interpreter to do all sorts of things like memory management and dependency resolution.

If that sounded complicated and scary, then I have good news: C++ is actually far simpler. C++ compiles **directly** to assembly, which is read by the processor. This means there is virtually zero magic complicated things happening under the hood (for all intents and purposes), which makes things far simpler to understand.
***
With that in mind, let's look at the first line:
```C++
#include <stdio.h>
```
This is analogous to the `using` statement in C#, although its functionality is actually far simpler! In C#, the line `using UnityEngine;` statement causes the compiler to look for a package named `UnityEngine`, which you must configure your project/compiler to be able to find — in practice, Unity configures it for you. 

In C++, a line beginning with `#` is read as a "directive" for the compiler. The `#include` directive simply tells the compiler to literally paste the contents of the file given directly into this file. So, the line `#include <stdio.h>` simply gets replaced with the contents of the file `stdio.h`.
***
### Wait, where does the compiler find these files?
You might be wondering where the `stdio.h` file is on your computer in the first place. On Windows, installing the C++ workloads will download windows-specific versions of `stdio.h` and other standard C/C++ files into your Visual Studio/Microsoft SDK install folder. On Linux, pretty much all header files go into `/usr/include/` or something similar.
***
### So, all files I want to include have to be in these particular folders?
Nope! Notice the brackets used in the directive: 
```C++
#include <stdio.h>
```
The use of `<>` brackets tells the compiler that this is a **global** include. This will make the compiler look in the default include paths for your computer. In contrast, the statement
```C++
#include "stdio.h"
```
is a **local** include directive. The use of `""` quotes here tells the compiler to look in the same folder as the file this `#include` statement appears in (you'll use these for when you make your own header files). This statement will actually cause the program to fail to compile (unless you have a file called `stdio.h` located in the same folder of course).

# Okay, so how do I compile it?

Now that we have a simple program, we have to figure out how to run it. This is as simple feeding in the path to your `main.cpp` file to a compiler. On Windows, simply run `cl main.cpp` (you won't be able to run this from a regular command prompt, you'll have to use the Visual Studio Developer Command Prompt which comes with Visual Studio), which produces the program `main.exe` and `main.obj`. On Linux, run `g++ main.cpp`, which produces the program `main` and `main.o`.