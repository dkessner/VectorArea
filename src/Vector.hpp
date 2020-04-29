//
// Vector.hpp
//


#include "ofMain.h"
#include "Pickable.hpp"


class Vector
{
    public:

    Vector();

    void set(const glm::vec3& components);
    void setPosition(const glm::vec3& position);

    void draw();

    void moveTail(const glm::vec3& movement);
    void moveHead(const glm::vec3& movement);

    private:

    glm::vec3 components;
    of3dPrimitive primitive;

    shared_ptr<PickableCircle> pickableTail; 
    shared_ptr<PickableCircle> pickableHead; 

    void initializeMesh();
    void updateMesh();
};


