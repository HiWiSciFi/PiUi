#include <iostream>

#include <glad/glad.h>
#include <glfw/glfw3.h>

int main() {
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(800, 600, "Testwindow", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	/*while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}*/

	gladLoadGLES2Loader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

	const GLubyte* glVersionStr = glGetString(GL_VERSION);
	std::cout << "GL Version: " << glVersionStr << std::endl;

	glfwTerminate();
}
