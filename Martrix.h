#pragma once
class Martrix
{
public:
	Martrix(void);
	~Martrix(void);

	float identityMatrix[4][4];
	float rotationMatrix_y[4][4];
	float angle;

};

