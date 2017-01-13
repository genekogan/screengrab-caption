#pragma once

#include "ofMain.h"

#include "ofxScreenGrab.h"
#include "ofxDarknet.h"

class ofApp : public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();
    
    ofxDarknet darknet;
    vector<detected_object> detections;
    ofxScreenGrab grabber;
    ofPixels pixels;
};
