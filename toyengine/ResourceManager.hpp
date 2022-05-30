#pragma once

#include "Shader.hpp"

#include <map>
#include <string>
#include <vector>

class ResourceManager {
private:
    ResourceManager() = default; // Private Singleton
    ResourceManager(ResourceManager const&) = delete; // Avoid copy constructor.
    void operator=(ResourceManager const&) = delete; // Don't allow copy assignment.
    ResourceManager(ResourceManager&&) = delete; // Avoid move constructor.
    void operator=(ResourceManager&&) = delete; // Don't allow move assignment.

public:
    static ResourceManager& getInstance()
    {
        static ResourceManager* instance = new ResourceManager();
        return *instance;
    }

    void startUp()
    {
    }

    void shutDown()
    {
    }

    Shader loadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name)
    {
    }

    Shader GetShader(std::string name)
    {
    }

private:
    std::map<std::string, Shader*> Shaders;
};
