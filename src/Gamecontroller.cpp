#include "Gamecontroller.hpp"
#include <GLFW/glfw3.h>
#include <vector>

static std::vector<Gamecontroller> controllers{ };

void Gamecontroller::Init() {
	glfwSetJoystickCallback(Gamecontroller::ConnectedCallback);
}

void Gamecontroller::PollAll() {
}

bool Gamecontroller::GetButton(Button button) {
	return false;
}

void Gamecontroller::ConnectedCallback(int jid, int connected) {

}
