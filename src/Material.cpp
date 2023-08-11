#include "Material.hpp"
#include "opengl.h"
#include <iostream>

Material::Material(const std::string& vertexShaderCode, const std::string& fragmentShaderCode) {
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* vertexShaderSource = vertexShaderCode.c_str();
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragmentShaderSource = fragmentShaderCode.c_str();
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "ERROR: Vertex Shader compilation failed:\n" << infoLog << std::endl;
	}

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "ERROR: Fragment Shader compilation failed:\n" << infoLog << std::endl;
	}

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, nullptr, infoLog);
		std::cout << "ERROR: Shader Program linking failed:\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Material::~Material() {
	glDeleteProgram(program);
}

void Material::Bind() {
	glUseProgram(program);
}

int Material::GetUniformLocation(const std::string& name) {
	return glGetUniformLocation(program, name.c_str());
}
