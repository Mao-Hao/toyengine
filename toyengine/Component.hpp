#pragma once

class GameObject;

//! \brief Base class for all components. Keeps track of the game object.
class Component {
public:
    Component(GameObject& gameObject)
        : mGameObject(gameObject)
    {
        (void)mGameObject; // to prevent warnings
    }
	
    virtual ~Component() {
		
    }

protected:
    inline GameObject& getGameObject() { return mGameObject; }
    inline const GameObject& getGameObject() const { return mGameObject; }

private:
    Component(const Component&) = delete;
    void operator=(Component const&) = delete;

    GameObject& mGameObject;
};
