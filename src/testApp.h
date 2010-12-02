#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxVectorMath.h"
#include "ofxKinectDataReader.h"
#include "dataContainer.h"
#include "ofxControlPanel.h"

class testApp : public ofBaseApp{

public:
	ofxKinectDataReader *loader;
	float * distancePixels;
	unsigned char * rgbPixels;
	
	static const int w = 640;
	static const int h = 480;
	
	//	vector <string> filenames;
	
	void setup();
	void update();
	void draw();
	void cleanUpScene();
	
	void setMovie(const char *filename);	
	void start();
	
	// key board & mouse
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button){
	}
	void mousePressed(int x, int y, int button){
	}
	
	void mouseReleased(int x, int y, int button){
	}
	void windowResized(int w, int h);
	
	
};

#endif
