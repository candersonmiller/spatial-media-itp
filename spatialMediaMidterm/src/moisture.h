/*
 *  moisture.h
 *  openFrameworks
 *
 *  Created by C. Anderson Miller on 3/8/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofMain.h"
#include "ofAddons.h"
#include "globals.h"
#ifndef _MOISTURE
#define _MOISTURE



class moisture{
	
public:
	
	void init(float xValue);
	void update(int ofMillis);
	void draw();
	bool onScreen();
	void setGravity(float grav);
	float getGravity();
	void pause();
	void unpause();
	float getX();
	float getY();
	
	void obstacleAvoidance(int obstacleNumber, float slope);

private:
	
	bool allClear;
	void circle(float radius);
	float offset1;
	float offset2;
	float offset3;
	float uniqueVal;
	
	float size;
	
	int timeOffset;
	float gravity;
	int counter1;
	float xVal;
	float xOffset;
	float yVal;
	bool paused;
};

#endif
