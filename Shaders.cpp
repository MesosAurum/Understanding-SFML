#include <iostream>
#include <string.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

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
	
	sf::Vector2u windowSize = { 640, 360 };
	sf::VideoMode videoMode = sf::VideoMode(windowSize);
	std::string title = "Tutorials";
	sf::RenderWindow window(sf::RenderWindow(videoMode, title));
	window.setFramerateLimit(60);

	sf::Clock clock;
	sf::Time time;

	time = clock.restart();

	//Textures we will work with.
	sf::Texture *texture = new sf::Texture();
	sf::Texture *texture2 = new sf::Texture();
	if(!texture->loadFromFile("Sprites/TextureExample.png")) {

		std::cerr << "ERROR::COULD_NOT_LOAD_TEXTURE_FROM_FILE!!!" << std::endl;
	}
	if(!texture2->loadFromFile("Sprites/HilbertCurve.png")) {

		std::cerr << "ERROR::COULD_NOT_LOAD_TEXTURE_FROM_FILE!!!" << std::endl;
	}

	sf::Shader shader;
	//Checks if the system this is running on will be able to use shaders.
	if(!shader.isAvailable()) {

		std::cerr << "SHADERS_WILL_NOT_WORK_ON_THIS_SYSTEM!!!" << std::endl;
	}
	//Checks if the system this is running on will be able to use geometry shaders.
	if(!shader.isGeometryAvailable()) {

		std::cerr << "GEOMETRY_SHADERS_WILL_NOT_WORK_ON_THIS_SYSTEM!!!" << std::endl;
	}
	//Our shader addresses
	std::string vertexAddress = "Shaders.vert";
	std::string fragmentAddress = "Shaders.vert";
	//May support different types of shaders, or just a vertex and fragment shader (in that order).
	if(!shader.loadFromFile("Shaders.vert", "Shaders.frag")) {

		std::cerr << "ERROR::COULD_NOT_LOAD_SHADER_FROM_FILE!!!" << std::endl;
	}

	sf::Vector2f windowSizeF = sf::Vector2f(windowSize);

	//Rectangles to hold the textures we will use.
	sf::RectangleShape rectangle0{ windowSizeF };
	rectangle0.setTexture(texture);
	sf::RectangleShape rectangle1{ windowSizeF };
	rectangle1.setTexture(texture2);

	//Sending our texture to the fragment shader.
	shader.setUniform("image", *rectangle0.getTexture());
	//Sending our windowSize to the vertex shader.
	shader.setUniform("iResolution", windowSizeF);

	while(window.isOpen()) {

		//Update
		PollEvents(window);

		time = clock.getElapsedTime();

		//Sending our elapsed time to the fragment shader.
		shader.setUniform("iTime", time.asSeconds());

		//Getting the position of our mouse.
		sf::Vector2i pixel = sf::Mouse::getPosition(window);
		sf::Vector2f mousePos = window.mapPixelToCoords(pixel);
		mousePos = mousePos.componentWiseDiv(sf::Vector2f(window.getSize()));
		//This lines up our mousePos with the 'pos'/'uv' clip-space.
		mousePos -= sf::Vector2f(0.5f, 0.5f);
		//Sending the mouse position to the fragment shader.
		shader.setUniform("mousePos", mousePos);

		//Render
		window.clear();

		//Drawing

		window.draw(rectangle1);
		//The drawable figure we want to use with our shader must come first in .draw()
		//then the referenced shader.
		window.draw(rectangle0, &shader);

		window.display();
	}
	return 0;
}
