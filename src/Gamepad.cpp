#include "Gamepad.hpp"
#include <GLFW/glfw3.h>
#include <array>
#include <iostream>

#define GLFW_MAX_JOYSTICK_COUNT (GLFW_JOYSTICK_LAST + 1)

static std::array<Gamepad, GLFW_MAX_JOYSTICK_COUNT> gamepads;

Gamepad::Gamepad(int id) : id(id), state() {
	connected = glfwJoystickPresent(id);
	if (connected) JoystickConnectedCallback(id, GLFW_CONNECTED);
}

void Gamepad::JoystickConnectedCallback(int jid, int event) {
	gamepads[jid].connected = (event == GLFW_CONNECTED) && glfwJoystickIsGamepad(jid);
	if (gamepads[jid].connected) gamepads[jid].Update();
	std::cout << "Joystick \"" << glfwGetGamepadName(jid) << "\" " << (event == GLFW_CONNECTED ? "connected" : "disconnected") << " Gamepad: " << (glfwJoystickIsGamepad(jid) ? "true " : "false") << std::endl;

	glfwGetGamepadName(jid);
}

Gamepad::~Gamepad() {
}

void Gamepad::Update() {
	glfwGetGamepadState(id, &state);
}

bool Gamepad::GetButton(Facebutton button) {
	if (!connected) return false;
	int glfwButton = (
		button == Facebutton::DOWN  ? GLFW_GAMEPAD_BUTTON_A :
		button == Facebutton::RIGHT ? GLFW_GAMEPAD_BUTTON_B :
		button == Facebutton::LEFT  ? GLFW_GAMEPAD_BUTTON_X : GLFW_GAMEPAD_BUTTON_Y);
	return state.buttons[glfwButton];
}

bool Gamepad::GetButton(Menubutton button) {
	if (!connected) return false;
	int glfwButton = (
		button == Menubutton::START ? GLFW_GAMEPAD_BUTTON_START :
		button == Menubutton::BACK  ? GLFW_GAMEPAD_BUTTON_BACK  : GLFW_GAMEPAD_BUTTON_GUIDE);
	return state.buttons[glfwButton];
}

bool Gamepad::GetButton(DPad button) {
	if (!connected) return false;
	int glfwButton = (
		button == DPad::UP   ? GLFW_GAMEPAD_BUTTON_DPAD_UP   :
		button == DPad::DOWN ? GLFW_GAMEPAD_BUTTON_DPAD_DOWN :
		button == DPad::LEFT ? GLFW_GAMEPAD_BUTTON_DPAD_LEFT : GLFW_GAMEPAD_BUTTON_DPAD_RIGHT);
	return state.buttons[glfwButton];
}

bool Gamepad::GetButton(Joystick button) {
	if (!connected) return false;
	int glfwButton = (button == Joystick::LEFT ? GLFW_GAMEPAD_BUTTON_LEFT_THUMB : GLFW_GAMEPAD_BUTTON_RIGHT_THUMB);
	return state.buttons[glfwButton];
}

bool Gamepad::GetButton(Bumper button) {
	if (!connected) return false;
	int glfwButton = (button == Bumper::LEFT ? GLFW_GAMEPAD_BUTTON_LEFT_BUMPER : GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER);
	return state.buttons[glfwButton];
}

glm::fvec2 Gamepad::GetJoystick(Joystick joystick) {
	if (joystick == Joystick::LEFT) {
		return glm::fvec2(state.axes[GLFW_GAMEPAD_AXIS_LEFT_X], state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y]);
	}
	return glm::fvec2(state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X], state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y]);
}

glm::fvec1 Gamepad::GetTrigger(Trigger trigger) {
	if (trigger == Trigger::LEFT) {
		return glm::fvec1(state.axes[GLFW_GAMEPAD_AXIS_LEFT_TRIGGER]);
	}
	return glm::fvec1(state.axes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER]);
}

Gamepad& Gamepad::Get(int id) {
	return gamepads[id];
}

bool Gamepad::Any::GetButton(Facebutton button) {
	for (int i = 0; i < GLFW_MAX_JOYSTICK_COUNT; i++) {
		if (gamepads[i].GetButton(button)) {
			return true;
		}
	}
	return false;
}

bool Gamepad::Any::GetButton(Menubutton button) {
	for (int i = 0; i < GLFW_MAX_JOYSTICK_COUNT; i++) {
		if (gamepads[i].GetButton(button)) {
			return true;
		}
	}
	return false;
}

bool Gamepad::Any::GetButton(DPad button) {
	for (int i = 0; i < GLFW_MAX_JOYSTICK_COUNT; i++) {
		if (gamepads[i].GetButton(button)) {
			return true;
		}
	}
	return false;
}

bool Gamepad::Any::GetButton(Joystick button) {
	for (int i = 0; i < GLFW_MAX_JOYSTICK_COUNT; i++) {
		if (gamepads[i].GetButton(button)) {
			return true;
		}
	}
	return false;
}

bool Gamepad::Any::GetButton(Bumper button) {
	for (int i = 0; i < GLFW_MAX_JOYSTICK_COUNT; i++) {
		if (gamepads[i].GetButton(button)) {
			return true;
		}
	}
	return false;
}

void Gamepad::Init() {
	glfwSetJoystickCallback(JoystickConnectedCallback);

	for (int i = 0; i < GLFW_MAX_JOYSTICK_COUNT; i++) {
		gamepads[i] = Gamepad(i);
		glfwSetJoystickUserPointer(i, &(gamepads[i]));
	}
}

void Gamepad::UpdateAll() {
	for (int i = 0; i < GLFW_MAX_JOYSTICK_COUNT; i++) {
		gamepads[i].Update();
	}
}
