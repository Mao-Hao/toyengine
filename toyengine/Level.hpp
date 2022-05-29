#pragma once

#include "GameObject.hpp"

#include <algorithm>
#include <memory>
#include <vector>

//! \brief A level in the game.  Essentially mannages a collection of game
//! objects, and does some collision detection.
class Level {
public:
    Level(int w, int h)
        : mW(w)
        , mH(h)
    {
    }

    inline int w() const { return mW; }
    inline int h() const { return mH; }

    //!< Set an object to be added.
    void addObject(std::shared_ptr<GameObject> object) { mObjectsToAdd.push_back(object); }
    //!< Set an object to be removed.
    void removeObject(std::shared_ptr<GameObject> object) { mObjectsToRemove.push_back(object); }
    //!< Get if an object is in the level.
    bool hasObject(std::shared_ptr<GameObject> object) const { return std::find(mObjects.begin(), mObjects.end(), object) != mObjects.end(); }

    void update() //!< Update the objects in the level.
    {
        for (auto obj : mObjectsToAdd) {
            mObjects.push_back(obj);
        }
        mObjectsToAdd.clear();

        for (auto gameObject : mObjects) {
            gameObject->update(*this);
        }
        for (auto gameObject : mObjects) {
            gameObject->step(*this);
        }

        for (auto obj : mObjectsToRemove) {
            auto elem = std::find(mObjects.begin(), mObjects.end(), obj);
            if (elem != mObjects.end()) {
                mObjects.erase(elem);
            }
        }
        mObjectsToRemove.clear();
    }

    void render() //!< Render the level.
    {
        for (auto& object : mObjects) {
            object->render();
        }
    }

private:
    Level(const Level&) = delete;
    void operator=(Level const&) = delete;

    int mW, mH;
    std::vector<std::shared_ptr<GameObject>> mObjects;

    std::vector<std::shared_ptr<GameObject>> mObjectsToAdd;
    std::vector<std::shared_ptr<GameObject>> mObjectsToRemove;
};
