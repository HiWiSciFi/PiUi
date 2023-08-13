#pragma once

#include <string>

class FileSystem final {
public:
	static std::string ReadFileContents(const std::string& path);

	struct ExecutablePath final {
		std::string name;
		std::string directory;

		ExecutablePath();
		~ExecutablePath();

		ExecutablePath(const ExecutablePath& other);
		ExecutablePath(ExecutablePath&& other) noexcept;
		ExecutablePath& operator=(const ExecutablePath& other);
		ExecutablePath& operator=(ExecutablePath&& other) noexcept;
	};

	static ExecutablePath GetExecutablePath();
};
