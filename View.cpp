#include <iostream>
#include <string.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

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

	srand(static_cast<unsigned int>(std::time(NULL)));

	sf::Vector2u windowSize = { 640, 360 };
	sf::VideoMode videoMode = sf::VideoMode(windowSize);
	std::string title = "Tutorials";
	sf::RenderWindow window(sf::RenderWindow(videoMode, title));
	window.setFramerateLimit(60);

	sf::Image image{ "Sprites/textureExample.png" };
	window.setIcon(image);

	image.resize(windowSize);

	//Generating pattern to show view being zoomed in.
	//Steven wolfram's cellular automata.
	std::array<bool, 640> board0 = {};
	std::array<bool, 640> board1 = {};
	//Rule 30 for default.
	//30 here is in binary written backwards.
	const unsigned int rules[8] = { 0, 1, 1, 1, 1, 0, 0, 0 };
	for(unsigned int x = 0; x < windowSize.x; ++x) {

		board0[x] = rand() % 2;
		board1[x] = board0[x];
	}
	for(unsigned int y = 0; y < windowSize.y; ++y) {
		for(unsigned int x = 0; x < windowSize.x; ++x) {

			board1[x] = board0[x];
		}
		for(unsigned int x = 0; x < windowSize.x; ++x) {

			int l = (x - 1) % (windowSize.x - 1);
			int m = x;
			int r = (x + 1) % (windowSize.x - 1);

			l = board1.at(l);
			m = board1.at(m);
			r = board1.at(r);
			for(int i = 0; i < 8; ++i) {

				unsigned int bit0 = i % 2;
				unsigned int bit1 = int(floor(i / 2)) % 2;
				unsigned int bit2 = int(floor(i / 4)) % 2;

				if(l == bit2 && m == bit1 && r == bit0) {

					board0[x] = rules[i];
				}
			}
			std::uint8_t c = m * 0xFF;

			sf::Color color = sf::Color(c, c, c, 255);
			image.setPixel({ x, y }, color);
		}
	}

	sf::Texture texture;
	if(!texture.resize(image.getSize())){

		std::cerr << "ERROR::COULD_NOT_RESIZE_TEXTURE!!!" << std::endl;
	}
	texture.update(image);

	sf::Sprite sprite{ texture };

	sf::RectangleShape rectangle;
	rectangle.setSize({ 1.0f, 2.0f });
	rectangle.setOrigin(rectangle.getGeometricCenter());
	rectangle.setFillColor(sf::Color::Green);
	rectangle.setPosition(0.5f * sf::Vector2f(windowSize));

	//We can set the center (where the view is centered around) where the view is positioned,
	//and the size of the view (how large the window is) in pixels.
	sf::View view0({ rectangle.getPosition(), { 16.0, 9.0f } });
	//Using setSize() we can also set the size of the view.
	view0.setSize({ 32.0f, 9.0f });
	//Using setCenter() we can also set the center of the view.
	view0.setCenter({ rectangle.getPosition() });
	//Zooms into the scene,
	//under 1 is zooming in,
	//over 1 is zooming out.
	view0.zoom(2.0f);
	view0.setRotation(sf::radians(0.2f));
	//Cuts the viewport,
	//size and position are normalized (0 is 0, 1 is window x and y normalized position/size.
	//First set of coordinates states where the cut starts from, second set is the size of the cut.
	view0.setScissor({ { 0.0f, 0.0f }, { 0.5f, 1.0f } });
	//Setting viewport,
	//this will change the sf::FloatRect which the view is displayed in.
	view0.setViewport({ { 0.0f, 0.0f }, { 1.0, 0.5f } });

	sf::View view1;
	view1.setSize({ 32.0f, 9.0f });
	view1.setCenter({ rectangle.getPosition() });
	view1.setViewport({ { 0.0f, 0.5f }, { 1.0, 0.5f } });

	//getSize() returns the size of the view
	//getCenter() returns where the position of the view is centered over.
	std::cout << "View size X: " << view0.getSize().x << std::endl;
	std::cout << "View size Y: " << view0.getSize().y << std::endl;
	std::cout << "View center X: " << view0.getCenter().x << std::endl;
	std::cout << "View center Y: " << view0.getCenter().y << std::endl;

	//getViewport() returns the sf::FloatRect Viewport where the view is shown.
	sf::FloatRect viewPort = view0.getViewport();
	std::cout << "Viewport position X: " << viewPort.position.x << std::endl;
	std::cout << "Viewport position Y: " << viewPort.position.y << std::endl;
	std::cout << "Viewport size X: " << viewPort.size.x << std::endl;
	std::cout << "Viewport size Y: " << viewPort.size.y << std::endl;

	//Setting the view of the window.
	//This changes what our window will display.
	window.setView(view0);

	float velocity = 0.1f;
	while(window.isOpen()) {

		//Update
		PollEvents(window);

		//Moving the rectangle to show off the view moving with our rectangle.
		float x = 0.0f;
		float y = 0.0f;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {

			y = -velocity;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {

			y = velocity;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {

			x = -velocity;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {

			x = velocity;
		}
		rectangle.move({ x, y });

		view0.setCenter({ rectangle.getPosition() });
		window.setView(view0);

		//Render
		window.clear();

		//Drawing
		window.draw(sprite);
		window.draw(rectangle);

		//Change view and draw again to show the second view.
		window.setView(view1);
		window.draw(sprite);
		window.draw(rectangle);

		window.display();
	}
	return 0;
}
