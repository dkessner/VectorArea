//
// Pickable.hpp
//


#include "ofMain.h"
#include <limits>
#include <memory>
#include <vector>


class Pickable
{
    public:

    virtual double distance(const glm::vec3& mouse) 
    {
        return std::numeric_limits<int>::max();
    }

    virtual void drawHighlight() {}

    virtual void pickBegin() {}
    virtual void pickMove() {}
    virtual void pickEnd() {}

    static void addToRegistry(std::shared_ptr<Pickable> pickable);

//    private:  // TODO: uncomment

    static std::vector<std::weak_ptr<Pickable>> registry;
};


