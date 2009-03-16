#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	
	
#ifdef _USE_LIVE_VIDEO
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(320,240);
#else
	vidPlayer.loadMovie("fingers.mov");
	vidPlayer.play();
#endif
	
    colorImg.allocate(320,240);
	grayImage.allocate(320,240);
	grayBg.allocate(320,240);
	grayDiff.allocate(320,240);
	
	bLearnBakground = true;
	isPaused = false;
	showCameraStuff = false;
	threshold = 24;
	
	
	//start drawing init stuff
	dropletNumber = 10;
	int bunchOfRandoms[30] = {749,
		12,
		398,
		80,
		437,
		644,
		190,
		671,
		483,
		489,
		70,
		136,
		202,
		647,
		500,
		683,
		424,
		587,
		488,
		284,
		583,
		621,
		87,
		342,
		483,
		615,
		330,
		165,
		253,
	279};
	for(int i = 0; i < dropletNumber; i++){
		droplets[i].init(bunchOfRandoms[i]);
	}
	test.init(200,300,500, 600);
	
	// doesn't work lineNumber0.init(750,250,630, 200);
	// plays wrong way lineNumber0.init(630, 250,750,200);
	// 
	// does work 
	//lineNumber0.init(630, 200,750,250);
	obstacleNumber = 6;
	lineNumber[0].init(100,1000, 100,100 );
	lineNumber[1].init(100,800, 00,700);
	lineNumber[5].init(100,800, 700,700);
	
	
	
	
	//around the circle
	lineNumber[2].init(640,600, 640,100); //through the circle
	lineNumber[3].init(640,430, 480, 530);
	lineNumber[4].init(640,430, 800, 530);
	
	//lineNumber[2].init(
}

