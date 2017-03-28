#pragma once
#include <iostream>
#include <GL/glut.h>
#include "MouseHistory.h"

using namespace std;

class UserInput 
{
private:
	bool bShiftDown;
	int lastX, lastY, buttonDown;
	MouseHistory mouseHistory;
	double angleX, angleY, angleZ;
	double positionX, positionY;
	double positionZ;
	double distanceFromObj;

public:
	UserInput(float * viewPosition);
	void Keyboard(unsigned char key, int x, int y);
	void Mouse(int button, int state, int x, int y);
	void MouseMotion(int x, int y);
	~UserInput(void);

	// UpdateGlobalRotationAngle
	void UpdateGlobalRotation(void);

	//Get Set functions
	inline double GetAngleX() {
		return angleX;
	}
	inline double GetAngleY() {
		return angleY;
	}
	inline double GetAngleZ() {
		return angleZ;
	}
	inline double GetViewDistance() {
		return distanceFromObj;
	}
};

