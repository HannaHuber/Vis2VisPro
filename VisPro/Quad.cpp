#include "Quad.h"

Quad::Quad() {

	// Init vao
	glGenVertexArrays(1, &vao);												 
	glBindVertexArray(vao);
	
	// Init vbo
	glGenBuffers(1, &vbo);																				
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Bind vertex data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);									  																	 
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);		
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));

	// Unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	
}

// Init vertex positions
GLfloat Quad::vertices[24] = { /*0.0f, 800.0f, 0.0f, 1.0f,
							   0.0f, 0.0f, 0.0f, 0.0f,
							   1024.0f, 0.0f, 1.0f, 0.0f,

							   0.0f, 800.0f, 0.0f, 1.0f,
							   1024.0f, 0.0f, 1.0f, 0.0f,
							   1024.0f, 800.0f, 1.0f, 1.0f*/

							   - 1.0f, 1.0f, 0.0f, 1.0f,
							   -1.0f, -1.0f, 0.0f, 0.0f,
							   1.0f, -1.0f, 1.0f, 0.0f,

							   -1.0f, 1.0f, 0.0f, 1.0f,
							   1.0f, -1.0f, 1.0f, 0.0f,
							   1.0f, 1.0f, 1.0f, 1.0f
};


Quad::~Quad() {
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);

}

void Quad::bindVAO() {
	glBindVertexArray(vao);
}