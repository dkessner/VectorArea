//
// Pickable.hpp
//


#pragma once
#include "ofMain.h"
#include <limits>
#include <memory>
#include <vector>


class Pickable
{
    public:

    virtual void draw() const {} 

    static void addToRegistry(std::shared_ptr<Pickable> pickable);
    static void mousePressed(int x, int y, int button);
    static void mouseDragged(int x, int y, int button);
    static void mouseReleased(int x, int y, int button);

    protected:

    bool selected() const
    {
        return distance(mouse()) < pickRadius;
    }

    virtual double distance(const glm::vec3& mouse) const
    {
        return std::numeric_limits<int>::max();
    }

    glm::vec3 mouse() const
    {
        return glm::vec3(ofGetMouseX(), ofGetMouseY(), 0);
    }

    static constexpr double pickRadius = 10.0;

    virtual void handleMousePressed(int x, int y, int button) {}
    virtual void handleMouseDragged(int x, int y, int button) {}
    virtual void handleMouseReleased(int x, int y, int button) {}

    // TODO: mouse event handling and listeners

    /*
    virtual void pickBegin() {}
    virtual void pickMove() {}
    virtual void pickEnd() {}
    */

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

    void draw() const override
    {
        double radius = pickRadius;

        if (selected())
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

    virtual void handleMousePressed(int x, int y, int button)
    {
        cout << "pressed\n" << flush;
    }

    virtual void handleMouseDragged(int x, int y, int button)
    {
    }

    virtual void handleMouseReleased(int x, int y, int button)
    {
    }

    protected:

    double distance(const glm::vec3& mouse) const override
    {
        return glm::distance(position, mouse);
    }

    private:

    const glm::vec3 position;
};




