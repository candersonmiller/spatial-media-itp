/*
 *  obstacle.h
 *  openFrameworks
 *
 *  Created by C. Anderson Miller on 3/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofMain.h"
#include "ofAddons.h"
#include "globals.h"
#ifndef _OBSTACLE
#define _OBSTACLE



class obstacle{

	
public:
	void init(float x1, float y1, float x2 , float y2);
	int approaching(float x1, float y1);
	void setStart(float x1, float y1);
	void setEnd(float x2, float y2);
	float slope();
	void draw();
	
	
private:
	float xStart, yStart, xEnd, yEnd;
	

};

#endif