//
// Vector.cpp
//


#include "Vector.hpp"


void Vector::set(const glm::vec3& components)
{
    this->components = components;
    updateMesh();
}


void Vector::draw()
{
    mesh.draw();
}


void Vector::updateMesh()
{
    mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    mesh.addVertex(glm::vec3());
    mesh.addVertex(components);

    mesh.addColor(ofColor::blue);
    mesh.addColor(ofColor::white);
}



