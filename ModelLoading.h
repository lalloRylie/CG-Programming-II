//ModelLoading.h
/////////////////////////////////////////////

#pragma once

#include "Application.h"
#include "Object.h"
#include <vector>

class Mesh : public Object{

public:
	Mesh(){}
	Mesh(const char* objFile);
	virtual ~Mesh();

	void BuildMesh(const char* objFile);

private:		
	bool loadOBJ(const char * path, std::vector < glm::vec3 > &out_vertices, std::vector < glm::vec2 > &out_uvs, std::vector < glm::vec3 > &out_normals);
};