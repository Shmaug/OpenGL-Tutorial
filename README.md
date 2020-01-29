# Learning Modern OpenGL (and C++)
This tutorial is designed for people with a background in high-level engines (namely Unity) and programming experience (not necessarily C++). I will describe setting up a cross-platform C++ project using CMake, covering all the steps in great detail.

OpenGL is a powerful and extensible graphics platform, but can be incredibly confusing to set up. The step between engines such as Unity and OpenGL is daunting and confusing for many, which this tutorial aims to bridge.

## What this tutorial covers
This tutorial aims to bridge the gap between conventional high-level engines such as Unity and low-level graphics in C++ and OpenGL. This tutorial assumes intermediate knowledge of Unity (GameObject heirarchies, basic material setup, etc), and will cover how to set up a C++ OpenGL project from scratch, and how to implement basic rendering functionality.

# Recommended Tools
Unity provides a nice interface to creating a project, and handles the intricacies of compiling your code and organizing dependencies. In C++, you must handle these yourself. *This is the most common part I've seen people get stuck on, so I will go through it in detail*.

## Recommended Tools - Windows
On Windows, Visual Studio is the way to go. If you come from a Unity background, you probably already have it installed, however there are certain "workflows" required to make Visual Studio play nice with C++. These *should* have come installed already, but just in case, launch the "Visual Studio Installer" program (it comes with Visual Studio, so you should already have it) and click "Modify" on the version of Visual Studio you intend to use:

![Modify Visual Studio](https://raw.githubusercontent.com/Shmaug/OpenGL-Tutorial/master/_images/vs_modify.png)

Now, we will select a few components to install. I use the following workloads:

![Visual Studio Workloads](https://raw.githubusercontent.com/Shmaug/OpenGL-Tutorial/master/_images/vs_workloads.png)

Additionally, I recommend using CMake (described later). Visual Studio 2019 has integrated CMake support, which you can enable by going to the "Individual Components" tab and enabling:

![Visual Studio CMake](https://raw.githubusercontent.com/Shmaug/OpenGL-Tutorial/master/_images/vs_cmake.png)

## Recommended Tools - Linux
On Linux, `g++` is a good tool to compile C++ projects. Most distributions of Linux come with it, so you should be good to go. Additionally, I recommend using CMake as a build system, which again comes with most distributions of Linux.


# [Start here!](https://github.com/Shmaug/OpenGL-Tutorial/blob/master/ProjectSetup)