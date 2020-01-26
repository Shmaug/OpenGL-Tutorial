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