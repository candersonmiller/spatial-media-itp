/*
 *  obstacle.cpp
 *  openFrameworks
 *
 *  Created by C. Anderson Miller on 3/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "obstacle.h"


void obstacle::init(float x1, float y1, float x2, float y2){
	xStart = x1;
	yStart = y1;
	xEnd = x2;
	yEnd = y2;
	
}

// give me a point that you're at, and I will tell you if you should even worry
// if you should worry, I'll tell you what direction to slip, and how fast
int obstacle::approaching(float x1, float y1){
	if((x1 > xStart && x1 < xEnd) || (x1 < xStart && x1 > xEnd)){
		
		
		// doesn't work 
		// plays wrong way lineNumber0.init(630, 250,750,200);
		//					lineNumber0.init(750,250,630, 200);
		// does work 
		
		// it is in the 'target area' and should be prepared because it will hit at some point
		
		
		//check for slope and see how urgent the matter is
		float slop = slope();
		
		//now I need to check for whether it's going to hit SOON
		
		if((xStart > xEnd && yStart < yEnd)|| (xEnd > xStart && yEnd < yStart)){  //we need to go left
			if(slop > 2){
				//slow slope and we're in it
				
				if((y1 > yStart && y1 < yEnd) || (y1 < yStart && y1 > yEnd)){
					return 1;
				}else{
					return 2;
				}
				
				//slow slope and we're not in it
				
			}else{
				//fast slope and we're in it
				
				
				//fast slope and we're not in it
				
				if((y1 > yStart && y1 < yEnd) || (y1 < yStart && y1 > yEnd)){
					return 3;
				}else{
					return 4;
				}
			}
			
			
		}else{
			if(slop > 2){
				//slow slope and we're in it
				
				if((y1 > yStart && y1 < yEnd) || (y1 < yStart && y1 > yEnd)){
					return 5;
				}else{
					return 6;
				}
				
				//slow slope and we're not in it
				
			}else{
				//fast slope and we're in it
				
				
				//fast slope and we're not in it
				
				if((y1 > yStart && y1 < yEnd) || (y1 < yStart && y1 > yEnd)){
					return 7;
				}else{
					return 8;
				}
			}
			
			//if(x) //be aware
			//if x < 5 move left
			//    case 1: slow slope, we're in it
			//    case 2: slow slope, we're fine
			//    case 3: fast slope, we're in it
			//    case 4: fast slope, we're fine
			//if x > 4 move right
			//    case 5: slow slope, we're in it
			//    case 6: slow slope, we're fine
			//    case 7: fast slope, we're in it
			//    case 8: fast slope, we're fine
			//
			// slow down y movement a bunch on the case of 1 3 5 7
			// move slow on 1 5
			// move fast on 3 7
		}
		//case 1, start moving right slow
		
		//if it's a steep slope, move right slow
		//case 2, stop moving and slip right
		//if it's a shallow slope, move right slow
		//case 3, start moving left slow
		//if it's a steep slope move left slow
		//case 4, stop moving and slip left
		//if it's a shallow slope, move left fast
		
	}else{
		return 0;
	}	
}


float obstacle::slope(){
	float xDiff = xStart - xEnd;
	if(xDiff < 0) xDiff *= -1;
	float yDiff = yStart - yEnd;
	if(yDiff < 0) yDiff *= -1;
	return xDiff/yDiff;
}

void obstacle::setStart(float x1, float y1){
	xStart = x1;
	yStart = y1;
	
}


void obstacle::setEnd(float x2, float y2){
	
	xEnd = x2;
	yEnd = y2;
}

void obstacle::draw(){
	bool side = true;
	if(!side){
		glColor3f(1,1,1);
		glBegin(GL_LINES);
		glVertex3f(xStart,(height - yStart),0);
		glVertex3f(xEnd, (height - yEnd), 0);
		glEnd();
	}else{
		glColor3f(1,1,1);
		glBegin(GL_LINES);
		glVertex3f( width - ( yStart) * width/height, height - ( xStart * height/width),0);
		glVertex3f( width - (yEnd) * width/height,  height - (xEnd * height/width),0);
		glEnd();
	}
	
	
	
	//printf("obstacle y value %f\n", yStart);
}


/*
 int approaching(float x1, float y1);
 void setStart(float x1, float y1);
 void setEnd(float x2, float y2);
 void draw();
 
 
 */