#include "../Global.h"
#include "../Common.h"
ofstream Log("log.txt");
int main() {
    sf::Window win(sf::VideoMode(512, 512), "Lol");
    glewInit();
    Shader f("Frag", Shader::Fragment);
    Shader v("Vert", Shader::Vertex);
    Program p;
    p.Attach(f);
    p.Attach(v);
    for (;;) {
        sf::Event e;
        while (win.pollEvent(e)) switch (e.type) {
        case sf::Event::Closed:
            exit(0);
            break;
        }
        win.display();
    }
    //Game::Run();
    return EXIT_SUCCESS;
}