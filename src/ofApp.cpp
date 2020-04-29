//
// ofApp.cpp
//


#include "ofApp.h"
#include "Pickable.hpp"


using namespace std;
using namespace glm;


namespace {

float x = 200;
float y = 400;


void testCallback(const glm::vec3& movement)
{
    x += movement.x;
    y += movement.y;
}

}


void ofApp::setup()
{
    v.set(vec3(200.0, 50.0, 0));
    v.move(vec3(3*ofGetWindowWidth()/4, ofGetWindowHeight()/2, 0.0));

    auto p = PickableCircle::create(500, 400);
    pickables.push_back(p);
    p->registerCallback(testCallback);

    p = PickableCircle::create(500, 500);
    pickables.push_back(p);
    p->registerCallback(testCallback);
}


void ofApp::update()
{
}



namespace {

void tutorial2D()
{
    ofNoFill();
    ofSetColor(255);
    ofSetLineWidth(1);
    ofDrawRectangle(64, 64, 64, 64);
    ofDrawCircle(192, 96, 32);
    ofDrawLine(256, 64, 320, 128);
    ofDrawTriangle(352, 128, 384, 64, 416, 128);
    ofDrawEllipse(512, 96, 128, 64);
    ofDrawRectRounded(608, 64, 64, 64, 9);
    ofDrawBezier(704, 64, 736, 128, 768, 160, 800, 64);
}

void tutorial3D()
{
    ofNoFill();
    ofSetLineWidth(1);
    ofSetColor(255);
    ofDrawBox(64, 256, 0, 64, 64, 64);
    ofDrawCone(160, 256, 0, 32, 128);
    ofDrawCylinder(256, 256, 32, 128);
    ofDrawIcoSphere(352, 256, 0, 32);
    ofDrawPlane(448, 256, 64, 64);
    ofDrawSphere(544, 256, 32);
}

} // namespace




void ofApp::draw()
{
    ofBackground(0);

    ofSetColor(255);
    ofDrawBitmapString("Hello, world!", 50, 50);

    v.draw();

    for (auto p : pickables)
        p->draw();

    ofFill();
    ofSetLineWidth(1);
    ofSetColor(0, 255, 0);
    ofDrawCircle(x, y, 20);

    //tutorial2D();
    tutorial3D();
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

