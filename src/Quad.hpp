#pragma once

#include "Material.hpp"
#include <glm/glm.hpp>

class Quad final {
private:
	unsigned int vertexArray = 0;
	unsigned int vertexBuffer = 0;
	unsigned int uvBuffer = 0;
	unsigned int indexBuffer = 0;
	Material* material = nullptr;

public:
	Quad(Material* material, glm::fvec2 position, glm::fvec2 size, float depth);
	~Quad();

	void SetMaterial(Material* material);
	void Draw();
};
