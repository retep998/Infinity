#include "Global.h"
namespace View {
    Vector2u32 Size;
    Vector2u64 Pos;
    Vector2f32 Posf;
    void Resize(uint32_t width, uint32_t height) {
        glViewport(0, 0, width, height);
        Size.X = width;
        Size.Y = height;
    }
    void Init() {
        Pos.X = 0;
        Pos.Y = 0;
    }
    void Update() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) Posf.Y -= Time::Delta*10;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) Posf.X -= Time::Delta*10;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) Posf.Y += Time::Delta*10;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) Posf.X += Time::Delta*10;
    }
}