#include "FileSystem.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <unistd.h>

std::string FileSystem::ReadFileContents(const std::string& path) {
	std::ifstream fs;
	std::stringstream ss;

	fs.open(path, std::ios::in);
	ss << fs.rdbuf();
	fs.close();
	return ss.str();
}

FileSystem::ExecutablePath FileSystem::GetExecutablePath() {
	static bool pathFound = false;
	static ExecutablePath path{ };

	if (!pathFound) {
		std::vector<char> pathBuffer(256);

		size_t length;
		do length = ::readlink("/proc/self/exe", pathBuffer.data(), pathBuffer.size());
		while (length == pathBuffer.size() && (pathBuffer.resize(pathBuffer.size() * 2), true));
		pathBuffer.at(pathBuffer.size() - 1) = '\0';

		std::string pathstr(pathBuffer.data());
		size_t lastSeparator = pathstr.find_last_of("/\\");
		path.name = pathstr.substr(lastSeparator + 1);
		path.directory = pathstr.substr(0, lastSeparator);
	}

	return path;
}

FileSystem::ExecutablePath::ExecutablePath()
	: name(), directory() { }

FileSystem::ExecutablePath::~ExecutablePath() { }

FileSystem::ExecutablePath::ExecutablePath(const ExecutablePath& other)
	: name(other.name), directory(other.directory) { }

FileSystem::ExecutablePath::ExecutablePath(ExecutablePath&& other) noexcept {
	*this = std::move(other);
}

FileSystem::ExecutablePath& FileSystem::ExecutablePath::operator=(const ExecutablePath& other) {
	if (this != &other) {
		name = other.name;
		directory = other.directory;
	}
	return *this;
}

FileSystem::ExecutablePath& FileSystem::ExecutablePath::operator=(ExecutablePath&& other) noexcept {
	if (this != &other) {
		name = std::move(other.name);
		directory = std::move(other.directory);
	}
	return *this;
}
