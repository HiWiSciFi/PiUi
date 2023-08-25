#include "opengl.h"
//#include <GLFW/glfw3.h>
#include <iostream>
#include "FileSystem.hpp"
#include "Material.hpp"
#include "Quad.hpp"

#include <linux/fb.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

int main() {

	// framebuffer test
	int fbfd = 0;
	struct fb_var_screeninfo var_info;
	fbfd = open("/dev/fb0", O_RDWR);
	if (fbfd == -1) {
		std::cout << "Error: cannot open framebuffer" << std::endl;
		return 1;
	}
	std::cout << "Framebuffer opened" << std::endl;
	if (ioctl(fbfd, FBIOGET_VSCREENINFO, & var_info)) {
		std::cout << "Error reading variable screen info" << std::endl;
	}
	std::cout << "Display info:\n\t" << var_info.xres << "x" << var_info.yres << " " << var_info.bits_per_pixel << std::endl;
	close(fbfd);

	// Path test code
	FileSystem::ExecutablePath exePath = FileSystem::GetExecutablePath();
	std::cout << "Path:\n\t" << exePath.directory << "\n\t" << exePath.name << std::endl;

//	glfwInit();
//	Gamepad::Init();
//
//	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
//	const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);
//
//	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // TODO: maybe change?
//	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
//	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE); // TODO: ?
//	glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
//	glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_FALSE);
//	glfwWindowHint(GLFW_FLOATING, GLFW_FALSE);
//	glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_TRUE);
//	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_FALSE);
//	glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);
//	glfwWindowHint(GLFW_RED_BITS, videoMode->redBits);
//	glfwWindowHint(GLFW_GREEN_BITS, videoMode->greenBits);
//	glfwWindowHint(GLFW_BLUE_BITS, videoMode->blueBits);
//	glfwWindowHint(GLFW_ALPHA_BITS, GLFW_DONT_CARE);
//	glfwWindowHint(GLFW_DEPTH_BITS, GLFW_DONT_CARE);
//	glfwWindowHint(GLFW_STENCIL_BITS, GLFW_DONT_CARE);
//	glfwWindowHint(GLFW_STEREO, GLFW_FALSE);
//	glfwWindowHint(GLFW_SAMPLES, 0); // TODO: multisampling
//	glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);
//	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
//	glfwWindowHint(GLFW_REFRESH_RATE, videoMode->refreshRate);
//	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
//	glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE); // only for non GLES
//	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_FALSE);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, GLFW_NO_ROBUSTNESS); // TODO: maybe update due to Raspi stability
//	glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, GLFW_ANY_RELEASE_BEHAVIOR);
//#ifndef NDEBUG
//	glfwWindowHint(GLFW_CONTEXT_NO_ERROR, GLFW_TRUE);
//#else
//	glfwWindowHint(GLFW_CONTEXT_NO_ERROR, GLFW_FALSE);
//#endif
//	glfwWindowHintString(GLFW_X11_CLASS_NAME, "HiWiSciFi/PiUi");
//	glfwWindowHintString(GLFW_X11_INSTANCE_NAME, "HiWiSciFi/PiUi");
//
//	GLFWwindow* window = glfwCreateWindow(videoMode->width, videoMode->height, "Testwindow", monitor, nullptr);
//	glfwMakeContextCurrent(window);
//
//	// TODO: handle move
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
//
//#ifdef _WIN32
//	gladLoadGLES2Loader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
//#endif
//	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
//	glViewport(0, 0, videoMode->width, videoMode->height);
//	HandleGLErrors();
//
//	glfwShowWindow(window);
//
//	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
//		if (key == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(window, GLFW_TRUE);
//	});
//
//	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
//		glViewport(0, 0, width, height);
//	});
//
//	std::string vertexShaderCode = FileSystem::ReadFileContents("res/background.vert.glsl");
//	std::string fragmentShaderCode = FileSystem::ReadFileContents("res/background.frag.glsl");
//	Material backgroundMaterial(vertexShaderCode, fragmentShaderCode);
//	Quad background(&backgroundMaterial, glm::fvec2(0.0f, 0.0f), glm::fvec2(1.0f, 1.0f), 1.0f);
//	Quad foreground(&backgroundMaterial, glm::fvec2(0.1f, 0.25f), glm::fvec2(0.1f, 0.5f), 0.9f);
//
//	while (!glfwWindowShouldClose(window)) {
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		// render
//		background.Draw();
//
//		if (Gamepad::Any::GetButton(Gamepad::Facebutton::A)) {
//			foreground.Draw();
//			std::cout << "A Pressed" << std::endl;
//		}
//
//		glfwSwapBuffers(window);
//
//		glfwPollEvents();
//		Gamepad::UpdateAll();
//	}
//
//	glfwTerminate();
}
