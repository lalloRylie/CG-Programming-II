#include "Application.h"

#pragma once

class Object{

	public:
		Object();

		virtual ~Object();
		virtual void Update(const float& deltaTime);
		virtual void Render(const Camera& camera);

		void SetPosition(vec3 position);
		void SetScale(vec3 scale);

		vec3 GetPosition(), position;
		float GetLeftX();
		float GetRightX();
		float GetTopY();
		float GetBottomY();

		void SaveObjectState(char *message = "Saved Object State");
		void LoadObjectState(char *message = "Loaded Object State");
		GLuint LoadBMP(const char * imagepath), textureID;

	protected:
		void BuildTriangles(const GLuint& perRow, const GLuint& perColumn);
		void BuildTriangleStrip(const GLuint& perRow, const GLuint& perColumn);
		float rotAngle, rotSpeed;
		Object* objectState;
		vec3 scale;
		GLuint numUVs, numIndices, renderMode, vertexBufferID, uvID, normID;

	private:
		void LoadTriangles(GLfloat *vertices, GLfloat *uvs);
		float leftX, rightX, topY, bottomY;
		mat4 BeforeRender();
};