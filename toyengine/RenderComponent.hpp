#pragma once

#include "Component.hpp"
#include "Shader.hpp"

//! \brief A component that handles rendering.
class RenderComponent : public Component {
public:
    RenderComponent(GameObject& gameObject, Shader& shader)
        : Component(gameObject)
        , mShader(shader)
    {
    
    }

    virtual void render() = 0; //!< Do the render.
	
protected:
	Shader mShader; //!< The shader to use.
};

