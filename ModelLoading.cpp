//ModelLoading.cpp
/////////////////////////////////////////////

#include "ModelLoading.h"

bool Mesh::loadOBJ(const char * path, std::vector < glm::vec3 > &out_vertices, std::vector < glm::vec2 > &out_uvs, std::vector < glm::vec3 > &out_normals){
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	FILE * file = fopen(path, "r");
	if(file == NULL){
	    printf("Impossible to open the file !\n");
	    return false;
	}

	char line[256];
	char lineHeader[128];

	while(fgets(line, sizeof(line), file)){
		sscanf(line, "%s", lineHeader);

		if(strcmp(lineHeader, "v" ) == 0 ){
            glm::vec3 vertex;
			sscanf(line, "%*s %f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_vertices.push_back(vertex);
        }else if ( strcmp( lineHeader, "vt" ) == 0 ){
            glm::vec2 uv;
			sscanf(line, "%*s %f %f\n", &uv.x, &uv.y );
            temp_uvs.push_back(uv);
        }else if ( strcmp( lineHeader, "vn" ) == 0 ){
            glm::vec3 normal;
			sscanf(line, "%*s %f %f %f\n", &normal.x, &normal.y, &normal.z );
            temp_normals.push_back(normal);
        }else if ( strcmp( lineHeader, "f" ) == 0 ){
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];

			//int matches = sscanf(line, "%*s %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );

			int matches = sscanf(line, "%*s %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2], &vertexIndex[3], &uvIndex[3], &normalIndex[3] );

			if(matches != 12){
				matches = sscanf(line, "%*s %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
			
				if(matches != 9){
					matches = sscanf(line, "%*s %d/%d %d/%d %d/%d\n", &vertexIndex[0], &uvIndex[0],	&vertexIndex[1], &uvIndex[1], &vertexIndex[2], &uvIndex[2]);

					if(matches != 6){
						matches = sscanf(line, "%*s %d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);

						if(matches != 3){
							printf("File can't be read by our simple parser : ( Try exporting with other options\n");
							return false;
						}
					}
				}
			}

			if(matches == 12){
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[3]);

				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				vertexIndices.push_back(vertexIndex[3]);

				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[3]);

				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				uvIndices.push_back(uvIndex[3]);

				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[3]);

				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
				normalIndices.push_back(normalIndex[3]);
			} else if(matches == 9){
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);

				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);

				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			} else if(matches == 6){
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);

				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
			} else if(matches == 3){
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
			} else return false;
		}
	}

	// For each vertex of each triangle
	for(unsigned int i=0, uvSize = (unsigned int)uvIndices.size(),
        normSize = (unsigned int)normalIndices.size(); i<vertexIndices.size(); ++i){
        out_vertices.push_back(temp_vertices[vertexIndices[i] - 1]);

		if(uvSize > 0)
			out_uvs.push_back(temp_uvs[uvIndices[i] - 1]);

		if(normSize > 0)
			out_normals.push_back(temp_normals[normalIndices[i] - 1]);
    }

	this->numIndices = vertexIndices.size();
	return true;
}

void Mesh::BuildMesh(const char* objFile) {	
	// Read our .obj file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals; // Won't be used at the moment.

	bool res = loadOBJ(objFile, vertices, uvs, normals);

	if(loadOBJ(objFile, vertices, uvs, normals)){
		renderMode = GL_TRIANGLES;
        
        glGenBuffers(1, &vertexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

		size_t uvSize = uvs.size(), normSize = normals.size();

		if(uvSize > 0){
			glGenBuffers(1, &uvID);
			glBindBuffer(GL_ARRAY_BUFFER, uvID);
			glBufferData(GL_ARRAY_BUFFER, uvSize * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
		}

		if(normSize > 0){
			glGenBuffers(1, &normID);
			glBindBuffer(GL_ARRAY_BUFFER, normID);
			glBufferData(GL_ARRAY_BUFFER, normSize * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
		}
	}	
}

Mesh::Mesh(const char* objFile) : Object(){
	BuildMesh(objFile);
}

Mesh::~Mesh(){
	
}