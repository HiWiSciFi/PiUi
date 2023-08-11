#pragma once

#include <cstdint>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Gamepad final {
public:
	enum class Facebutton : uint8_t {
		DOWN  = 0,
		RIGHT = 1,
		LEFT  = 2,
		UP    = 3,
		A     = DOWN,
		B     = RIGHT,
		X     = LEFT,
		Y     = UP
	};

	enum class Menubutton : uint8_t {
		START = 0,
		BACK  = 1,
		GUIDE = 2
	};

	enum class DPad : uint8_t {
		UP         = 0,
		DOWN       = 1,
		LEFT       = 2,
		RIGHT      = 3
	};

	enum class Joystick : uint8_t {
		LEFT  = 0,
		RIGHT = 1
	};

	enum class Bumper : uint8_t {
		LEFT  = 0,
		RIGHT = 1
	};

	enum class Trigger : uint8_t {
		LEFT = 0,
		RIGHT = 1
	};

private:
	int id;
	bool connected;
	GLFWgamepadstate state;

	Gamepad(int id);

public:
	Gamepad() = default;
	~Gamepad();

	void Update();

	[[nodiscard]] bool GetButton(Facebutton button);
	[[nodiscard]] bool GetButton(Menubutton button);
	[[nodiscard]] bool GetButton(DPad button);
	[[nodiscard]] bool GetButton(Joystick button);
	[[nodiscard]] bool GetButton(Bumper button);

	[[nodiscard]] glm::fvec2 GetJoystick(Joystick joystick);
	[[nodiscard]] glm::fvec1 GetTrigger(Trigger trigger);

	static Gamepad& Get(int id);

	class Any final {
	public:
		Any() = delete;
		~Any() = delete;

		[[nodiscard]] static bool GetButton(Facebutton button);
		[[nodiscard]] static bool GetButton(Menubutton button);
		[[nodiscard]] static bool GetButton(DPad button);
		[[nodiscard]] static bool GetButton(Joystick button);
		[[nodiscard]] static bool GetButton(Bumper button);
	};

private:
	static void JoystickConnectedCallback(int jid, int event);

public:
	static void Init();
	static void UpdateAll();
};
