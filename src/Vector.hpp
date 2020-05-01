//
// Vector.hpp
//


#include "ofMain.h"
#include "Pickable.hpp"


class Vector
{
    public:

    Vector();

    void set(double x, double y=0, double z=0);
    void set(const glm::vec3& components);

    void setPosition(double x, double y=0, double z=0);
    void setPosition(const glm::vec3& position);

    void draw();

    void moveTail(const glm::vec3& movement);
    void moveHead(const glm::vec3& movement);

    private:

    //
    // Implementation notes:
    //
    // - components: the actual <x,y,z> components of the vector
    //
    // - primitive: the graphics info, including the mesh (vertices to draw)
    //   and the coordinate system info (ofNode), which includes the position
    //   (of the tail) of the vector in space
    //
    // tail: primitive.getPosition()
    // head: primitive.getPosition() + components
    //

    glm::vec3 components;
    of3dPrimitive primitive;

    shared_ptr<PickableCircle> pickableTail; 
    shared_ptr<PickableCircle> pickableHead; 

    void initializeMesh();
    void updateMesh();
};


