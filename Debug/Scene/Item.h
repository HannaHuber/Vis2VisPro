#pragma once
#include "Geometry.h"

class Item : public Geometry {
public:
	Item(glm::mat4& model_matrix, std::vector<Mesh*> m, unsigned int pts);
	virtual ~Item();
	virtual void update(float deltaT);
	// Use draw method from Geometry?
	unsigned int points;
private:
	float alpha;
	glm::vec3 color;

};