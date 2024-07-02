#ifndef ENGINE_H
#define ENGINE_H

#include "WindowsContainer.h"
#include "GameTimer.h"

class Demo;

/// The Engine.
/// 
/// This class provides functionality to initialize, run, and manage the game engine, including window creation,
/// message processing, and handling graphics-specific initialization, content loading, updating, drawing, and unloading.
/// 
/// To use jAzul as you Graphics API, you need to begin by extending this class and creating your own engine
/// 
/// @see WindowContainer
/// @see jAzul
class Engine : public WindowContainer
{
public:
    Engine(); ///< Default constructor.
    Engine(const Engine& other) = default; ///< Copy constructor.
    Engine& operator=(const Engine& other) = default; ///< Copy assignment operator.
    Engine(Engine&& other) = default; ///< Move constructor.
    Engine& operator=(Engine&& other) = default; ///< Move assignment operator.
    virtual ~Engine() = default; ///< Destructor.

    /// Run the engine.
    /// 
    /// below is what the internal loop of jAzul's engine is doing
    /// 
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
    /// this->Update();             // calls your class' Update
    /// this->Draw();               // calls your class' Draw
    /// this->privRenderFrame();    // renders the frame
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// 
    /// @see jAzul
    /// 
    /// @param hInstance Handle to the application instance.
    void run(HINSTANCE hInstance);

    /// Initialize the scene window.
    /// 
    /// called once when the engine is first booted up
    /// 
    /// @param hInstance Handle to the application instance.
    /// @param _window_title Title of the window.
    /// @param _window_class Class name of the window.
    /// @param _width Width of the window.
    /// @param _height Height of the window.
    /// @return True if initialization is successful, false otherwise.
    bool InitializeWindow(HINSTANCE hInstance, std::string _window_title = "jAzul Graphics API", std::string _window_class = "jAzul Graphics API", int _width = 800, int _height = 600);

    /// Process window messages.
    /// 
    /// @see WindowContainer
    /// 
    /// @return True if messages are processed, false otherwise.
    bool ProcessMessages();

    /// @brief Initialize game-specific resources.
    virtual void Initialize() = 0;

    /// @brief Load game-specific content.
    virtual void LoadContent() = 0;

    /// @brief Update the game state.
    virtual void Update() = 0;

    /// @brief Draw the game.
    virtual void Draw() = 0;

    /// @brief Unload game-specific content.
    virtual void UnLoadContent() = 0;

protected:
    /// @brief Set the name of the window.
    /// @param WindowName The name of the window.
    void SetWindowName(const char* const WindowName);

    /// @brief Set the width and height of the window.
    /// @param width The width of the window.
    /// @param height The height of the window.
    void SetWidthHeight(const int width, const int height);

    /// @brief Get the width of the window.
    /// @return The width of the window.
    const int GetWidth() const;

    /// @brief Get the height of the window.
    /// @return The height of the window.
    const int GetHeight() const;

    /// @brief Set the background color of the window.
    /// @param R Red component.
    /// @param G Green component.
    /// @param B Blue component.
    /// @param A Alpha component (default is 1.0f).
    void SetBackgroundColor(const float R, const float G, const float B, const float A = 1.0f);

    /// @brief Set the background color of the window.
    /// @param color The color vector.
    void SetBackgroundColor(const Vect& color);

    /// @brief Get the elapsed time in seconds.
    /// @return The elapsed time in seconds.
    const float GetTimeInSeconds() const;

private:
    /// @brief Calculate frame statistics.
    /// 
    /// This function is called every frame internally
    void CalculateFrameStats();

    /// @brief Render a frame.
    /// 
    /// This function is called every frame internally
    void privRenderFrame();

    /// @brief Print input information.
    void PrintInputs();

private:
    GameTimer mTimer; ///< Game timer.
};

#endif // ENGINE_H
