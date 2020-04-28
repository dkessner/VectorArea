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

    // TODO: callback interface
    //  - store list of std::function; use std::bind for member functions
    // https://embeddedartistry.com/blog/2017/02/01/improving-your-callback-game/

    // static interface for app to register Pickable objects and delegate mouse
    // events

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

    bool picked() const
    {
        return distance(mouse()) < pickRadius;
    }

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


