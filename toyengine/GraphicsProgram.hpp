#pragma once

#include <glad/glad.h>
// glad must be on top of GLFW/glfw3.h
#include <GLFW/glfw3.h>

#include "Level.hpp"

#include <memory.h>

//! \brief This class sets up a full graphics program.
class GraphicsProgram {
public:
    // Constructor
    GraphicsProgram(std::shared_ptr<Level> level);

    // Desctructor
    ~GraphicsProgram();

    // Per frame update
    void update();

    // Renders shapes to the screen
    void render();

    // loop that runs forever
    void loop();

private:
    // The current level
    std::shared_ptr<Level> mLevel;
	
    // The window we'll be rendering to
    GLFWwindow* mWindow = nullptr;

};


////! \brief This class sets up a full graphics program.
//class GraphicsProgram {
//public:
//	//! \brief Constructor.
//	GraphicsProgram();
//
//	//! \brief Destructor.
//	~GraphicsProgram();
//
//	//! \brief Initializes the graphics program.
//	//! \param[in] vertexShaderPath The path to the vertex shader.
//	//! \param[in] fragmentShaderPath The path to the fragment shader.
//	//! \param[in] geometryShaderPath The path to the geometry shader.
//	//! \return True if the graphics program was initialized successfully, false otherwise.
//	bool Initialize(const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShaderPath = nullptr);
//
//	//! \brief Deinitializes the graphics program.
//	void Deinitialize();
//
//	//! \brief Binds the graphics program.
//	void Bind();
//
//	//! \brief Unbinds the graphics program.
//	void Unbind();
//
//	//! \brief Sets the value of a uniform.
//	//! \param[in] name The name of the uniform.
//	//! \param[in] value The value of the uniform.
//	void SetUniform(const char* name, int value);
//
//	//! \brief Sets the value of a uniform.
//	//! \param[in] name The name of the uniform.
//	//! \param[in] value The value of the uniform.
//	void SetUniform(const char* name, float value);
//
//	//! \brief Sets the value of a uniform.
//	//! \param[in] name The name of the uniform.
//	//! \param[in] value The value of the uniform.
//	void SetUniform(const char* name, const glm::vec2& value);
//
//	//! \brief Sets the value of a uniform.
//	//! \param[in] name The name of the uniform.
//	//! \param[in] value The value of the uniform.
//	void SetUniform(const char* name, const glm::vec3& value);
//};

