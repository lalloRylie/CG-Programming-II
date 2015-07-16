#include "Application.h"
#include "Object.h"

#pragma once

class Cube : public Object{

	public:
		Cube();
		virtual ~Cube();

	private:
		void BuildCube();
		void RotateCube();
};