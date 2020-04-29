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
}


void Vector::set(const glm::vec3& components)
{
    this->components = components;
    updateMesh();
}


void Vector::move(const vec3& movement)
{
    primitive.move(movement);
    pickableTail->move(movement);
}


void Vector::moveTail(const glm::vec3& movement)
{
    primitive.move(movement);
}


void Vector::setPosition(const vec3& position)
{
    primitive.setPosition(position);
    pickableTail->setPosition(position);
}


void Vector::draw()
{
    primitive.draw();
    pickableTail->draw();
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


