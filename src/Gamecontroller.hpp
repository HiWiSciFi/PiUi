#pragma once

class Gamecontroller final {
public:
	enum class Button { // XBOX Mapping
		SOUTH   =  0,   // A
		EAST    =  1,   // B
		WEST    =  2,   // X
		NORTH   =  3,   // Y

		LBUMPER =  4,   // L1
		RBUMPER =  5,   // R1

		BACK    =  6,   // Back
		START   =  7,   // Start
		GUIDE   =  8,   // XBox

		LTHUMB  =  9,   // LT
		RTHUMB  = 10    // RT
	};

public:
	static void Init();
	static void PollAll();

	[[nodiscard]] static bool GetButton(Button button);

private:
	static void ConnectedCallback(int jid, int connected);
};
