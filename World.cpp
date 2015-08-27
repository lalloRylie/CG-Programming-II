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
	//plane = new Plane(1, 1);
	//plane->SetScale(vec3(0.15f));
	//plane->SetPosition(vec3(-1.0f, -1.0f, 0.0f));

	//cube = new Cube();

	mesh = new Mesh();
	mesh->BuildMesh("./Assets/Models/arceus.obj");
	mesh->SetPosition(vec3(0.0f));
	mesh->SetRotation(1.2f);
	mesh->SetScale(vec3(2.0f));

	texture1 = mesh->LoadBMP("./Assets/Textures/arceus.bmp");
	
	//GLuint textureID = plane->LoadBMP("test.bmp");
	//GLuint textureID = plane->LoadBMP("dirt.bmp");
	//GLuint textureID = plane->LoadBMP("world.bmp");

	////load world...
	//ifstream myfile(LEVEL_0);

	//char buffer[::MAX_BUFFER_SIZE];
	//char path[::MAX_PATH_SIZE];

	//if (myfile.is_open())
	//{
	//	string line;
	//	unsigned char len = 0;

	//	bool loadLevelData = true;

	//	while(getline (myfile,line) )
	//	{
	//		line.copy(buffer, len = line.length());
	//		buffer[len] = '\0';

	//		if(IS_EMPTY_LINE(buffer[0])){
	//			continue;
	//		}
	//		else if(LOAD_TEXTURE(buffer[0])){
	//			//Setting buffer size...
	//			numTextures = buffer[1] - ASCII_ZERO;
	//			textureBuffer = (u8*)malloc(MAX_PATH_SIZE * numTextures);

	//			loadLevelData = false;
	//			continue;
	//		}
	//		else if(LOAD_LEVELDATA(buffer[0])){
	//			//Adding 1 to accomindate for comma...
	//			u8 numStride = ::GetNumCharCount((u8*)&buffer[1]) + 1;

	//			levelWidth = std::stoi(&buffer[1]);
	//			levelHeight = std::stoi(&buffer[1 + numStride]);

	//			levelBuffer = (u8*)malloc(levelWidth * levelHeight);

	//			loadLevelData = true;
	//			continue;
	//		}
	//		else if(loadLevelData){
	//			//TODO: May need to put this elsewhere so it doesn't persist...
	//			static u16 levelIndex = 0;

	//			//FillBuffer((u8*)buffer, levelBuffer, levelIndex, levelWidth);

	//			continue;
	//		}

	//		unsigned char commaLen = FindChar(buffer, ',');

	//		static u8 texIndex = 0;

	//		//numTextures = buffer[1] - ASCII_ZERO;
	//		//	textureBuffer = (u8*)malloc(MAX_PATH_SIZE * numTextures);

	//		//Found textures...
	//		if(commaLen > 0){
	//			strcpy(path, buffer);
	//			path[commaLen - 1] = '\0';

	//			memcpy(&textureBuffer[texIndex], &path, MAX_PATH_SIZE);
	//			texIndex += MAX_PATH_SIZE - 1;
	//			
	//			continue;
	//		}

	//		//load textures...
	//		//string filePath = 
	//	}

	//	myfile.close();
	//}

	//else cout << "Unable to open file"; 
}

//unsigned char World::FindChar(const char* buffer, const char& c){
//	//TODO: Search for char c, if found return true...
//	char* value = (char*)buffer;
//	unsigned char len = 0;
//
//	while(value != '\0'){
//		++len;
//		if(*value == c){
//			return len;
//		}
//		++value;
//	}
//
//	return len = 0;
//}

//TODO: Add functionality later...
World::~World(){
	//delete plane;
	//plane = NULL;

	//delete cube;
	//cube = NULL;

	delete mesh;
	mesh = NULL;
}

void World::Update(const float& deltaTime){

	//plane->Update(deltaTime);
	//cube->Update(deltaTime);
	mesh->Update(deltaTime);
}

void World::Render(const Camera& camera){
	//plane->Render(camera);
	//cube->Render(camera);

	mesh->Render(camera);
}