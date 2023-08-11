#include "FileSystem.hpp"
#include <fstream>
#include <sstream>

#ifdef _WIN32
#define WIN32_MEAN_AND_LEAN
#include <Windows.h>
#else
#include <filesystem>
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
	//TODO: Implement

//#ifdef _WIN32
//	GetModuleFileName(NULL, )
//#else
//	std::filesystem::canonical("/proc/self/exe");
//#endif
	return std::string();
}
