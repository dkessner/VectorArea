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
    //
    // client interface/implementation
    //

    public:

    Pickable();

    bool isActive() const {return active;}
    void setActive(bool active) {this->active = active;}

    virtual void draw() const = 0;

    typedef std::function<void(const glm::vec3& movement)> Callback;
    void registerCallback(const Callback& callback);

    typedef std::function<glm::vec3(const glm::vec3& mouse)> MouseTransformation;
    void setMouseTransformation(const MouseTransformation& mouseTransformation);

    virtual ~Pickable() {}

    //
    // subclass interface/implementation
    //

    protected:

    bool active = true;
    std::vector<Callback> callbacks;
    MouseTransformation mouseTransformation;

    // virtual functions to be overridden in subclasses

    virtual double distance(const glm::vec3& mouse) const {return std::numeric_limits<int>::max();}
    virtual void handleMousePressed() {}
    virtual void handleMouseDragged() {}
    virtual void handleMouseReleased() {}

    // helper functions for subclasses

    static void addToRegistry(std::shared_ptr<Pickable> pickable);

    static constexpr double pickRadius = 7.0;

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

    bool isPicked() const
    {
        // note: distance() is virtual, pickRadius is static
        return distance(mouse()) < pickRadius;
    }

    private:

    // mouse event handling -- static mouse event handlers delegate
    // to Pickable objects in the registry

    static void mousePressed(ofMouseEventArgs&);
    static void mouseDragged(ofMouseEventArgs&);
    static void mouseReleased(ofMouseEventArgs&);

    static std::vector<std::weak_ptr<Pickable>> registry;
    static void initializeRegistry();
    static std::shared_ptr<Pickable> selected;
};


class PickableCircle : public Pickable
{
    public:

    // static create() automatically adds object to registry

    static std::shared_ptr<PickableCircle> create(double x = 0, double y = 0)
    {
        auto result = shared_ptr<PickableCircle>(new PickableCircle(x, y));
        addToRegistry(result);
        return result;
    }

    void draw() const override;

    void setPosition(const glm::vec3& position) {this->position = position;}
    void move(const glm::vec3& movement) {position += movement;}

    protected:

    double distance(const glm::vec3& mouse) const override;
    void handleMouseDragged() override;

    private:

    glm::vec3 position;

    PickableCircle(double x, double y)
    :   position(x, y, 0)
    {}
};


class PickableLineSegment : public Pickable
{
    public:

    // static create() automatically adds object to registry

    static std::shared_ptr<PickableLineSegment> create(double x1 = 0, double y1 = 0,
                                                       double x2 = 0, double y2 = 0)
    {
        auto result = shared_ptr<PickableLineSegment>(new PickableLineSegment(x1, y1, x2, y2));
        addToRegistry(result);
        return result;
    }

    void draw() const override;

    void setEndpoints(const glm::vec3& a, const glm::vec3& b) {this->a=a; this->b=b;}
    void move(const glm::vec3& movement) {a += movement; b += movement;}

    protected:

    double distance(const glm::vec3& mouse) const override;
    void handleMouseDragged() override;

    private:

    glm::vec3 a, b;

    PickableLineSegment(double x1, double y1, double x2, double y2)
    :   a(x1, y1, 0), b(x2, y2, 0)
    {}
};


