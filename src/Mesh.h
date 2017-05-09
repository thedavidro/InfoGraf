#pragma once

#include "Object.h"
#include <vector>

#include <gtc\matrix_transform.hpp>
#include <glm.hpp>
#include <assimp\types.h>

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	GLuint id;
	string type;
	aiString path;
};

class Mesh {
public:
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;
	
	Mesh(vector<Vertex> vert, vector<GLuint> ind, vector<Texture> text);
	void Draw(Shader MeshShader, GLint DrawMode);

private:
	GLuint VAO, EBO, VBO;
	void setupMesh();
};