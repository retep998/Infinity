#include "Global.h"
namespace Game {
    bool Over = false;
    void Run() {
        Time::Init();
        Window::Init();
        Graphics::Init();
        View::Init();
        Chunk::Init();
        Chunk* c = new Chunk();
        while (!Over) {
            Time::Update();
            Window::HandleEvents();
            View::Update();
            Graphics::Clear();
            c->Render();
            Window::Display();
            GLenum e = glGetError();
		    switch (e) {
		    case GL_NO_ERROR:                                                             break;
		    case GL_INVALID_ENUM:                  cout << "Invalid enum"        << endl; break;
		    case GL_INVALID_VALUE:                 cout << "Invalid enum"        << endl; break;
		    case GL_INVALID_OPERATION:             cout << "Invalid operation"   << endl; break;
		    case GL_INVALID_FRAMEBUFFER_OPERATION: cout << "Invalid framebuffer" << endl; break;
		    case GL_OUT_OF_MEMORY:                 cout << "Out of memory"       << endl; break;
            default:                               cout << "Unknown error"       << endl; break;
		    }
        }
    }
}