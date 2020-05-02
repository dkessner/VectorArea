//
// ofApp.cpp
//


#include "ofApp.h"
#include "Pickable.hpp"


using namespace std;
using namespace glm;


void ofApp::setup()
{
    v.set(vec3(200.0, 50.0, 0));
    v.setPosition(3*ofGetWindowWidth()/4, ofGetWindowHeight()/2);

    w = make_shared<Vector>(100.0, 0, 0);
    w->setPosition(ofGetWindowWidth()/2, ofGetWindowHeight()/2);
    w->getPickableTail()->setActive(false);
    w->getPickableBody()->setActive(false);
}


void ofApp::update()
{
}



void ofApp::draw()
{
    ofBackground(0);

    ofSetColor(255);
    ofDrawBitmapString("Hello, world!", 50, 50);

    v.draw();
    w->draw();
}


void ofApp::mouseDragged(int x, int y, int button) {}
void ofApp::mousePressed(int x, int y, int button) {}
void ofApp::mouseReleased(int x, int y, int button) {}

void ofApp::keyPressed(int key){}
void ofApp::keyReleased(int key){}
void ofApp::mouseMoved(int x, int y ){}
void ofApp::mouseEntered(int x, int y){}
void ofApp::mouseExited(int x, int y){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){}

