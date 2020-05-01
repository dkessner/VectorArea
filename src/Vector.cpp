//
// Vector.cpp
//


#include "Vector.hpp"
#include "glm/gtx/rotate_vector.hpp"


using namespace std;
using namespace glm;


Vector::Vector()
{
    pickableTail = PickableCircle::create();
    pickableTail->registerCallback(bind(&Vector::moveTail, this, std::placeholders::_1));

    pickableHead = PickableCircle::create();
    pickableHead->registerCallback(bind(&Vector::moveHead, this, std::placeholders::_1));

    initializeMesh();
}


void Vector::set(double x, double y, double z)
{
    set(vec3(x, y, z));
}


void Vector::set(const glm::vec3& components)
{
    this->components = components;
    updateMesh();
}


void Vector::setPosition(double x, double y, double z)
{
    setPosition(vec3(x, y, z));
}


void Vector::setPosition(const vec3& position)
{
    primitive.setPosition(position);
    pickableTail->setPosition(position);
    pickableHead->setPosition(position + components);
}

 
void Vector::moveTail(const glm::vec3& movement)
{
    primitive.move(movement);   // move the position of the tail/primitive
    components -= movement;     // move the head back to where it was
    updateMesh();
}


void Vector::moveHead(const glm::vec3& movement)
{
    components += movement;
    updateMesh();
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

    mesh.setMode(OF_PRIMITIVE_LINES);
    mesh.addVertex(glm::vec3());    // tail at (0,0)
    mesh.addVertex(components);     // head at (components)

    mesh.addVertex(glm::vec3());    // arrowLeft
    mesh.addVertex(glm::vec3());    // arrowRight

    mesh.addColor(ofColor::blue);
    mesh.addColor(ofColor::white);
    mesh.addColor(ofColor::yellow);
    mesh.addColor(ofColor::yellow);

    mesh.addIndex(0);
    mesh.addIndex(1);

    mesh.addIndex(2);
    mesh.addIndex(1);

    mesh.addIndex(3);
    mesh.addIndex(1);
}


void Vector::updateMesh()
{
    ofMesh& mesh = primitive.getMesh();
    mesh.setVertex(1, components);

    vec3 arrowLeft = glm::normalize(glm::rotateZ(components, -5*(float)PI/6)) * 30;
    mesh.setVertex(2, components + arrowLeft);

    vec3 arrowRight = glm::normalize(glm::rotateZ(components, 5*(float)PI/6)) * 30;
    mesh.setVertex(3, components + arrowRight);
}



