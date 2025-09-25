#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

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

		if(const auto *mouseScrolled = event->getIf<sf::Event::MouseWheelScrolled>()) {

			std::cout << "Mouse delta: " << mouseScrolled->delta << std::endl;
		}
		if(event->getIf<sf::Event::MouseEntered>()) {

			std::cout << "Mouse has entered the screen!" << std::endl;
		}
		if(event->getIf<sf::Event::MouseLeft>()) {

			std::cout << "Mouse has exited the screen!" << std::endl;
		}
		if(event->getIf<sf::Event::MouseButtonPressed>()) {

			std::cout << "Mouse has a button being pressed!" << std::endl;
		}
	}
}
int main() {

	sf::Vector2u windowSize = { 640, 360 };
	sf::VideoMode videoMode = sf::VideoMode(windowSize);
	sf::String title = "Understanding S.F.M.L.";

	sf::RenderWindow window(videoMode, title, sf::Style::Default);
	window.setFramerateLimit(60);

	//Key is based on selected keyboard layout.
	//Scancode is based on the QWERTY AT-101 keyboard.
	//Scancode is the same as Scan.

	//Returns a scancode in a selected keyboard layout.
	sf::Keyboard::Scancode scanCode = sf::Keyboard::delocalize(sf::Keyboard::Key::S);
	//Returns a key in QWERTY keyboard.
	sf::Keyboard::Key keyCode = sf::Keyboard::localize(sf::Keyboard::Scancode::Z);

	//Returns a string of the scancode input.
	std::string str = sf::Keyboard::getDescription(sf::Keyboard::Scancode::C);
	std::cout << "Key description: " << str << std::endl;

	//Returns how many keys are in sf::Keyboard::Key, + 1 for any unknown.
	std::cout << "Key count: " << sf::Keyboard::KeyCount << std::endl;
	//Returns how many scancodes are in sf::Keyboard::Scan, + 1 for any unknown.
	std::cout << "Scancode count: " << sf::Keyboard::ScancodeCount << std::endl;

	//Will show virtual keyboard if your system supports it.
	sf::Keyboard::setVirtualKeyboardVisible(true);

	//Returns the amount of buttons in sf::Mouse::Button.
	std::cout << "Mouse button count: " << sf::Mouse::ButtonCount << std::endl;

	sf::Vector2i coords = window.mapCoordsToPixel({ 394.47f, 42.8472f });
	std::cout << "Coord x: " << coords.x << std::endl;
	std::cout << "Coord y: " << coords.y << std::endl;

	while(window.isOpen()) {

		//Updating
		PollEvents(window);

		//Checking if the delocalized key 's' is pressed.
		if(sf::Keyboard::isKeyPressed(scanCode)) {

			std::cout << "S key is pressed." << std::endl;
		}
		//Checking if the localized scancode 'z' is pressed.
		if(sf::Keyboard::isKeyPressed(keyCode)) {

			std::cout << "Z key is pressed." << std::endl;
		}

		//Checks if the left mouse button has been pressed.
		if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

			std::cout << "Left mouse button is pressed." << std::endl;
		}

		//Gets mouse position relative to the window.
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		//Converts pixel coordinates to world coordinates, but here our position is relative to the window.
		sf::Vector2f coords = window.mapPixelToCoords(mousePos);
		//Displaying pixel coords in terminal.
		std::cout << "coord x: " << coords.x << std::endl;
		std::cout << "coord y: " << coords.y << std::endl;
		std::cout << std::endl;

		//Rendering
		window.clear();

		window.display();
	}
	return 0;
}
