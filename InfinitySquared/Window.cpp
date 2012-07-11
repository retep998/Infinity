#include "Global.h"
namespace Window {
    sf::Window* Win;
    void Init() {
        Win = new sf::Window(sf::VideoMode(800, 600, 32), "InfinitySquared", sf::Style::Default, sf::ContextSettings(0, 0, 0, 3, 3));
        glewInit();
    }
    void HandleEvents() {
        sf::Event e;
        while (Win->pollEvent(e)) {
            switch (e.type) {
            case sf::Event::Closed:
                Game::Over = true;
                break;
            case sf::Event::Resized:
                View::Resize(e.size.width, e.size.height);
                break;
            }
        }
    }
    void Display() {
        Win->setTitle(to_string(Time::FPS));
        Win->display();
    }
    void Resize(uint32_t width, uint32_t height) {
        Win->setSize(sf::Vector2u(width, height));
        View::Resize(width, height);
    }
}