//
// Pickable.cpp
//


#include "Pickable.hpp"


using namespace std;
using namespace glm;


// registry of Pickable objects to receive mouse events
vector<weak_ptr<Pickable>> Pickable::registry;


void Pickable::initializeRegistry()
{
    ofAddListener(ofEvents().mousePressed, &Pickable::mousePressed);
    ofAddListener(ofEvents().mouseDragged, &Pickable::mouseDragged);
    ofAddListener(ofEvents().mouseReleased, &Pickable::mouseReleased);
}


// Pickable object selected on mouse press, and receives subsequent mouse drag
// and mouse release events
shared_ptr<Pickable> Pickable::selected;


/*static*/ void Pickable::addToRegistry(shared_ptr<Pickable> pickable)
{
    if (registry.empty()) initializeRegistry();
    registry.push_back(pickable); 
}


/*static*/ void Pickable::mousePressed(ofMouseEventArgs&)
{
    for (auto wp : registry)
        if (auto p = wp.lock())
            if (p->picked())
            {
                selected = p;
                break;
            }

    if (selected)
        selected->handleMousePressed();
}


/*static*/ void Pickable::mouseDragged(ofMouseEventArgs&)
{
    if (selected)
    {
        selected->handleMouseDragged();

        for (const auto& callback : selected->callbacks)
            callback(mouseMovement());
    }
}

/*static*/ void Pickable::mouseReleased(ofMouseEventArgs&)
{
    if (selected)
        selected->handleMouseReleased();

    selected.reset();
}


void Pickable::registerCallback(Callback callback)
{
    callbacks.push_back(callback);
}


//
// PickableCircle
//


void PickableCircle::draw() const
{
    ofFill();
    ofSetColor(128);
    ofSetLineWidth(1);
    ofDrawCircle(position, pickRadius);

    if (picked())
    {
        ofNoFill();
        ofSetColor(0, 255, 0);
        ofSetLineWidth(3);
        ofDrawCircle(position, pickRadius * 1.2);
    }
}


void PickableCircle::handleMouseDragged()
{
    position += mouseMovement();
}


double PickableCircle::distance(const vec3& mouse) const
{
    return glm::distance(position, mouse);
}


//
// PickableLineSegment
//


void PickableLineSegment::draw() const
{
    ofFill();
    picked() ? ofSetColor(0, 255, 0) : ofSetColor(128);
    ofSetLineWidth(picked() ? 3 : 1);
    ofDrawLine(a, b);
}


void PickableLineSegment::handleMouseDragged()
{
    a += mouseMovement();
    b += mouseMovement();
}


double PickableLineSegment::distance(const vec3& mouse) const
{
    return glm::distance((a+b)/2, mouse) / 10; // hack
}


