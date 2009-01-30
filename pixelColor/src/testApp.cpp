#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){

	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(320,240);
    colorImg.allocate(320,240);
	bLearnBakground = true;
	threshold = 80;
	
	red = 0;
	green = 0;
	blue = 0;
	logo.loadImage("logo.gif");
}

//--------------------------------------------------------------
void testApp::update(){
	ofBackground(100,100,100);
    
    bool bNewFrame = false;
	

	vidGrabber.grabFrame();
	bNewFrame = vidGrabber.isFrameNew();
	colorImg.setFromPixels(vidGrabber.getPixels(), 320,240);
	
	
}

//--------------------------------------------------------------
void testApp::draw(){
	colorImg.draw(0,0);

	//ofSetColor(red, green, blue);
	//ofRect(400,300,30,30);
	ofSetColor(red, green, blue);
	logo.draw(300,300,325,300);
	ofSetColor(255, 255, 255);
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
	if(x < 320 && y < 240){
		pixels = colorImg.getPixels();
		int pixelImConcernedWith = (320  * y * 3) + (x * 3);
		red = (int)pixels[pixelImConcernedWith];
		green = (int) pixels[pixelImConcernedWith + 1];
		blue = (int) pixels[pixelImConcernedWith + 2];
	}
}	

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(){

}
