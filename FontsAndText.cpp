#include <iostream>
#include <string.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

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

	sf::Font font;
	//Opening font from file, if we can't open the file, we send an error.
	if(!font.openFromFile("Fonts/arial.ttf")) {

		std::cerr << "ERROR::COULD_NOT_LOAD_FROM_FILE::MAIN::Fonts/arial.ttf" << std::endl;
	}
	//Smooths font, makes pixels blurred together.
	font.setSmooth(false);
	//Checks if the font has been set smooth or not.
	std::cout << "Is smooth?: " << font.isSmooth();

	//Gives the typeface family.
	std::cout << "Family: " << font.getInfo().family << std::endl;
	//Gives the kerning amount (Think about it as overlap of characters).
	std::cout << "Kerning: " << font.getKerning('A', 'B', 12, false) << std::endl;
	//Gives how many pixels are between each line of text.
	std::cout << "Line spacing: " << font.getLineSpacing(12) << std::endl;
	//Gives how far below font to put an underline.
	std::cout << "Underline depth: " << font.getUnderlinePosition(12) << std::endl;
	//Gets the vertical thickness of the underline.
	std::cout << "Underline thickness: " << font.getUnderlineThickness(12) << std::endl;

	char glyph = '&';
	//Checks if the font has a specific glyph in its unicode subset.
	std::cout << "Does the font have this glyph " << glyph << "?:" << font.hasGlyph(glyph) << std::endl;

	sf::Text text(font, "Hello, world!\nHow do you do?", 24);
	text.setOrigin(text.getGlobalBounds().size * 0.5f);
	text.setPosition(sf::Vector2f(windowSize) * 0.5f);

	//Only one of these will work at a time unless using '|' to separate styles.
	//The text will be unchanged.
	text.setStyle(sf::Text::Regular);
	//Makes the text bolded.
	text.setStyle(sf::Text::Bold);
	//Sets the text to an italic style.
	text.setStyle(sf::Text::Italic);
	//Puts an underline in the text.
	text.setStyle(sf::Text::Underlined);
	//Puts a line through the center of the text.
	text.setStyle(sf::Text::StrikeThrough);
	//Returns the set style.
	std::cout << text.getStyle() << std::endl;

	//Gets the set font.
	//We can use this to pass the same font to other texts, or check the font information.
	text.setFont(text.getFont());

	//Gives global position of indexed character.
	//Here, the 'O' in world is the indexed character.
	std::cout << "Position of 'o' in 'world': " << std::endl;
	std::cout << "X: " << text.findCharacterPos(8).x << std::endl;
	std::cout << "Y: " << text.findCharacterPos(8).y << std::endl;

	//To set the size of the characters in the text.
	text.setCharacterSize(12);
	//Gets the size of the texts characters.
	std::cout << "Character size: " << text.getCharacterSize() << std::endl;
	//Sets the factor of space between characters.
	text.setLetterSpacing(2.4f);
	//Gets the factor of space between each character.
	std::cout << "Letter spacing: " << text.getLetterSpacing() << std::endl;
	//Sets the factor of space between lines.
	text.setLineSpacing(0.42f);
	//Gets the factor of space between lines.
	std::cout << "Line spacing: " << text.getLineSpacing() << std::endl;
	
	//To change the string (input text).
	text.setString("We can change the input text!");
	//Returns the text's input string.
	std::cout << std::string(text.getString()) << std::endl;

	while(window.isOpen()) {

		//Update
		PollEvents(window);

		//Render
		window.clear();

		//Drawing
		window.draw(text);

		window.display();
	}
	return 0;
}
