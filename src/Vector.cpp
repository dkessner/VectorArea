//
// Vector.cpp
//


#include "Vector.hpp"


using namespace std;
using namespace glm;


Vector::Vector()
{
    pickableTail = PickableCircle::create();
    pickableTail->registerCallback(bind(&Vector::moveTail, this, std::placeholders::_1));

    pickableHead = PickableCircle::create();
    pickableHead->registerCallback(bind(&Vector::moveHead, this, std::placeholders::_1));
}


void Vector::set(const glm::vec3& components)
{
    this->components = components;
    initializeMesh();
}


void Vector::moveTail(const glm::vec3& movement)
{
    primitive.move(movement);
    pickableHead->move(movement);
}


void Vector::moveHead(const glm::vec3& movement)
{
    components += movement;
    updateMesh();
}


void Vector::setPosition(const vec3& position)
{
    primitive.setPosition(position);
    pickableTail->setPosition(position);
    pickableHead->setPosition(position + components);
}


void Vector::draw()
{
    primitive.draw();
    pickableTail->draw();
    pickableHead->draw();
}


void Vector::initializeMesh()
{
    ofMesh& mesh = primitive.getMesh();

    mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    mesh.addVertex(glm::vec3());
    mesh.addVertex(components);

    mesh.addColor(ofColor::blue);
    mesh.addColor(ofColor::white);
}


void Vector::updateMesh()
{
    ofMesh& mesh = primitive.getMesh();
    mesh.setVertex(1, components);
}



