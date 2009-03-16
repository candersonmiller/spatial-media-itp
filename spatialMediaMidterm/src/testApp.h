#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"

#define OF_ADDON_USING_OFXOPENCV
#define _USE_LIVE_VIDEO

#include "ofAddons.h"


#include "moisture.h"
#include "obstacle.h"
#include <vector>
//#define _USE_LIVE_VIDEO		// uncomment this to use a live camera
								// otherwise, we'll use a movie file

#define width 1024
#define height 768


class testApp : public ofSimpleApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();

        #ifdef _USE_LIVE_VIDEO
		  ofVideoGrabber 		vidGrabber;
		#else
		  ofVideoPlayer 		vidPlayer;
		#endif
        
        ofxCvColorImage		colorImg;
        
        ofxCvGrayscaleImage 	grayImage;
		ofxCvGrayscaleImage 	grayBg;
		ofxCvGrayscaleImage 	grayDiff;
		ofImage					forDisplay;
        ofxCvContourFinder 	contourFinder;

		int 				threshold;
		bool				bLearnBakground;
	bool				showCameraStuff;
	bool				isPaused;
		
private:
	float offset1;
	float offset2;
	float offset3;
	float activePoint;
	int counter1;
	int dropletNumber;
	moisture droplet;
	moisture droplet1;
	moisture droplets[30];
	obstacle test;	
	obstacle lineNumber0;
	obstacle lineNumber1;
	int obstacleNumber;
	obstacle lineNumber[30];
	vector<moisture> generatedObjects;
};

#endif
