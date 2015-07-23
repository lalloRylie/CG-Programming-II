//ModelLoading.h
/////////////////////////////////////////////

#pragma once

#include "Application.h"
#include "Object.h"
#include <vector>

bool loadOBJ(const char * path, std::vector < glm::vec3 > &out_vertices, std::vector < glm::vec2 > &out_uvs, std::vector < glm::vec3 > &out_normals);

class Mesh : public Object{

	public:
		Mesh();
		virtual ~Mesh();
		char* OBJFile;

	private:
		void BuildMesh();
		bool loadOBJ(const char * path, std::vector < glm::vec3 > &out_vertices, std::vector < glm::vec2 > &out_uvs, std::vector < glm::vec3 > &out_normals);
};