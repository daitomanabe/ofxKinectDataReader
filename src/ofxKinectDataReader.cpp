#include "ofxKinectDataReader.h"
#include <stdio.h>

ofxKinectDataReader::ofxKinectDataReader(const char *filename) {
	char buf[256];
	sprintf(buf, "%s%s", ofToDataPath("./", true).c_str(), filename);
	rawFile = fopen(buf, "rb");
	if(rawFile != NULL) {
		cout << "ofxKinectDataReader::ofxKinectDataReader() | file open success. : " << buf << endl;
		fseek(rawFile, 0L, SEEK_END);
		maxFrame = ftell(rawFile) / sizeof(dataContainer);
		fseek(rawFile, 0L, SEEK_SET);
		
		container = new dataContainer[maxFrame];
		fread(container, sizeof(dataContainer), maxFrame, rawFile);
		
		relativeMaxClock = prevClock = maxClock = container[maxFrame - 1].stamp;
		
		open = true;
	} else {
		cout << "ofxKinectDataReader::ofxKinectDataReader() | file open error. : can't open " << buf << endl;
		open = false;
		memset(container, 0, sizeof(dataContainer) * DEPTH_LENGTH);
		maxClock = 1;
	}
	currentFrame = 0;
	distancePixels = container[currentFrame].distancePixels;
	rgbPixels = container[currentFrame].rgbPixels;
	isStarted = false;
	startClockOffset = (double)0;
}

bool ofxKinectDataReader::start() {
	if(open) {
		isStarted = true;
		startClockOffset = container[currentFrame].stamp + get_stamp_sec();
	}
	return isStarted;
}

bool ofxKinectDataReader::stop() {
	isStarted = false;
}

double ofxKinectDataReader::readTo() {
	if(open && isStarted) {
		double currentClock = get_stamp_sec() - startClockOffset;
		while(maxClock < currentClock) {
			currentClock -= maxClock;
		}
//			cout << maxFrame << ", " << currentFrame << ", " << maxClock << ", " << currentClock << endl;
		if(currentClock < prevClock) {
			currentFrame = 0;
		}
		while(container[currentFrame].stamp < currentClock) {
			currentFrame++;
			if(maxFrame - 1 <= currentFrame) {
				currentFrame = 0;
				break;
			}
		}
		distancePixels = container[currentFrame].distancePixels;
		rgbPixels = container[currentFrame].rgbPixels;
		
		prevClock = currentClock;
		return container[currentFrame].stamp;
	} else if(open) {
		distancePixels = container[currentFrame].distancePixels;
		rgbPixels = container[currentFrame].rgbPixels;
		prevClock = startClockOffset + container[currentFrame].stamp;
		return container[currentFrame].stamp;
	} else {
		return (double)0;
	}
}

void ofxKinectDataReader::shift(int ds) {
	double dClock = container[currentFrame].stamp;
	currentFrame = (maxFrame + currentFrame + ds) % maxFrame;
	startClockOffset += container[currentFrame].stamp - dClock;
	prevClock = get_stamp_sec() - startClockOffset;
	cout << "shift " << ds << "frame | now " << currentFrame << "frame." << endl;
}

void ofxKinectDataReader::asignDistancePixels(float ** _distancePixels) {
	*_distancePixels = distancePixels;
}

float *ofxKinectDataReader::getDistancePixels() {
	return distancePixels;
}

void ofxKinectDataReader::asignRgbPixels(unsigned char** _rgbPixels) {
	*_rgbPixels = rgbPixels;
}

unsigned char *ofxKinectDataReader::getRGBPixels() {
	return rgbPixels;
}



void ofxKinectDataReader::close() {
	if(open) {
		fclose(rawFile);
		delete [] container;
		open = false;
		cout << "ofxKinectDataReader::close() | success." << endl;
	} else {
		cout << "ofxKinectDataReader::close() | don't open file." << endl;
	}
}
