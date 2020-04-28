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

    // client maintains control over drawing

    virtual void draw() const {} 

    // client registers Pickable objects to receive mouse events

    static void addToRegistry(std::shared_ptr<Pickable> pickable);

    // callback on drag movement

    typedef std::function<void(const glm::vec3& movement)> Callback;
    void registerCallback(Callback callback);

    protected:

    static constexpr double pickRadius = 10.0;

    // helper functions for subclasses

    static glm::vec3 mouse()
    {
        return glm::vec3(ofGetMouseX(), ofGetMouseY(), 0);
    }

    static glm::vec3 previousMouse()
    {
        return glm::vec3(ofGetPreviousMouseX(), ofGetPreviousMouseY(), 0);
    }

    static glm::vec3 mouseMovement()
    {
        return mouse() - previousMouse();
    }

    bool picked() const
    {
        // note: distance() is virtual, pickRadius is static
        return distance(mouse()) < pickRadius;
    }

    // virtual functions to be overridden in subclasses

    virtual double distance(const glm::vec3& mouse) const {return std::numeric_limits<int>::max();}
    virtual void handleMousePressed() {}
    virtual void handleMouseDragged() {}
    virtual void handleMouseReleased() {}

    private:

    static std::vector<std::weak_ptr<Pickable>> registry;
    static void initializeRegistry();
    static std::shared_ptr<Pickable> selected;

    static void mousePressed(ofMouseEventArgs&);
    static void mouseDragged(ofMouseEventArgs&);
    static void mouseReleased(ofMouseEventArgs&);

    std::vector<Callback> callbacks;
};


class PickableCircle : public Pickable
{
    public:

    PickableCircle(double x, double y)
    :   position(x, y, 0)
    {}

    void draw() const override;

    protected:

    double distance(const glm::vec3& mouse) const override;
    void handleMouseDragged() override;

    private:

    glm::vec3 position;
};


