#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>

static void PollEvents(sf::RenderWindow &window) {

	//The pollEvent function checks if there is a queued event happening.
	while(const std::optional event = window.pollEvent()) {

		//Checks if the close button has been clicked.
		if(event->is<sf::Event::Closed>()) {

			window.close();
		}
		//Checks if any key on the keyboard has been pressed.
		if(const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {

			std::cout << "Keyboard has been used!" << std::endl;
			//Checks if the escape key has been pressed.
			if(keyPressed->scancode == sf::Keyboard::Scancode::Escape) {

				window.close();
			}
		}
		//Checks if any character on the keyboard has been typed.
		if(const auto *textEntered = event->getIf<sf::Event::TextEntered>()) {

			char chr = static_cast<char>(textEntered->unicode);
			std::cout << "Key: " << chr << std::endl;
		}
		//Checks if a mouse button has been pressed.
		if(const auto *mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {

			//Checks if the left mouse button has been pressed.
			if(mousePressed->button == sf::Mouse::Button::Left) {

				std::cout << "Left mouse button pressed!" << std::endl;
			}
			else if(mousePressed->button == sf::Mouse::Button::Right) {//Checks if the right mouse button has been pressed.

				std::cout << "Right mouse button pressed!" << std::endl;
			}
		}
		//Checks if the mouse has left the screen.
		if(event->is<sf::Event::MouseLeft>()) {

			std::cout << "Mouse left the screen!" << std::endl;
		}
		else if(event->is<sf::Event::MouseEntered>()) {//Checks if the mouse has entered the screen.

			std::cout << "Mouse has entered the screen!" << std::endl;
		}
		//Checks if the mouse has moved inside the screen.
		if (event->is<sf::Event::MouseMoved>()) {

			std::cout << "Mouse has been moved within the screen!" << std::endl;
		}
		//Checks if the mouse has been moved at all.
		if(event->is<sf::Event::MouseMovedRaw>()) {

			std::cout << "Mouse has been moved!" << std::endl;
		}
		//Checks if the window has been focused onto (not at start-up).
		if(event->is<sf::Event::FocusGained>()) {

			std::cout << "Focus gained!" << std::endl;
		}
		//Checks if the window has been focused away from.
		if(event->is<sf::Event::FocusLost>()) {

			std::cout << "Focus lost!" << std::endl;
		}
		//Checks if the window has been resized.
		if(event->is<sf::Event::Resized>()) {

			std::cout << "Screen is resized!" << std::endl;
		}
	}
}
int main() {

	sf::Vector2u windowSize = { 640, 360 };
	sf::VideoMode videoMode = sf::VideoMode(windowSize);
	sf::RenderWindow *window = new sf::RenderWindow(videoMode, "Tutorials");
	window->setFramerateLimit(60);

	//Ignore circleShape for this episode.
	sf::CircleShape circle(5.0f);
	//Alpha channels may be included for colors (Transparency).
	circle.setFillColor(sf::Color(192, 255, 238, 0));
	circle.setOrigin(circle.getGeometricCenter());
	circle.setPosition(sf::Vector2f(windowSize) * 0.5f);

	while(window->isOpen()) {

		//Update
		PollEvents(*window);

		//A color may be called from the Color class Red, Yellow, Green, Cyan, Blue, Magenta, Black, and White.
		sf::Color color0 = sf::Color::Green;
		//RGB values may be input for specific colors.
		sf::Color color1 = sf::Color(100, 149, 237);
		//A hex number may be input for specific colors as well.
		sf::Color color3 = sf::Color(0x3F00FFFF);

		//Render
		window->clear(color3);

		//Drawing
		window->draw(circle);

		window->display();
	}

	delete window;
	return 0;
}
