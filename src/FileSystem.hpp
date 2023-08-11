#pragma once

#include <string>

class FileSystem final {
public:
	static std::string ReadFileContents(const std::string& path);
	static std::string GetExecutablePath();
};
