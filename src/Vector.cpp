//
// Vector.cpp
//


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


void Vector::updateMesh()
{
    ofMesh& mesh = primitive.getMesh();

    mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    mesh.addVertex(glm::vec3());
    mesh.addVertex(components);

    mesh.addColor(ofColor::blue);
    mesh.addColor(ofColor::white);
}



