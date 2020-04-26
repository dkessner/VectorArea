//
// Pickable.cpp
//


#include "Pickable.hpp"


using namespace std;


vector<weak_ptr<Pickable>> Pickable::registry;


void Pickable::addToRegistry(shared_ptr<Pickable> pickable)
{
    registry.push_back(pickable); 
}


void Pickable::mousePressed(int x, int y, int button)
{
    for (auto wp : registry)
        if (auto p = wp.lock())
            if (p->selected())
                p->handleMousePressed(x, y, button);
}


void Pickable::mouseDragged(int x, int y, int button)
{


}

void Pickable::mouseReleased(int x, int y, int button)
{

}



