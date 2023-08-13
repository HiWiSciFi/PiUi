#include "FileSystem.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

#ifdef _WIN32
#define WIN32_MEAN_AND_LEAN
#include <Windows.h>
#else
#include <unistd.h>
#endif

std::string FileSystem::ReadFileContents(const std::string& path) {
	std::ifstream fs;
	std::stringstream ss;

	fs.open(path, std::ios::in);
	ss << fs.rdbuf();
	fs.close();
	return ss.str();
}

std::string FileSystem::GetExecutablePath() {
	static bool pathFound = false;
	static std::string path;

	if (!pathFound) [[unlikely]] {
		std::vector<char> pathBuffer(256);

#ifdef _WIN32
		{
			do {
				::SetLastError(ERROR_SUCCESS);
				if (::GetModuleFileName(NULL, pathBuffer.data(), pathBuffer.size()) == 0)
					throw std::runtime_error("unknown error getting executable path");
			} while (::GetLastError() == ERROR_INSUFFICIENT_BUFFER && (pathBuffer.resize(pathBuffer.size() * 2), true));
		}
#else
		{
			size_t length;
			do length = ::readlink("/proc/self/exe", pathBuffer.data(), pathBuffer.size());
			while (length == pathBuffer.size() && (pathBuffer.resize(pathBuffer.size() * 2), true));
			pathBuffer.at(pathBuffer.size() - 1) = '\0';
		}
#endif

		path.assign(pathBuffer.data());
	}

	return path;
}
