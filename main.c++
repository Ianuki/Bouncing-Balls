#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>
#include <vector>
#include <string>

#include "ball.h"

int main(int Argc, char * Argv[]) { 
    const int screen_width = 1200;
    const int screen_height = 800;

    SetConsoleTitleA("- Debugging -");
    sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Balls", sf::Style::Default);
    window.setFramerateLimit(60);

    std::vector<ball*> balls;
    bool paused = false;

    while (window.isOpen()) {
        window.clear();

        sf::Event win_event;

        while (window.pollEvent(win_event)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || win_event.type == sf::Event::Closed) {
                window.close();
                exit(0);
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                for (int i = 0; i < 1; i++) {
                    ball* b = new ball(window);
                    balls.push_back(b);
                }
            }

            if ((win_event.type == sf::Event::KeyPressed) && (win_event.key.code == sf::Keyboard::R)) {
                std::cout << "Resetting\n";

                balls.clear();
            }

            if ((win_event.type == sf::Event::KeyPressed) && (win_event.key.code == sf::Keyboard::Space)) {
                paused = !paused;
            }
        }

        for (ball* b : balls) {
            if (!paused) {
                b->update();
            }

            b->check_for_collisions(balls, window);
            b->draw(window);
        }

        char title_buffer[100]; 
        snprintf(title_buffer, sizeof(title_buffer), "Balls count: %d | FPS: %f", balls.size(), 60.f);

        window.setTitle(std::string(title_buffer));
        window.display();
    }

	return 0;
}
