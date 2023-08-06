#include <iostream>

#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>

int main() {
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Testwindow", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	/*while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}*/

	const GLubyte* glVersionStr = glGetString(GL_VERSION);
	std::cout << "GL Version: " << glVersionStr << std::endl;

	glfwTerminate();
}
