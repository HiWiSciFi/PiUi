#include <iostream>

#include <glfw/glfw3.h>

int main() {
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(800, 600, "Testwindow", nullptr, nullptr);
	std::cout << "Hello World!" << std::endl;

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}

	glfwTerminate();
}
