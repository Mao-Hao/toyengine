#pragma once

#pragma comment(lib, "winmm.lib") // timeBeginPeriod
#include <Windows.h> // Include windows.h before glad. to avoid macro redefinition

#include <chrono>
#include <deque>
#include <iomanip>
#include <numeric>
#include <thread>

/*!
 * Timer class that takes care of managing the FPS of the game
 * and makes sure that it is capped at 60 FPS all the time.
 */
class Timer {
public:
    float avgFPS;

    /*!
     * Constructor that initializes the variables as well as the
     * first measurement of the ticks.
     */
    Timer(size_t FPS_)
    {
        timeBeginPeriod(1);	
		
        FPS = FPS_;
        avgFPS = (float)FPS;
        ticksPerTime = (long long)(1000.0f / FPS);
        startTicks = std::chrono::system_clock::now();
        frameCount = 0;
    }

    /*!
     * Default destructor.
     */
    ~Timer() { timeEndPeriod(1); }

    /*!
     * Function that takes care of the computation of the elapsed ticks
     * between frames and sets the Timer to sleep if the ticks are higher
     * than the desired ticks per frame. Finally, it computes the average
     * frames per second (FPS).
     */
    void update()
    {
        ++frameCount;
        // Compute elapsed ticks since starting the ticks above
        currTicks = std::chrono::system_clock::now();
        auto elapsedTicks = std::chrono::duration_cast<std::chrono::milliseconds>(currTicks - startTicks).count();
        //std::cout << "Elapsed ticks: " << elapsedTicks << std::endl;
        // If the elapsed ticks are higher than the desired per frame, we sleep
        if (elapsedTicks < ticksPerTime) {
            std::this_thread::sleep_for(std::chrono::milliseconds(ticksPerTime - elapsedTicks));
            currTicks = std::chrono::system_clock::now();
            elapsedTicks = std::chrono::duration_cast<std::chrono::milliseconds>(currTicks - startTicks).count();
        }

        // Update the curren ticks number after computing the elapsed ticks
        startTicks = currTicks;
        // Put the last frame time into our deque
        frameTimes.push_back(elapsedTicks);

        // If we have more frames than our frame count, remove the one on the front (oldest one)
        if (frameTimes.size() > FPS) {
            frameTimes.pop_front();
        }       

        float avgTicksPerFrame = accumulate(frameTimes.begin(), frameTimes.end(), 0.0f) / frameTimes.size();
        avgFPS = 1.0f / (avgTicksPerFrame / 1000.0f);
    }

private:
    // Initialize a deque to keep a history of frames to average on
    std::deque<long long> frameTimes;

    size_t FPS;
    
    int frameCount;
	
    long long ticksPerTime;

    std::chrono::system_clock::time_point startTicks;

    std::chrono::system_clock::time_point currTicks;
};