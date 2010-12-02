#pragma once

#include "ofMain.h"
#include "dataContainer.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

class ofxKinectDataReader {
	private :
	int maxFrame;
	FILE *rawFile;
	dataContainer *container;
	double sec_to_max_stamp;
	int currentFrame;
	double maxClock;
	double relativeMaxClock;
	double startClockOffset;
	double prevClock;
	
//	float *points;
//	unsigned char *brightness;
//  wunsigned char * depthPixels;
	float * distancePixels;
	unsigned char * rgbPixels;
	
public :
	bool open;
	bool isStarted;
	ofxKinectDataReader(const char *filename);
	bool start();
	bool stop();
	double readTo();
	void shift(int ds);
	
	void asignDistancePixels(float** _distancePixels);
	float * getDistancePixels();
	void asignRgbPixels(unsigned char** _rgbPixels);
	unsigned char * getRGBPixels();
	
	void close();
	void printStamp() {
		cout << container[currentFrame].stamp << endl;
	}
};