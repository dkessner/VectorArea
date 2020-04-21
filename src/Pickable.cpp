//
// src/Pickable.cpp
//


#include "Pickable.hpp"


using namespace std;


void Pickable::addToRegistry(shared_ptr<Pickable> pickable)
{
    registry.push_back(pickable); 
}


vector<weak_ptr<Pickable>> Pickable::registry;


