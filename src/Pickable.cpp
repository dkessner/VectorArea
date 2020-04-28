//
// Pickable.cpp
//


#include "Pickable.hpp"


using namespace std;
using namespace glm;


vector<weak_ptr<Pickable>> Pickable::registry;
shared_ptr<Pickable> Pickable::selected;


void Pickable::addToRegistry(shared_ptr<Pickable> pickable)
{
    registry.push_back(pickable); 
}


void Pickable::mousePressed(int x, int y, int button)
{
    for (auto wp : registry)
        if (auto p = wp.lock())
            if (p->picked())
            {
                selected = p;
                break;
            }

    if (selected)
        selected->handleMousePressed(x, y, button);
}


void Pickable::mouseDragged(int x, int y, int button)
{
    if (selected)
        selected->handleMouseDragged(x, y, button);
}

void Pickable::mouseReleased(int x, int y, int button)
{
    if (selected)
        selected->handleMouseReleased(x, y, button);

    selected.reset();
}


//
// PickableCircle
//

void PickableCircle::draw() const
{
    double radius = pickRadius;

    if (picked())
    {
        ofSetLineWidth(5);
        radius *= 1.2;
    }
    else
    {
        ofSetLineWidth(2);
    }

    ofSetColor(255);
    ofDrawCircle(position, radius);
}


void PickableCircle::handleMousePressed(int x, int y, int button)
{
    cout << "pressed\n" << flush;
}


void PickableCircle::handleMouseDragged(int x, int y, int button)
{
    cout << "dragged\n" << flush;

    position -= previousMouse();
    position += mouse();
}


void PickableCircle::handleMouseReleased(int x, int y, int button)
{
    cout << "released\n" << flush;
}


double PickableCircle::distance(const vec3& mouse) const
{
    return glm::distance(position, mouse);
}


