//
// Pickable.cpp
//


#include "Pickable.hpp"


using namespace std;


void Pickable::addToRegistry(shared_ptr<Pickable> pickable)
{
    registry.push_back(pickable); 
}


void Pickable::drawHighlightPicked(glm::vec3 mousePosition, double radius)
{
    for (auto pickable : Pickable::registry)
    {
        if (auto p = pickable.lock())
        {
            if (p->distance(mousePosition) < radius)
                p->drawHighlight();
        }
    }
}


vector<weak_ptr<Pickable>> Pickable::registry;


