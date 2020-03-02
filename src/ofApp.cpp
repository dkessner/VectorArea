//
// ofApp.cpp
//


#include "ofApp.h"


void ofApp::setup()
{
    arrow.setMode(OF_PRIMITIVE_LINE_STRIP);
    arrow.addVertex(ofPoint(50, 50));
    arrow.addVertex(ofPoint(100, 100));

    arrow.addColor(ofColor::white);
    arrow.addColor(ofColor::white);
}


void ofApp::update()
{
    arrow.setVertex(1, ofPoint(ofGetMouseX(), ofGetMouseY()));
}


void ofApp::draw()
{
    ofBackground(0);
    ofSetColor(255);
    ofDrawBitmapString("Hello, world!", 50, 50);

    arrow.draw();
}


void ofApp::keyPressed(int key){}
void ofApp::keyReleased(int key){}
void ofApp::mouseMoved(int x, int y ){}
void ofApp::mouseDragged(int x, int y, int button){}
void ofApp::mousePressed(int x, int y, int button){}
void ofApp::mouseReleased(int x, int y, int button){}
void ofApp::mouseEntered(int x, int y){}
void ofApp::mouseExited(int x, int y){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){}

