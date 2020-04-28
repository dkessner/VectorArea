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
    static void mousePressed(int x, int y, int button);
    static void mouseDragged(int x, int y, int button);
    static void mouseReleased(int x, int y, int button);

    // callback on drag movement

    typedef std::function<void(const glm::vec3& movement)> Listener;
    void registerListener(Listener listener);

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

    bool picked() const
    {
        // note: distance() is virtual, pickRadius is static
        return distance(mouse()) < pickRadius;
    }

    // virtual functions to be overridden in subclasses

    virtual double distance(const glm::vec3& mouse) const {return std::numeric_limits<int>::max();}
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

    void draw() const override;
    void handleMousePressed(int x, int y, int button) override;
    void handleMouseDragged(int x, int y, int button) override;
    void handleMouseReleased(int x, int y, int button) override;

    protected:

    double distance(const glm::vec3& mouse) const override;

    private:

    glm::vec3 position;
};


