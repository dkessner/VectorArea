//
// Pickable.hpp
//


#include <limits>
#include <memory>
#include <vector>


class Pickable
{
    public:

    virtual double distance(int mouseX, int mouseY) 
    {
        return std::numeric_limits<int>::max();
    }

    virtual void drawHighlight() {}

    virtual void pickBegin() {}
    virtual void pickMove() {}
    virtual void pickEnd() {}

    static void addToRegistry(std::shared_ptr<Pickable> pickable);

    private:

    static std::vector<std::weak_ptr<Pickable>> registry;
};


