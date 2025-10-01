#include <iostream>
#include <string.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>

static void PollEvents(sf::RenderWindow &window) {

	while(const std::optional event = window.pollEvent()) {

		if(event->is<sf::Event::Closed>()) {

			window.close();
		}
		else if(const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {

			if(keyPressed->scancode == sf::Keyboard::Scancode::Escape) {

				window.close();
			}
		}
	}
}
int main() {

	const float tau = 6.28318530f;

	sf::Vector2u windowSize = { 640, 360 };
	sf::VideoMode videoMode = sf::VideoMode(windowSize);
	std::string title = "Tutorials";
	sf::RenderWindow window(sf::RenderWindow(videoMode, title));
	window.setFramerateLimit(60);

	//We may set a radius of the circle at start.
	sf::CircleShape circle{ 60.0f };
	//Or we may change it later on using setRadius.
	circle.setRadius(60.0f);
	//setOrigin sets where our shape will transform around.
	//getGeometricCenter returns the center of a shape.
	circle.setOrigin(circle.getGeometricCenter());
	//setPosition sets where our shape will be relative to the shapes origin.
	circle.setPosition(sf::Vector2f(windowSize) * 0.5f);
	//setFillColor sets the color of the internal bounds of our shape.
	circle.setFillColor(sf::Color::Green);
	//setOutlineThickness sets how thick an outline of our shape will be.
	circle.setOutlineThickness(3.0);
	//setOutlineColor sets the color of said outline.
	circle.setOutlineColor(sf::Color::Blue);
	//setPointCount sets what n-regular-Polygon will be displayed.
	circle.setPointCount(3);

	//getPointCount returns the number of points in a shape.
	for(unsigned int i = 0; i < circle.getPointCount(); ++i) {

		//getPoint will return an indexed point that makes up a shape.
		sf::Vector2f point = circle.getPoint(i);
		std::cout << "X: " << point.x << std::endl;
		std::cout << "Y: " << point.y << std::endl;
		std::cout << std::endl;
	}
	//We may set the size of the rectangle at start.
	sf::RectangleShape rectangle{ { 34.0f, 55.0f } };
	//Or we may change it later on using setSize.
	rectangle.setSize({ 34.0f, 55.0f });
	rectangle.setPosition(sf::Vector2f(windowSize) * 0.25f);
	rectangle.setFillColor(sf::Color(0xFF0F00FF));
	rectangle.setOutlineThickness(3.0f);
	rectangle.setOutlineColor(sf::Color(0x7DF9FFFF));
	rectangle.setRotation(sf::radians(137.5f));

	sf::ConvexShape convex;
	//The number of points in a convex shape must be set, 
	//they may be set at start as well using {} just like with the radius of circleShape and size of rectangleShape.
	convex.setPointCount(6);
	//Each point of the convex shape must be set, or the shape will have any points not set at {0.0, 0.0}.
	convex.setPoint(0, { 53.0f, -39.0f });
	convex.setPoint(1, { 0.0f, -64.0f });
	convex.setPoint(2, { -68.0f, -53.0f });
	convex.setPoint(3, { -60.0f, 42.0f });
	convex.setPoint(4, { -12.0f, 42.0f });
	convex.setPoint(5, { 12.0f, 24.0f });
	convex.setPosition(sf::Vector2f(windowSize) * 0.75f);
	convex.setFillColor(sf::Color(0x50C878FF));
	convex.setOutlineThickness(2.0f);
	convex.setOutlineColor(sf::Color(0xAF3787FF));
	
	//If using a convex shape, the outline will not always work correctly if the shape is not really convex.
	//However the filled portion of the shape will still work correctly in either case.

	while(window.isOpen()) {

		//Update
		PollEvents(window);

		//Render
		window.clear();

		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::Vector2f mousePosF = window.mapPixelToCoords(mousePos);
		sf::Vector2f d = mousePosF - circle.getPosition();
		float theta = atan2(d.y, d.x);

		if(sqrt(d.x * d.x + d.y * d.y) > circle.getRadius()) {

			sf::Vector2f dir = sf::Vector2f(cos(theta), sin(theta));
			dir *= 3.0f;
			circle.move(dir);
		}
		theta += tau * 0.25f;
		circle.setRotation(sf::radians(theta));

		//Drawing
		window.draw(circle);
		window.draw(rectangle);
		window.draw(convex);

		window.display();
	}
	return 0;
}
