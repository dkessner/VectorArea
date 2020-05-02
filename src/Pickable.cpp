//
// Pickable.cpp
//


#include "Pickable.hpp"


using namespace std;
using namespace glm;



typedef std::function<glm::vec3(const glm::vec3& mouse)> MouseTransformation;

namespace {

vec3 identity(const vec3& mouse) {return mouse;}

vec3 circleTransform(const vec3& mouse)
{
    vec3 center(1024/2.0f, 768/2.0f, 0.0f);
    constexpr int radius = 100;

    vec3 d = normalize(mouse - center) * radius; 
    return center + d;
}


} // namespace


Pickable::Pickable()
:   mouseTransformation(identity)
{}


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
            if (p->isActive() && p->isPicked())
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
        selected->handleMouseDragged();
}


/*static*/ void Pickable::mouseReleased(ofMouseEventArgs&)
{
    if (selected)
        selected->handleMouseReleased();

    selected.reset();
}


void Pickable::registerCallback(const Callback& callback)
{
    callbacks.push_back(callback);
}


void Pickable::setMouseTransformation(const MouseTransformation& mouseTransformation)
{
    this->mouseTransformation = mouseTransformation;
}


//
// PickableCircle
//


void PickableCircle::draw() const
{
    if (!active) return;

    ofFill();
    ofSetColor(128);
    ofSetLineWidth(1);
    ofDrawCircle(position, pickRadius);

    if (isPicked())
    {
        ofNoFill();
        ofSetColor(0, 255, 0);
        ofSetLineWidth(3);
        ofDrawCircle(position, pickRadius * 1.2);
    }
}


void PickableCircle::handleMouseDragged()
{
    vec3 mouse = mouseTransformation(Pickable::mouse());
    vec3 previousMouse = mouseTransformation(Pickable::previousMouse());
    vec3 mouseMovement = mouse - previousMouse;

    position += mouseMovement;

    for (const auto& callback : callbacks)
        callback(mouseMovement);
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
    if (!active) return;

    ofFill();
    isPicked() ? ofSetColor(0, 255, 0) : ofSetColor(128);
    ofSetLineWidth(isPicked() ? 3 : 1);
    ofDrawLine(a, b);

    float x = (3*a.x+b.x)/4;
    float y = (a.y+b.y)/2 + 40;

    constexpr bool showDistances = false;
    if (showDistances)
    {
        ofDrawBitmapString("dist(mouse,segment): " + to_string(distance(mouse())), x, y += 20);
        ofDrawBitmapString("dist(mouse,a): " + to_string(glm::distance(mouse(), a)), x, y += 20);
        ofDrawBitmapString("dist(mouse,b): " + to_string(glm::distance(mouse(), b)), x, y += 20);
    }
}


void PickableLineSegment::handleMouseDragged()
{
    a += mouseMovement();
    b += mouseMovement();

    for (const auto& callback : callbacks)
        callback(mouseMovement());
}


//
// glm geometric functions (dot, cross, distance, normalize)
//      https://glm.g-truc.net/0.9.9/api/a00279.html
//


double PickableLineSegment::distance(const vec3& mouse) const
{
    vec3 u = b - a;
    vec3 v = mouse - a;
    vec3 w = mouse - b;
    double vu = dot(v,u);
    double wu = dot(w,u);

    if (vu < 0) return length(v); // distance to a

    if (wu > 0) return length(w); // distance to b

    // we're "between" a and b, so we calculate perpendicular distance by
    // projecting onto the segment

    vec3 u1 = normalize(u);
    vec3 vproj = dot(v,u1) * u1;
    vec3 d = v - vproj;
    return length(d);
}