//--------------------------------------------------------------
void testApp::update(){
	ofBackground(0,0,0);
    
    bool bNewFrame = false;
	
#ifdef _USE_LIVE_VIDEO
	vidGrabber.grabFrame();
	bNewFrame = vidGrabber.isFrameNew();
#else
	vidPlayer.idleMovie();
	bNewFrame = vidPlayer.isFrameNew();
#endif
	
	if (bNewFrame){
		
#ifdef _USE_LIVE_VIDEO
		colorImg.setFromPixels(vidGrabber.getPixels(), 320,240);
#else
		colorImg.setFromPixels(vidPlayer.getPixels(), 320,240);
#endif
		
        grayImage = colorImg;
		if (bLearnBakground == true){
			grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
			bLearnBakground = false;
		}
		
		// take the abs value of the difference between background and incoming and then threshold:
		grayDiff.absDiff(grayBg, grayImage);
		grayDiff.threshold(threshold);
		unsigned char* pixels = grayDiff.getPixels();
		int counterOfPixels = 0;
		float pixlTotal = 0;
		int activePixels = 0;
		int yValueToMonitor = 155;
		for(int i = 0; i < 320 * 240; i++){
			if(i > yValueToMonitor * 320 + 10 && i < yValueToMonitor * 320 + 10 + 200){
				counterOfPixels++;
				if(pixels[i] == 255){
					//printf("counterOfPixels %d\n", counterOfPixels);
					pixlTotal += counterOfPixels;
					activePixels++;
				}
			}
		}
		if(activePixels > 5){
			activePoint = (pixlTotal/activePixels)/200;
			printf("active point: %f\n", activePoint);
		}else{
			activePoint = -1;
		}
		
		//200 pixels long, starting at x position 10, going to 210
		//looking at Y position 152
		
		// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
		contourFinder.findContours(grayDiff, 20, (340*240)/3, 10, true);	// find holes
	}
	
	//printf("%f \n", ofGetFrameRate());
	
	
	
	if(activePoint){
		bool makeNew = true;
		for(int i = 0; i < generatedObjects.size(); i++){
			if(generatedObjects[i].getX() - (activePoint * 1024) < 5 && generatedObjects[i].getX() - (activePoint * 1024) > -5){
				makeNew = false;
			}
		}
		
		if(makeNew){
			moisture theNewOne;
			generatedObjects.push_back(theNewOne);
			generatedObjects[generatedObjects.size()-1].init(activePoint * 1024);
		}
	}

	if(!isPaused){
	for(int i = 0; i < dropletNumber; i++){
		if(ofGetElapsedTimeMillis() <  i * 1000){
			//do nothing
		}else{
			droplets[i].update(ofGetElapsedTimeMillis());
			
		}
		//droplets[i].obstacleAvoidance(test.approaching(droplets[i].getX(), droplets[i].getY()), test.slope());
		for(int k = 0; k < obstacleNumber; k++){
			droplets[i].obstacleAvoidance(lineNumber[k].approaching(droplets[i].getX(), droplets[i].getY()), lineNumber[k].slope());
		}
		
	}
		
		
		for(int i = 0; i < generatedObjects.size(); i++){
			generatedObjects[i].update(ofGetElapsedTimeMillis());
			for(int k = 0; k < obstacleNumber; k++){
				generatedObjects[i].obstacleAvoidance(lineNumber[k].approaching(generatedObjects[i].getX(), generatedObjects[i].getY()), lineNumber[k].slope());
			}
			
		}
	
	if(! generatedObjects.empty() ){
		for(int i = 0; i < generatedObjects.size(); i++){
			if(generatedObjects[i].getY() > 800){
				generatedObjects.erase( generatedObjects.begin() + i);
			}
		}
	}
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(0, 0, 0);
	ofSetColor(0, 0, 0);
	ofRect(0,0,1400,1400);
	for(int i = 0; i < dropletNumber; i++){
		droplets[i].draw();
	}
	
	//test.draw();
	if(! generatedObjects.empty() ){
		for(int i = 0; i < generatedObjects.size(); i++){
			generatedObjects[i].draw();
		}
	}
	
	
	for(int i =0; i < obstacleNumber; i++){
		//lineNumber[i].draw();
	}

	
	if(showCameraStuff){
	// draw the incoming, the grayscale, the bg and the thresholded difference
	//ofSetColor(0xffffff);
	colorImg.draw(20,20);	
	grayImage.draw(360,20);
	grayBg.draw(20,280);
	grayDiff.draw(360,280);
		ofSetColor(255, 255, 255);
		ofLine(0, 432, 2000, 432);
		ofSetColor(255, 0, 0);
		ofLine(370, 0, 370, 1000);
		ofLine(570, 0, 570, 1000);
		
	// then draw the contours:
	
	ofFill();
	ofSetColor(0x333333);
	ofRect(360,540,320,240);
	ofSetColor(0xffffff);
    
	// we could draw the whole contour finder
	//contourFinder.draw(360,540);
	
	// or, instead we can draw each blob individually,
	// this is how to get access to them:
    for (int i = 0; i < contourFinder.nBlobs; i++){
        contourFinder.blobs[i].draw(360,540);
    }
	
	// finally, a report:
	
	ofSetColor(0xffffff);
	char reportStr[1024];
	sprintf(reportStr, "bg subtraction and blob detection\npress ' ' to capture bg\nthreshold %i (press: +/-)\nnum blobs found %i", threshold, contourFinder.nBlobs);
	ofDrawBitmapString(reportStr, 20, 600);
	}
	
	
	ofSetColor(0, 0, 0);
	ofFill();
	ofRect(950, 0, 1000,1000);
	ofFill();
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
	switch (key){
		case ' ':
			bLearnBakground = true;
			break;
		case '+':
			threshold ++;
			if (threshold > 255) threshold = 255;
			break;
		case '-':
			threshold --;
			if (threshold < 0) threshold = 0;
			break;
		case 'c':
			if(showCameraStuff){
				showCameraStuff = false;
			}else{
				showCameraStuff = true;
			}
			break;
		case 'p':
			if(isPaused){
				for(int i = 0; i < 30; i++){
					droplets[i].unpause();
				}
				isPaused = false;
			}else{
				for(int i = 0; i < 30; i++){
					droplets[i].pause();
				}
				isPaused = true;
			}
	}
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
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
