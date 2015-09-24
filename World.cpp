#include "World.h"
#include "ModelLoading.h"

GLuint texture1 = NULL;
GLuint texture2 = NULL;

//TODO: Restructure the project
namespace{
	const u8 MAX_BUFFER_SIZE = 64;
	const u8 MAX_PATH_SIZE = 32;

	u16 GetNumCharCount(u8 *src){
		u16 count = 0;
		while(IS_NUMBER(*src)){
			++count;
			++src;
		}

		return count;
	}
}

static void FillBuffer(u8 *src, u8 *dest, u16 &index, u16 const &length){
	for(u16 i = 0, count = 0; count < length; ++i){
		if(IS_NUMBER(src[i])){
			dest[index++] = src[i];
			++count;
		}
	}
}

//TODO: Add functionality later...
World::World(){
	/*mesh1 = new Mesh();
	mesh1->BuildMesh("./Assets/Models/plane.obj");
	mesh1->SetScale(vec3(1.0));
	mesh1->SetPosition(vec3(0.0f, 0.0f, 0.0f));*/

	mesh = new Mesh();
	mesh->BuildMesh("./Assets/Models/dense_sphere.obj");
	mesh->SetScale(vec3(1.0f));
	mesh->SetRotation(0.3f);
	mesh->SetPosition(vec3(0.0f));

	texture1 = mesh->LoadBMP("./Assets/Textures/sun.bmp");

}

World::~World(){
	/*delete mesh1;
	mesh1 = NULL;*/

	delete mesh;
	mesh = NULL;
}

void World::Update(const float& deltaTime){

	//mesh1->Update(deltaTime);
	mesh->Update(deltaTime);
}

void World::Render(const Camera& camera){
	//mesh1->Render(camera);
	mesh->Render(camera);
}