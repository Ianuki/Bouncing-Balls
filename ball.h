#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class ball {
	public:
		int radius;
		float speed;
		float direction;
		sf::Vector2f position;
		sf::Color color;

		ball(sf::RenderWindow&);
		~ball();

		void draw(sf::RenderWindow&);
		bool check_for_collisions(std::vector<ball*>, sf::RenderWindow&);
		void update();
};
