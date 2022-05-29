#pragma once

#include "Component.hpp"

#include <memory>

class Level;

class GenericComponent : public Component {
public:
    GenericComponent(GameObject& gameObject)
        : Component(gameObject)
    {
    }
    //!< Update the object.
    virtual void update(Level& level) { }

    //!< Handle a collision with the given object.
    virtual void collision(Level& level, std::shared_ptr<GameObject> obj) { }
};