#include "Quad.hpp"
#include "opengl.h"
#include <vector>
#include <iostream>

Quad::Quad(Material* material, glm::fvec2 position, glm::fvec2 size, float depth) : material(material) {
	std::vector<float> vertices {
		position.x,          position.y + size.y, depth, // bottom left
		position.x + size.x, position.y + size.y, depth, // bottom right
		position.x + size.x, position.y,          depth, // top right
		position.x,          position.y,          depth  // top left
	};

	static std::vector<float> uvs {
		0.0f, 0.0f, // bottom left
		1.0f, 0.0f, // bottom right
		1.0f, 1.0f, // top right
		0.0f, 1.0f  // top left
	};

	static std::vector<unsigned short> indices {
		0, 1, 2, // bottom right triangle
		2, 3, 0  // top left triangle
	};

	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribBinding(0, 0);
	glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
	glBindVertexBuffer(0, vertexBuffer, 0, 3 * sizeof(float));

	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(float), uvs.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribBinding(1, 1);
	glVertexAttribFormat(1, 2, GL_FLOAT, GL_FALSE, 0);
	glBindVertexBuffer(1, uvBuffer, 0, 2 * sizeof(float));

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), indices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
}

Quad::~Quad() {
	glDeleteVertexArrays(1, &vertexArray);
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &uvBuffer);
	glDeleteBuffers(1, &indexBuffer);
}

void Quad::SetMaterial(Material* material) {
	this->material = material;
}

void Quad::Draw() {
	glBindVertexArray(vertexArray);
	material->Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
}
