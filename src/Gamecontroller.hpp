#pragma once

class Gamecontroller final {
public:
	enum class Button {
		A           =  0,
		B           =  1,
		X           =  2,
		Y           =  3,
		LBUMPER     =  4,
		RBUMPER     =  5,
		BACK        =  6,
		START       =  7,
		GUIDE       =  8,
		LSTICK      =  9,
		RSTICK      = 10,
		DUP         = 11,
		DRIGHT      = 12,
		DDOWN       = 13,
		DLEFT       = 14
	};

public:
	static void Init();
	static void PollAll();

	[[nodiscard]] static bool GetButton(Button button);

private:
	static void ConnectedCallback(int jid, int connected);
};
