//
// Vector.hpp
//


#include "ofMain.h"
#include "Pickable.hpp"


class Vector
{
    public:

    Vector(const glm::vec3& components, const glm::vec3& position);
    Vector(const glm::vec3& components);
    Vector(double x=0, double y=0, double z=0);

    void set(double x, double y=0, double z=0);
    void set(const glm::vec3& components);

    void setPosition(double x, double y=0, double z=0);
    void setPosition(const glm::vec3& position);

    void draw();

    shared_ptr<Pickable> getPickableTail() {return pickableTail;}
    shared_ptr<Pickable> getPickableHead() {return pickableHead;}
    shared_ptr<Pickable> getPickableBody() {return pickableBody;}

    glm::vec3 getPosition() const {return primitive.getPosition();}
    const glm::vec3& getComponents() const {return components;}

    // Pickable callbacks

    void moveTail(const glm::vec3& movement);
    void moveHead(const glm::vec3& movement);
    void moveBody(const glm::vec3& movement);

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
    shared_ptr<PickableLineSegment> pickableBody;

    void initializeMesh();
    void updateMesh();
};


