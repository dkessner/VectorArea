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

    static constexpr double pickRadius = 10.0;

    static glm::vec3 mouse()
    {
        return glm::vec3(ofGetMouseX(), ofGetMouseY(), 0);
    }

    static glm::vec3 previousMouse()
    {
        return glm::vec3(ofGetPreviousMouseX(), ofGetPreviousMouseY(), 0);
    }

    virtual double distance(const glm::vec3& mouse) const
    {
        return std::numeric_limits<int>::max();
    }

    bool picked() const
    {
        return distance(mouse()) < pickRadius;
    }

    virtual void handleMousePressed(int x, int y, int button) {}
    virtual void handleMouseDragged(int x, int y, int button) {}
    virtual void handleMouseReleased(int x, int y, int button) {}

    private:

    static std::vector<std::weak_ptr<Pickable>> registry;
    static std::shared_ptr<Pickable> selected;
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

        if (picked())
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
        cout << "dragged\n" << flush;

        position -= previousMouse();
        position += mouse();
    }

    virtual void handleMouseReleased(int x, int y, int button)
    {
        cout << "released\n" << flush;
    }

    protected:

    double distance(const glm::vec3& mouse) const override
    {
        return glm::distance(position, mouse);
    }

    private:

    glm::vec3 position;
};


