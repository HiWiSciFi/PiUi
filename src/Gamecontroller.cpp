#include "Gamecontroller.hpp"
#include <vector>

static std::vector<Gamecontroller> controllers{ };

void Gamecontroller::Init() {

}

void Gamecontroller::PollAll() {
}

bool Gamecontroller::GetButton(Button button) {
	return false;
}

void Gamecontroller::ConnectedCallback(int jid, int connected) {

}
