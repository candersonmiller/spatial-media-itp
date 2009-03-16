/*
 *  moisture.cpp
 *  openFrameworks
 *
 *  Created by C. Anderson Miller on 3/8/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "moisture.h"

//-----------------------------------------------------------------

void moisture::init(float xValue){
	
	offset1 = 0;
	offset2 = 0;
	offset3 = 0;
	counter1 = 0;
	xVal = xValue;
	size = 0.5;
	
	gravity = 120;
	//srand(time(0));
	//ofSeedRandom(rand() + xValue);
	//xVal = ofRandom(0, 800);
	uniqueVal = random() % 100;
	//printf("%f\n",uniqueVal);
	timeOffset = random() % 300;
	//printf("%f\n", uniqueVal);
	
	paused = false;
	
	allClear = true;
	xOffset = 0;
}

//-----------------------------------------------------------------
void moisture::update(int ofMillis){
	if(!paused){
		ofMillis += timeOffset;
		counter1++;
		offset1 = sin(ofMillis / uniqueVal);
		offset2 = cos(ofMillis  / uniqueVal);
	}
	
	
	float percentIncrease = (float)(counter1/5 % 1000)/1000;  //attempt at creating a 'T' for x = 1/2 a t^2
	percentIncrease = (.5 * gravity * pow(percentIncrease,2));
	
	yVal = (((counter1)/5) % 1000) * (1+ percentIncrease);
	
	if(yVal > 1100){
		xOffset = 0;
		counter1 = 0;
	}
}

//-----------------------------------------------------------------
void moisture::draw(){
	
	glPushMatrix();
	bool side = true;
	float xTranslation = xVal + xOffset;
	float yTranslation = height - yVal;
	if(!side){
		glTranslated(xTranslation, 000, 0);
		glTranslated(0, yTranslation  , 0);
	
	}else{
		//glTranslated((height - yVal) * (width/height) ,0, 0);
		//glTranslated(0, ((width - (xVal + xOffset)) * width)/height, 0);
		
		glTranslated(0, height - ((xTranslation * height)/width),0);
		glTranslated( ((yTranslation * width)/height), 0,0);
				
		//float widthRatio = height/width;
		//float heightRatio = width/height;
		//glTranslated(width - ( (height - yVal) * heightRatio), - xVal, 0);
		
		
		//glVertex3f(xStart,(height - yStart),0);
		//glVertex3f(xEnd, (height - yEnd), 0);
		//glEnd();
		//}else{
		//glColor3f(1,1,1);
		//glBegin(GL_LINES);
		//glVertex3f( width - ( yStart) * height/width, height - ( xStart * height/width),0);
		//glVertex3f( width - (yEnd) * height/width,  height - (xEnd * height/width),0);
	}

	

	
	glColor3f(0,0,0);
	
	glPushMatrix();
	glTranslated(- offset1 * 5, - offset2 * 5, 0);
	circle(25 * size);
	glPopMatrix();
	
	glTranslated(15 * size,2 * size,0);
	
	glPushMatrix();
	glTranslated( offset1 * 5 * size, offset2 * 5 * size, 0);
	circle(25 * size);
	glPopMatrix();
	
	glTranslated(-8 * size, 8 * size, 0);
	
	
	glPushMatrix();
	glTranslated( offset3 * 5 * size, -offset2 * 5 * size, 0);
	circle(25 * size);
	glPopMatrix();
	
	glTranslated(5 * size, -8 * size, 0);
	
	glPushMatrix();
	glTranslated( -offset1 * 5 * size, offset2 * 5 * size, 0);
	circle(25 * size);
	glPopMatrix();
	
	glPopMatrix();
	
}

//----------------------------------------------------------------
bool moisture::onScreen(){
	
	
}


void moisture::pause(){
	paused = true;
}

void moisture::unpause(){
	paused = false;
}


void moisture::circle(float radius){
	float x,y;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f,1.0f,1.0f);
	
	x = (float)radius * cos(359 * PI/180.0f);
	y = (float)radius * sin(359 * PI/180.0f);
	for(int j = 0; j < 360; j++)
	{
		glVertex2f(x,y);
		x = (float)radius * cos(j * PI/180.0f);
		y = (float)radius * sin(j * PI/180.0f);
		glVertex2f(x,y);
	}
	glEnd();
}

//----------------------------------------------------------------
void moisture::setGravity(float grav){
	gravity = grav;
}



//----------------------------------------------------------------
float moisture::getGravity(){
	return gravity;
}


float moisture::getX(){
	return xVal + xOffset;
}

float moisture::getY(){
	return yVal;
}


void moisture::obstacleAvoidance(int obstacleNumber, float slope ){
	//if(x) //be aware
	if(obstacleNumber && obstacleNumber % 2 == 1){
		allClear = false;
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
		switch(obstacleNumber){
			case 1:
				xOffset -= slope; //less
				break;
			case 3:
				xOffset -=  slope;
				break;
			case 5:
				xOffset +=  slope;
				break;
			case 7:
				xOffset +=  slope;
		}
		//xOffset += 0.1;
	}else{
		allClear = true;
	}
}



