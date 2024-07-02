#include "Engine.h"

Engine::Engine() :
    WindowContainer()
{
}

void Engine::run(HINSTANCE hInstance)
{
    this->Initialize();
    if (this->InitializeWindow( hInstance, "jAzul Graphics API", "jAzul Graphics API Window Class)", 
                                this->graphicsEngine.GetWidth(), this->graphicsEngine.GetHeight())) 
    {
        this->LoadContent(); 

        this->mTimer.Reset();
        while (this->ProcessMessages()) {
            mTimer.Tick();
            this->CalculateFrameStats();

            this->Update();
            this->Draw();
            this->privRenderFrame();
        }
    }

    this->UnLoadContent();
}

bool Engine::InitializeWindow(HINSTANCE hInstance, std::string _window_title, std::string _window_class, int _width, int _height)
{
    bool result = this->windowRenderer.Initialize(hInstance, this, _window_title, _window_class, _width, _height);

    if (result)
        result = this->graphicsEngine.Initialize(this->windowRenderer.GetHandle(), _width, _height);

    return result;
}

bool Engine::ProcessMessages()
{
    return this->windowRenderer.ProcessMessages();
}

void Engine::SetWindowName(const char * const WindowName)
{
    this->windowRenderer.SetWindowName(WindowName);
}

void Engine::SetWidthHeight(const int width, const int height)
{
    this->graphicsEngine.SetWidth(width);
    this->graphicsEngine.SetHeight(height);
}

const int Engine::GetWidth() const
{
    return this->graphicsEngine.GetWidth();
}

const int Engine::GetHeight() const
{
    return this->graphicsEngine.GetHeight();
}

void Engine::SetBackgroundColor(const float R, const float G, const float B, const float A)
{
    this->graphicsEngine.SetBackgroundColor(R, G, B, A);
}

void Engine::SetBackgroundColor(const Vect& color)
{
    this->graphicsEngine.SetBackgroundColor(color);
}

const float Engine::GetTimeInSeconds() const
{
    return mTimer.TotalTime();
}

void Engine::CalculateFrameStats()
{
    // Code computes the average frames per second, and also the 
    // average time it takes to render one frame.  These stats 
    // are appended to the window caption bar.

    static int frameCnt = 0;
    static float timeElapsed = 0.0f;

    frameCnt++;

    // Compute averages over one second period.
    if ((mTimer.TotalTime() - timeElapsed) >= 1.0f)
    {
        float fps = (float)frameCnt; // fps = frameCnt / 1
        float mspf = 1000.0f / fps;

        std::string frameTime = "    FPS: " 
                            + std::to_string(fps) 
                            + "    Frame Time: " 
                            + std::to_string(mspf) + " (ms)";

        this->windowRenderer.UpdateWindowText(frameTime);

        // Reset for next average.
        frameCnt = 0;
        timeElapsed += 1.0f;
    }
}

void Engine::privRenderFrame()
{
    this->graphicsEngine.RenderFrame();
}

void Engine::PrintInputs()
{
    while (!kb.CharBufferIsEmpty()) {
        const unsigned char key = kb.ReadChar();
        std::string outMsg = "(Char) Key Pressed: ";
        outMsg += key;
        outMsg += "\n";

        OutputDebugStringA(outMsg.c_str());

    }

    while (!kb.KeyBufferIsEmpty()) {
        const KeyboardEvent kbe = kb.ReadKey();
        if (kbe.isPress()) {
            const unsigned char key = kbe.GetKeyCode();
            std::string outMsg = "(KeyDown) Key Pressed: ";
            outMsg += key;
            outMsg += "\n";

            OutputDebugStringA(outMsg.c_str());
        }
    }

    while (!mo.EventBufferIsEmpty()) {
        MouseEvent me = mo.ReadEvent();

        if (me.GetType() == MouseEvent::EventType::RAW_MOVE) {
            std::string outMsg = "(";

            outMsg += std::to_string(me.GetPosX());

            outMsg += ", ";

            outMsg += std::to_string(me.GetPosY());

            outMsg += ")\n";

            OutputDebugStringA(outMsg.c_str());
        }
    }
}
