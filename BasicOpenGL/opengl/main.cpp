#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(int argc, char** argv) {
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	GLFWwindow* window = glfwCreateWindow(1600, 900, "MyProgram", nullptr, nullptr);
	if (!window) {
		fprintf(stderr, "Failed to create window\n");
		return 1;
	}

	glfwMakeContextCurrent(window);

	if (const GLubyte* renderer = glGetString(GL_RENDERER))
		printf("OpenGL Renderer: %s\n", renderer);
	else {
		printf("Failed to get OpenGL renderer\n");
		return 1;
	}

	if (const GLubyte* version = glGetString(GL_VERSION))
		printf("OpenGL Version: %s\n", version);
	else {
		printf("Failed to get OpenGL version\n");
		return 1;
	}

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		printf("Failed to initialize GLEW!\n");
		return 1;
	}

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}