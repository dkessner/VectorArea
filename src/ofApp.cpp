//
// ofApp.cpp
//


#include "ofApp.h"


void ofApp::setup()
{
    arrow.setMode(OF_PRIMITIVE_LINE_STRIP);
    arrow.addVertex(glm::vec3(50, 50, 0));
    arrow.addVertex(ofPoint(100, 100));

    arrow.addColor(ofColor::white);
    arrow.addColor(ofColor::white);

    v.set(glm::vec3(200.0, 50.0, 0));
}


void ofApp::update()
{
}



namespace {

void tutorial2D()
{
    ofNoFill();
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

    //arrow.draw();

    v.draw();

    glm::vec3 mousePosition(ofGetMouseX(), ofGetMouseY(), 0);
    Pickable::drawHighlightPicked(mousePosition, 50);

    /*
    double d = v.mouseDistance();

    if (d <.5)
        v.drawHighlighted();
    else
        v.draw();
        */

    //tutorial2D();
    tutorial3D();
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

