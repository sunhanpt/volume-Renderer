#include "MouseHistory.h"

float MouseHistory::MouseMotionVelocityX()
{
	// Warning! Time stamp didn't really work! It's because in a second, there is no time difference in time_t data structure.
	// I guess millisecond unit might work. but I am not sure how to do it yet.
	int differenceBtwCurrentAndLastIndex = 0;
	for(int i = 0 ; i < MOUSE_HISTORY_SIZE ; i++) {
		int index = (currentIndexX - i < 0) ? currentIndexX - i + MOUSE_HISTORY_SIZE : currentIndexX - i;
		if(historyX[index] == -100) {
			differenceBtwCurrentAndLastIndex = i;
			break;
		}
	}
	float velocityX;
	if(differenceBtwCurrentAndLastIndex == 0)
		return 0.0f;
	if(currentIndexX - differenceBtwCurrentAndLastIndex + 1 < 0)
		velocityX = float(historyX[currentIndexX] - historyX[currentIndexX - differenceBtwCurrentAndLastIndex + 1 + MOUSE_HISTORY_SIZE]) / (differenceBtwCurrentAndLastIndex + 1);
	else
		velocityX = float(historyX[currentIndexX] - historyX[currentIndexX - differenceBtwCurrentAndLastIndex + 1]) / (differenceBtwCurrentAndLastIndex + 1);
	return velocityX;
	/*
	int tmpX = (currentIndexX - 9) % MOUSE_HISTORY_SIZE;
	if(tmpX < 0) tmpX += this ->MOUSE_HISTORY_SIZE;
	float velocityX;
	if(historyX[tmpX] == -100)
		return 0.0f;
	velocityX = historyX[currentIndexX] - historyX[tmpX];
	return velocityX;
	*/
}

void MouseHistory::SetGlobalAngles()
{
	globalAngleX = MouseMotionVelocityX(); globalAngleY = MouseMotionVelocityY();
}


float MouseHistory::MouseMotionVelocityY()
{
	// Warning! Time stamp didn't really work! It's because in a second, there is no time difference in time_t data structure.
	// I guess millisecond unit might work. but I am not sure how to do it yet.
	int differenceBtwCurrentAndLastIndex = 0;
	for(int i = 0 ; i < MOUSE_HISTORY_SIZE ; i++) {
		int index = (currentIndexX - i < 0) ? currentIndexY - i + MOUSE_HISTORY_SIZE : currentIndexY - i;
		if(historyY[index] == -100) {
			differenceBtwCurrentAndLastIndex = i;
			break;
		}
	}
	float velocityY;
	if(differenceBtwCurrentAndLastIndex == 0)
		return 0.0f;
	if(currentIndexY - differenceBtwCurrentAndLastIndex + 1 < 0)
		velocityY = float(historyY[currentIndexY] - historyY[currentIndexY - differenceBtwCurrentAndLastIndex + 1 + MOUSE_HISTORY_SIZE]) / (differenceBtwCurrentAndLastIndex + 1);
	else
		velocityY = float(historyY[currentIndexY] - historyY[currentIndexY - differenceBtwCurrentAndLastIndex + 1]) / (differenceBtwCurrentAndLastIndex + 1);
	return velocityY;
}