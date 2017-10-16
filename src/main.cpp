#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#define WINDOW_X 500
#define WINDOW_Y 500

bool check_Collision(sf::CircleShape* circle, sf::RectangleShape* rectangle)
{
	sf::Vector2f circle_position = circle->getPosition();
	sf::Vector2f rectangle_position = rectangle->getPosition();

	if (abs(circle_position.x - rectangle_position.x) <= circle->getRadius() * sqrt(M_PI) && abs(circle_position.y - rectangle_position.y) <= circle->getRadius() * sqrt(M_PI))
	{
		return true;
	}

	return false;
}

bool check_Allowed_Location(sf::CircleShape* circle, float move_x, float move_y) 
{
	sf::Vector2f circle_position = circle->getPosition();
	float circle_diameter = 2 * circle->getRadius();

	if (move_x > 0 || move_y > 0)
	{
		if (circle_position.x + circle_diameter + move_x > WINDOW_X || circle_position.y + circle_diameter + move_y > WINDOW_Y) 
		{
			return false;
		}
	}
	if (move_x < 0 || move_y < 0) 
	{
		if (circle_position.x + move_x < 0 || circle_position.y + move_y < 0) 
		{
			return false;
		}
	}

	return true;
}

int main()
{
	float circle_radius = 50.f;
	float circle_speed = 5.0;
	sf::Color circle_color = sf::Color::Blue;

	float square_side = 100.f;
	sf::Color square_color = sf::Color::Green;
	sf::Vector2f square_position;
	square_position.x = WINDOW_X - (WINDOW_X / sqrt(2));
	square_position.y = WINDOW_Y - (WINDOW_Y / sqrt(2));	

	sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "CircleSquare");
	window.setFramerateLimit(60.f);

	sf::CircleShape moving_circle(circle_radius);
	moving_circle.setFillColor(circle_color);

	sf::RectangleShape static_square(sf::Vector2f(square_side, square_side));
	static_square.setFillColor(square_color);
	static_square.setPosition(square_position);

	while (window.isOpen())
	{
		sf::Vector2f delta_move;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && check_Allowed_Location(&moving_circle, -1.0f, 0))
		{
			delta_move.x -= 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && check_Allowed_Location(&moving_circle, 1.0f, 0))
		{
			delta_move.x += 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && check_Allowed_Location(&moving_circle, 0, -1.0f))
		{
			delta_move.y -= 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && check_Allowed_Location(&moving_circle, 0, 1.0f))
		{
			delta_move.y += 1.0f;
		}
		
		moving_circle.setPosition(moving_circle.getPosition() + circle_speed * delta_move);
		
		if (check_Collision(&moving_circle, &static_square))
		{
			moving_circle.setFillColor(sf::Color::Red);
			static_square.setFillColor(sf::Color::Red);
		}
		else
		{
			moving_circle.setFillColor(circle_color);
			static_square.setFillColor(square_color);
		}

		window.clear();
		window.draw(static_square);
		window.draw(moving_circle);
		window.display();
	}

	return 0;
}