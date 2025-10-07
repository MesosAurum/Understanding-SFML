#include <iostream>
#include <string.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

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

	sf::Texture texture;
	sf::Texture otherTexture;
	//Loads the texture from a given file,
	//If the file cannot load from the file this will return false and we send an error.
	//Able to set sRGB space to true for texture, by default this is false.
	//Able to set the size of our texture rectangle, this by default matches the size of the input texture,
	//but we may make this larger or smaller, 
	//this may cut off textures or if we have many textures on a sheet then "focus" on a specific texture.
	if(!texture.loadFromFile("Sprites/textureExample.png", false, { { 0, 0 }, { 32, 32 } })) {

		std::cerr << "ERROR!!!::COULD_NOT_LOAD_FROM_FILE::" << "Sprites/textureExample.png" << std::endl;
	}
	if(!otherTexture.loadFromFile("Sprites/DefaultTexture.png")) {

		std::cerr << "ERROR!!!::COULD_NOT_LOAD_FROM_FILE::" << "Sprites/textureExample.png" << std::endl;
	}
	//Returns the maximum width/height of a texture allowed,
	//so the largest possible texture size would be getMaximumSize()^2.
	std::cout << "Maximum texture size: " << texture.getMaximumSize() << std::endl;
	//Returns the texture size in the x-axis.
	std::cout << "Texture X: " << texture.getSize().x << std::endl;
	//Returns the texture size in the y-axis.
	std::cout << "Texture Y: " << texture.getSize().y << std::endl;
	//Sets whether the texture is repeated,
	//(only works if our sprites texture rectangle is larger than the texture itself).
	texture.setRepeated(true);
	//Checks if the texture is repeated.
	std::cout << "Repeated?: " << texture.isRepeated() << std::endl;
	//Sets the texture to smooth,
	//I don't like using this so I always set it to false.
	texture.setSmooth(false);
	//checks if the texture is smooth.
	std::cout << "Smooth?: " << texture.isSmooth() << std::endl;
	//Swaps this texture with another texture and its settings
	//texture.swap(otherTexture);
	//Checks whether the texture is in the sRGB space (must be set in loadFromFile()).
	std::cout << "Is sRGB?: " << texture.isSrgb() << std::endl;

	sf::Sprite sprite{ texture };
	sf::Vector2f textureSize = sf::Vector2f(sprite.getTexture().getSize());
	//Setting the center of our sprite's transform.
	sprite.setOrigin(0.5f * textureSize);
	//Setting the translation of our sprite.
	sprite.setPosition(0.5f * sf::Vector2f(windowSize));
	//Setting the sprite to a larger size for it to be seen easier.
	sprite.setScale({ 3.0f, 3.0f });
	//If we resize the textureRectangle to a larger size than the texure size,
	//and the texture is 'repeated' then the texture will be tiled.
	sprite.setTextureRect({ { 0, 0 }, { 64, 64 } });
	//getTexture() returns the texture that our sf::Sprite is "holding".
	texture = sprite.getTexture();
	//We may change the coloring our our sprite, best used if the texture is in grayscale.
	sprite.setColor(sf::Color(0x98FB98FF));

	while(window.isOpen()) {

		//Update
		PollEvents(window);

		//Render
		window.clear();

		//Drawing
		window.draw(sprite);

		window.display();
	}
	return 0;
}
