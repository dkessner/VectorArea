//
// Vector.cpp
//


#include "Pickable.hpp"
#include "Vector.hpp"


void Vector::set(const glm::vec3& components)
{
    this->components = components;
    updateMesh();

    primitive.move(ofGetWindowWidth()/2, ofGetWindowHeight()/2, 0.0f);
}


void Vector::draw()
{
    primitive.draw();
}


void Vector::drawHighlighted()
{
    ofSetLineWidth(5);
    draw();
    ofSetLineWidth(1);
}


double Vector::mouseDistance()
{
    glm::vec3 mouse(ofGetMouseX(), ofGetMouseY(), 0);
    glm::vec3 tail = primitive.getPosition(); 
    glm::vec3 head = tail + components;

    double d1 = distance(mouse, tail);
    double d2 = distance(mouse, head);

    /*
    cout << "mouse: " << mouse << endl;
    cout << "tail: " << tail << endl;
    cout << "head: " << head << endl;
    cout << "d1: " << d1 << endl;
    cout << "d2: " << d2 << endl;
    */

    double threshold = 50;
    return (d1 < threshold || d2 < threshold) ? 0 : 1;
}


void Vector::updateMesh()
{
    ofMesh& mesh = primitive.getMesh();

    mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    mesh.addVertex(glm::vec3());
    mesh.addVertex(components);

    mesh.addColor(ofColor::blue);
    mesh.addColor(ofColor::white);
}


