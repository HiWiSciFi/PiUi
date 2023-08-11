#pragma once

#include "Material.hpp"
#include <glm/glm.hpp>

class Quad final {
private:
	unsigned int vertexArray;
	unsigned int vertexBuffer;
	unsigned int uvBuffer;
	unsigned int indexBuffer;
	Material* material;

public:
	Quad(Material* material, glm::fvec2 position, glm::fvec2 size, float depth);
	~Quad();

	void SetMaterial(Material* material);
	void Draw();
};
