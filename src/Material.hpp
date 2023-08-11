#pragma once

#include <string>

class Material final {
private:
	unsigned int program;

public:
	Material(const std::string& vertexShaderCode, const std::string& fragmentShaderCode);
	~Material();

	void Bind();
	int GetUniformLocation(const std::string& name);
};
