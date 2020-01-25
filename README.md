# Learning Modern OpenGL
OpenGL is a powerful and extensible graphics platform, but can be incredibly confusing to set up. The step between engines such as Unity and OpenGL is daunting and confusing for many, which this tutorial aims to bridge.

## What this tutorial covers
This tutorial aims to bridge the gap between conventional high-level engines such as Unity and low-level graphics in C++ and OpenGL. This tutorial assumes intermediate knowledge of Unity (GameObject heirarchies, basic material setup, etc), and will cover how to set up a C++ OpenGL project from scratch, and how to implement basic rendering functionality.

# Recommended Tools
Unity provides a nice interface to creating a project, and handles the intricacies of compiling your code and organizing dependencies. In C++, you must handle these yourself. *This is the most common part I've seen people get stuck on, so I will go through it in detail*.

## Recommended Tools - Windows
On Windows, Visual Studio is the way to go. If you come from a Unity background, you probably already have it installed, however there are certain "workflows" required to make Visual Studio play nice with C++. These *should* have come installed already, but just in case, launch the "Visual Studio Installer" program (it comes with Visual Studio, so you should already have it) and click "Modify" on the version of Visual Studio you intend to use.

## Recommended Tools - Linux
On Linux, `gcc` is a good tool to compile C++ projects. Most distributions of Linux come with it, so you should be good to go.

# So, where do I start?
At the end of the day, we want to write a bunch of C++ code, across a bunch of `.cpp` files. Let's start simple, with a single C++ file. Make a new folder somewhere, and make a file called `main.cpp` inside of it.