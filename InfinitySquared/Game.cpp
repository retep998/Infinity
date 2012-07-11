#include "Global.h"
namespace Game {
    bool Over = false;
    void Run() {
        Time::Init();
        Window::Init();
        Graphics::Init();
        Chunk::Init();
        Chunk* c = new Chunk();
        while (!Over) {
            Time::Update();
            Window::HandleEvents();
            Graphics::Clear();
            c->Render();
            Window::Display();
        }
    }
}