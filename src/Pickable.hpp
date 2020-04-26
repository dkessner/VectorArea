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

    virtual double distance(const glm::vec3& mouse) const
    {
        return std::numeric_limits<int>::max();
    }

    virtual void draw() const {} 

    protected:

    glm::vec3 mouse() const
    {
        return glm::vec3(ofGetMouseX(), ofGetMouseY(), 0);
    }

    static constexpr double pickRadius = 10.0;

    // TODO: mouse event handling and listeners

    /*
    virtual void pickBegin() {}
    virtual void pickMove() {}
    virtual void pickEnd() {}
    */

    static void addToRegistry(std::shared_ptr<Pickable> pickable);
    //static void drawHighlightPicked(glm::vec3 mousePosition, double radius);

    private:

    static std::vector<std::weak_ptr<Pickable>> registry;
};


class PickableCircle : public Pickable
{
    public:

    PickableCircle(double x, double y)
    :   position(x, y, 0)
    {}

    double distance(const glm::vec3& mouse) const override
    {
        return glm::distance(position, mouse);
    }

    void draw() const override
    {
        double radius = pickRadius;

        if (distance(mouse()) < radius)
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

    private:

    const glm::vec3 position;
};




