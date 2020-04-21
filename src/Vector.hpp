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

    void draw();
    void drawHighlighted();

    double mouseDistance();

    private:

    glm::vec3 components;
    of3dPrimitive primitive;

    void updateMesh();

    std::shared_ptr<Pickable> pickableHead;

    class PickableHead;
};


