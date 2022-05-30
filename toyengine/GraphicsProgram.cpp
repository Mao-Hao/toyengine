#include "Timer.hpp"

#include "GraphicsProgram.hpp"

#include <iostream>
#include <sstream>
#include <time.h>



// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

GraphicsProgram::GraphicsProgram(std::shared_ptr<Level> level)
    : mLevel(level)
{
    // Initialize random number generation.
    srand((unsigned int)time(nullptr));
    // Initialization flag
    bool success = true;
    // String to hold any errors that occur.
    std::stringstream errorStream;
    // The window we'll be rendering to
    mWindow = nullptr;

    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    mWindow = glfwCreateWindow(mLevel->w(), mLevel->h(), "Toy", nullptr, nullptr);
    if (mWindow == nullptr) {
        errorStream << "Failed to create GLFW window. OpenGL Error:" << glGetError() << "\n";
        success = false;
        glfwTerminate();
    }
    glfwMakeContextCurrent(mWindow);
    glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_callback);

	glfwSwapInterval(0);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        errorStream << "Failed to initialize GLAD\n";
        success = false;
    }

    if (!success) {
        errorStream << "Failed to initialize!\n";
        std::string errors = errorStream.str();
        std::cout << errors << "\n";
    } else {
        std::cout << "No OpenGL errors Detected during init\n\n";
    }
}

GraphicsProgram::~GraphicsProgram()
{
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
}

void GraphicsProgram::update()
{
    mLevel->update();
}

void GraphicsProgram::render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    mLevel->render();

    glfwSwapBuffers(mWindow);
}

void GraphicsProgram::loop()
{
    // Main loop flag
    // If this is quit = 'true' then the program terminates.
    bool quit = false;
    // Event handler that handles various events that are related to input and output
    // While application is running
    Timer timer(60u);
    while (!quit) {
        auto startTicks = std::chrono::high_resolution_clock::now();
        // Handle events on queue
        glfwPollEvents();

        // Check if we are still running
        // glfwWindowShouldClose returns true if the user pressed the 'esc' key
        // or clicked the 'x' in the corner of the window.
        if (glfwWindowShouldClose(mWindow) == 1) {
            quit = true;
        }

        // Update
        update();
        // Render
        render();

        timer.update();
        std::cout << std::fixed << std::setprecision(3) << "FPS: " << timer.avgFPS << std::endl;
    }
}