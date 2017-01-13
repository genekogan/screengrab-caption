#include "ofApp.h"

void ofApp::setup()
{
    //ofSetWindowShape(1440, 810);
    ofSetFullscreen(true);
    
    std::string datacfg = "/Users/gene/Code/of_v0.9.6_osx_release/apps/myApps/testYolo/bin/cfg/COCO_COPY_TEMP.data";
    std::string cfgfile = ofToDataPath( "cfg/yolo.cfg" );
    std::string weightfile = "/Users/gene/Code/of_v0.9.6_osx_release/apps/myApps/testYolo/bin/data/yolo.weights";
    std::string nameslist = ofToDataPath( "cfg/coco.list" );
    darknet.init( cfgfile, weightfile, datacfg, nameslist );

    grabber.setup(ofGetWidth(), ofGetHeight(), true);
}

void ofApp::update()
{
    float thresh = ofMap( ofGetMouseX(), 0, ofGetWidth(), 0, 1 );

    grabber.grabScreen(0, 0);
    grabber.getTextureReference().readToPixels(pixels);
    pixels.resize(ofGetWidth(), ofGetHeight());
    
    detections = darknet.yolo(pixels, thresh);
}

void ofApp::draw()
{
    ofSetColor(255);
    grabber.draw(0, 0);
    for(detected_object d : detections ){
        ofSetColor( d.color );
        glLineWidth( ofMap( d.probability, 0, 1, 0, 8 ) );
        ofNoFill();
        ofDrawRectangle( d.rect );
        ofDrawBitmapStringHighlight( d.label + ": " + ofToString(d.probability), d.rect.x, d.rect.y + 20 );
    }
}