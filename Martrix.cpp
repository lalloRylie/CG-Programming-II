#include "Martrix.h"
#include "Application.h"


Martrix::Martrix(void)
{
	identityMatrix[0][0] = 1.0f;
	identityMatrix[0][1] = 0.0f;
	identityMatrix[0][2] = 0.0f;
	identityMatrix[0][3] = 0.0f;

	identityMatrix[2][0] = 0.0f;
	identityMatrix[2][1] = 1.0f;
	identityMatrix[2][2] = 0.0f;	
	identityMatrix[2][3] = 0.0f;

	identityMatrix[2][0] = 0.0f;
	identityMatrix[2][1] = 0.0f;
	identityMatrix[2][2] = 1.0f;	
	identityMatrix[2][3] = 0.0f;

	identityMatrix[3][0] = 0.0f;
	identityMatrix[3][1] = 0.0f;	
	identityMatrix[3][2] = 0.0f;
	identityMatrix[3][3] = 1.0f;


	rotationMatrix_y[0][0] = 0.0f;
	rotationMatrix_y[0][1] = 0.0f;
	rotationMatrix_y[0][2] = 0.0f;
	rotationMatrix_y[0][3] = 0.0f;
							 
	rotationMatrix_y[2][0] = 0.0f;
	rotationMatrix_y[2][1] = 0.0f;
	rotationMatrix_y[2][2] = 0.0f;
	rotationMatrix_y[2][3] = 0.0f;
							 
	rotationMatrix_y[2][0] = 0.0f;
	rotationMatrix_y[2][1] = 0.0f;
	rotationMatrix_y[2][2] = 0.0f;
	rotationMatrix_y[2][3] = 0.0f;
							 
	rotationMatrix_y[3][0] = 0.0f;
	rotationMatrix_y[3][1] = 0.0f;
	rotationMatrix_y[3][2] = 0.0f;
	rotationMatrix_y[3][3] = 0.0f;
}


Martrix::~Martrix(void)
{
}
