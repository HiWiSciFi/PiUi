#include "opengl.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "FileSystem.hpp"
#include "Gamepad.hpp"
#include "Material.hpp"
#include "Quad.hpp"

void HandleGLErrors() {
	GLenum error;
	while ((error = glGetError()) != GL_NO_ERROR) {
		std::cout << "GL Error: ";
		switch (error) {
		case GL_NO_ERROR:                      std::cout << "GL_NO_ERROR";                      break;
		case GL_INVALID_ENUM:                  std::cout << "GL_INVALID_ENUM";                  break;
		case GL_INVALID_VALUE:                 std::cout << "GL_INVALID_VALUE";                 break;
		case GL_INVALID_OPERATION:             std::cout << "GL_INVALID_OPERATION";             break;
		case GL_OUT_OF_MEMORY:                 std::cout << "GL_OUT_OF_MEMORY";                 break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: std::cout << "GL_INVALID_FRAMEBUFFER_OPERATION"; break;
		default: std::cout << "unknown error";
		}
		std::cout << std::endl;
	}
}

int main() {
	glfwInit();
	Gamepad::Init();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);
	GLFWwindow* window = glfwCreateWindow(videoMode->width, videoMode->height, "Testwindow", monitor, nullptr);
	//GLFWwindow* window = glfwCreateWindow(800, 600, "Testwindow", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

#ifdef _WIN32
	gladLoadGLES2Loader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
#endif
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (key == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(window, GLFW_TRUE);
	});

	std::string vertexShaderCode = FileSystem::ReadFileContents("res/background.vert.glsl");
	std::string fragmentShaderCode = FileSystem::ReadFileContents("res/background.frag.glsl");
	Material backgroundMaterial(vertexShaderCode, fragmentShaderCode);
	Quad background(&backgroundMaterial, glm::fvec2(0.0f, 0.0f), glm::fvec2(1.0f, 1.0f), 1.0f);
	Quad foreground(&backgroundMaterial, glm::fvec2(0.1f, 0.25f), glm::fvec2(0.1f, 0.5f), 0.9f);

	bool rerender = true;
	while (!glfwWindowShouldClose(window)) {
		if (rerender) {
			glClear(GL_COLOR_BUFFER_BIT);

			// render
			background.Draw();
			foreground.Draw();

			glfwSwapBuffers(window);
			rerender = false;
		}
		glfwPollEvents();
		Gamepad::UpdateAll();
	}

	glfwTerminate();
}
