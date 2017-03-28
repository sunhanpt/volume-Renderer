#pragma once

#include <iostream>
#include <ctime>
using namespace std;

class MouseHistory
{
	double globalAngleX, globalAngleY;
	static const int MOUSE_HISTORY_SIZE = 10;
	int * historyX;
	int * historyY;
	time_t *timestampHistory;
	int currentIndexX, currentIndexY;
public:
	MouseHistory() {
		historyX = new int[MOUSE_HISTORY_SIZE];
		historyY = new int[MOUSE_HISTORY_SIZE];
		timestampHistory = new time_t[MOUSE_HISTORY_SIZE];
		for(int i = 0 ; i < MOUSE_HISTORY_SIZE ; i++) {
			historyX[i] = -100;
			historyY[i] = -100;
			timestampHistory[i] = -1;
		}
		currentIndexX = -1;
		currentIndexY = -1;
		globalAngleX = globalAngleY = 0.0;
	}
	~MouseHistory() {
		delete [] historyX;
		delete [] historyY;
	}
	void InitializeHistory() {
		for(int i = 0 ; i < MOUSE_HISTORY_SIZE ; i++) {
			historyX[i] = -100;
			historyY[i] = -100;
		}
		currentIndexX = -1;
		currentIndexY = -1;
		globalAngleX = globalAngleY = 0.0;
	}
	float MouseMotionVelocityX();
	float MouseMotionVelocityY();
	void SetGlobalAngles();

	// Get Func
	inline double GetGlobalAngleX() {
		return globalAngleX;
	}
	inline double GetGlobalAngleY() {
		return globalAngleY;
	}
public:
	void NewHistory(int x, int y) {
		if(currentIndexX == MOUSE_HISTORY_SIZE - 1) currentIndexX = -1;
		if(currentIndexY == MOUSE_HISTORY_SIZE - 1) currentIndexY = -1;
		historyX[++currentIndexX] = x;
		historyY[++currentIndexY] = y;
		time(&timestampHistory[currentIndexX]);
	}
};
