#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <cmath>

#include "ball.h"

int main(int argc, char * argv[]) { 
    const unsigned int screen_width = 1200;
    const unsigned int screen_height = 800;
    const unsigned int max_frame_rate = 60;

    SetConsoleTitleA("- Debugging -");

    sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Balls", sf::Style::Default);
    window.setFramerateLimit(max_frame_rate);
    window.setVerticalSyncEnabled(true);

    std::vector<ball*> balls;
    bool paused = false;

    int fps = 0;

    while (window.isOpen()) {
        clock_t start = clock();
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

        window.display();
        window.clear();

        if (!paused) {
            fps = 1.f / (clock() - start) * 1000.f;
            
            if (fps > max_frame_rate) {
                fps = max_frame_rate;
            }
        }

        char title_buffer[100];
        snprintf(title_buffer, sizeof(title_buffer), "Balls count: %d | FPS: %d", balls.size(), fps);

        window.setTitle(std::string(title_buffer));
    }

	return 0;
}
