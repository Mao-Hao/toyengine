#pragma once

#include "GenericComponent.hpp"
#include "RenderComponent.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <memory>
#include <vector>

class Level;

class GameObject {
public:

	GameObject(glm::vec3 position, glm::vec3 size, int tag)
        : mPosition(position)
		, mSize(size)
		, mTag(tag)
    {
    }

    virtual ~GameObject() { }

    int tag() const { return mTag; }

    void setX(float x) { mPosition.x = x; }
    void setY(float y) { mPosition.y = y; }
    void setZ(float z) { mPosition.z = z; }

    float x() const { return mPosition.x; }
    float y() const { return mPosition.y; }
    float z() const { return mPosition.z; }
	
    float w() const { return mSize.x; }
    float h() const { return mSize.y; }
    float d() const { return mSize.z; }

    void addGenericCompenent(std::shared_ptr<GenericComponent> comp) { mGenericComponents.push_back(comp); }
    void setRenderCompenent(std::shared_ptr<RenderComponent> comp) { mRenderComponent = comp; }

    void update(Level& level) //!< Update the object.
    {
        for (auto genericComponent : mGenericComponents) {
            genericComponent->update(level);
        }
    }

    void step(Level& level) //!< Do the physics step for the object.
    {
		// TODO:
    }

    void render() //!< Render the object.
    {
        if (mRenderComponent) {
            mRenderComponent->render();
        }
    }

private:
    GameObject(const GameObject&) = delete;
    void operator=(GameObject const&) = delete;

    glm::vec3 mPosition;
	glm::vec3 mSize;
	
    int mTag;

    std::vector<std::shared_ptr<GenericComponent>> mGenericComponents;
    std::shared_ptr<RenderComponent> mRenderComponent;
};