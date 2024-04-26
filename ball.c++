#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib> 

#include "ball.h"

float deg_to_rad(float degree) {
	return degree * (3.14159265359 / 180);
}

/* Constructors */
ball::ball(sf::RenderWindow &window) {
	this->radius = rand() % 50 + 10;
	this->speed = this->radius / 4;
	this->direction = rand() % 360;
	this->position = sf::Vector2f(sf::Mouse::getPosition(window).x - this->radius, sf::Mouse::getPosition(window).y - this->radius);
	this->color = sf::Color(rand() % 255, rand() % 255, rand() % 255);
}
ball::~ball() {
	delete this;
}

/* Functions */
void ball::draw(sf::RenderWindow &window) {
	sf::CircleShape ball_drawing;
	ball_drawing.setRadius(this->radius);
	ball_drawing.setFillColor(this->color);
	ball_drawing.setPosition(this->position);

	window.draw(ball_drawing);
}
bool ball::check_for_collisions(std::vector<ball*> balls, sf::RenderWindow &window) {
	bool collided = false;

	if (balls.size() > 0) {
		for (ball* b : balls) {
			float distance = sqrt(pow((b->position.x - this->position.x), 2) + pow((b->position.y + this->position.y), 2));
		}
	}

	if (this->position.x <= 0) {
		this->position.x = 1;
		this->direction = 360 - this->direction * 2;
		collided = true;
	}
	if (this->position.x >= window.getSize().x - this->radius * 2) {
		this->position.x = window.getSize().x - this->radius * 2 - 1;
		this->direction = 360 + this->direction * 2;
		collided = true;
	}
	if (this->position.y <= 0) {
		this->position.y = 1;
		this->direction = 360 - this->direction;
		collided = true;
	}
	if (this->position.y >= window.getSize().y - this->radius * 2) {
		this->position.y = window.getSize().y - this->radius * 2 - 1;
		this->direction = 360 - this->direction;
		collided = true;
	}

	return collided;
}
void ball::update() {
	this->position = sf::Vector2f(this->position.x + cos(deg_to_rad(this->direction)) * this->speed, this->position.y - sin(deg_to_rad(this->direction)) * this->speed);
}

