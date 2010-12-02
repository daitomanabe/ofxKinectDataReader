#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	setMovie("rec30fps_12_02_14-33-33-1.knct");
	start();
	
}


//--------------------------------------------------------------
void testApp::update(){
	
	loader->readTo();
	distancePixels = loader->getDistancePixels();
	rgbPixels = loader->getRGBPixels();
}

//--------------------------------------------------------------
void testApp::draw(){	
	ofBackground(0, 0, 0);
	glBegin(GL_POINTS);	
	//distance
	for(int x = 0; x < w; x++) {
		for(int y = 0; y < h; y++) {
			int n = x + y * w;
			float pz = ofMap(distancePixels[n], 0, 1000, 0, 255);
			ofSetColor(pz, pz, pz);
			glVertex3f(x, y, 0);
		}
	}		
	glEnd();
	
	ofSetColor(255, 255, 255);
	ofDrawBitmapString("distance", 10, h+40);
	
	//rgb
	glBegin(GL_POINTS);		
	for(int x = 0; x < w; x++) {
		for(int y = 0; y < h; y++) {
			int n = x + y * w;
			ofSetColor(rgbPixels[3 * n], rgbPixels[3 * n + 1], rgbPixels[3 * n + 2]);
			glVertex3f(w + x, y, 0);
		}
	}
	glEnd();
	
	cout << w << endl;
	ofSetColor(255, 255, 255);	
	ofDrawBitmapString("rgb", w+10, h+40);	
	
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}


//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

void testApp::setMovie(const char *filename) {
	loader = new ofxKinectDataReader(filename);
}

void testApp::start() {
	loader->start();
}
