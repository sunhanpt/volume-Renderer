#include "UserInput.h"

UserInput::UserInput(float * viewPosition)
	: lastX(-1), lastY(-1), buttonDown(-1), angleX(0.0), angleY(0.0), angleZ(0.0)
	, positionX(0.0f), positionY(0.0f), positionZ(-4.0f), bShiftDown(false)//, globalAngleX(0.0), globalAngleY(0.0)
{
	distanceFromObj = viewPosition[0] * viewPosition[0] + viewPosition[1] * viewPosition[1] + viewPosition[2] * viewPosition[2];
	distanceFromObj = sqrt(distanceFromObj);
}

UserInput::~UserInput(void)
{
}

void UserInput::UpdateGlobalRotation(void){
	angleY -= mouseHistory.GetGlobalAngleX() * 0.1;
	angleX -= mouseHistory.GetGlobalAngleY() * 0.1;
}

void UserInput::Mouse(int button, int state, int x, int y)
{
	// if it is when users let go of the left button while motioning, then objects should keep rotating.
    // Record the mouse position when a button is pressed.
	if(button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		// could Use Visitor pattern.
		// check the prev history and get the velocity of mouse cursor motion/move.
		mouseHistory.SetGlobalAngles();
	}
	else {
		mouseHistory.InitializeHistory();
	}
    lastX = x;
    lastY = y;
    buttonDown = button;
    bShiftDown = (glutGetModifiers() == GLUT_ACTIVE_SHIFT);
}

void UserInput::MouseMotion(int x, int y)
{
    int deltaX = x - lastX;
    int deltaY = y - lastY;

    switch(buttonDown) {
    case GLUT_LEFT_BUTTON:                  // Rotate in the x-y plane
        angleX -= deltaY;
        angleY -= deltaX;
		mouseHistory.NewHistory(x, y);
        break;
    case GLUT_RIGHT_BUTTON:                 // Rotate in the x-z plane
//        angleX -= deltaY;
//        angleZ -= deltaX;
		distanceFromObj -= deltaY * 0.1;
        break;
    case GLUT_MIDDLE_BUTTON:
        if (bShiftDown) {                  // Move in and out
            positionZ -= deltaY * 0.1;
        } else {                            // Move left and right
            positionX -= deltaX * 0.1;
            positionY += deltaY * 0.1;
        }
        break;
    }
    lastX = x;
    lastY = y;
}

void UserInput::Keyboard(unsigned char key, int x, int y)
{
	// Exit on escape.
    if (key == 27) exit(0);
}

