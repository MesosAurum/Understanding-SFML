#include <iostream>
#include <string.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>

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

	//Making a starting size of the window, 640 * 360 is easily scaled to other aspect ratios.
	sf::Vector2u windowSize = { 640, 360 };
	//VideoMode holds the window size and bitsPerPixel (later).
	sf::VideoMode videoMode = sf::VideoMode(windowSize);
	//Text here holds the text of the title bar.
	std::string title = "Understanding S.F.M.L.";
	//The window iteself.
	//Style may be:
	//Close = Window may only be minimized or closed.
	//Default = Window may be closed, minimized, maximized, or resized.
	//None = There is no titlebar, only the internal part of the window will be seen
	//and the window may not be moved.
	//Resize = The window may be resized, the title is shown.
	//Titlebar = The window title is shown.
	sf::RenderWindow window(videoMode, title, sf::Style::Default);
	//Sets the frame rate of the window to a specified amount.
	window.setFramerateLimit(60);
	//Synchronizes the frame rate of the window with the refresh rate of the user's monitor 
	//so there are no visual artifacts from drawing top to bottom.
	window.setVerticalSyncEnabled(true);

	//Sets the intput as the title.
	window.setTitle("Title");

	//CircleShape to use in sf::RenderWindow.
	sf::CircleShape circle(50.0f);
	circle.setFillColor(sf::Color::Green);
	circle.setOrigin(circle.getGeometricCenter());
	circle.setPosition(sf::Vector2f(window.getSize()) * 0.5f);

	//Sets the window invisible, window will also not show in taskbar.
	//window.setVisible(false);

	//When resizing this is the smallest size the window may be changed into.
	window.setMinimumSize(sf::Vector2u(640, 360));
	//When resizing this is the largest size the window may be changed into.
	window.setMaximumSize(sf::Vector2u(1280, 720));

	//Closes the window.
	//window.close();
	//Creates a new window based on inputs, same as when initializing the original window.
	//window.create(videoMode, text, sf::Style::Default);

	while(window.isOpen()) {
	
		//Poll events, ignore for now.
		PollEvents(window);
	
		//Checks whether the window is "clicked onto" (the window of focus).
		if(window.hasFocus()) {

			std::cout << "Window is being focused on!!!" << std::endl;
		}
		else {

			std::cout << "Window isn't being focused on!!!" << std::endl;
		}
		//Render
		//Clears anything drawn to the screen, a background color may be input.
		window.clear();
		
		//Draws anything of the sf::Drawable class to the screen, may have attributes like shaders added later.
		window.draw(circle);
	
		//Displays anything drawn to the screen.
		window.display();
	}
	return 0;
}
