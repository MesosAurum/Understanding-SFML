#include <iostream>
#include <SFML/Graphics/Rect.hpp>

int main() {

	//First set of inputs is the position of the top left corner of the rectangle.
	//Second set of inputs is the size of the rectangle.
	sf::FloatRect floatRectangle0({ 2.1f, 3.2f }, { 5.3f, 7.5f });
	sf::FloatRect floatRectangle1 = sf::FloatRect({ 1.7f, 2.5f }, { 3.3f, 5.5f });
	sf::FloatRect floatRectangle2 = { { 1.7f, 2.5f }, { 3.3f, 5.5f } };

	//sf::IntRect works the same as sf::FloatRect but uses int types instead of float types
	sf::IntRect intRectangle0({ 2, 3 }, { 5, 7 });

	sf::Vector2f center = floatRectangle0.getCenter();//Returns the center point of the rectangle, (p_0 + p_0 + p_1) / 2

	std::cout << "Center is at: (" << center.x << ", " << center.y << ")" << std::endl;

	if(floatRectangle0.findIntersection(floatRectangle1)) {//Checks if the input rectangle intersects the rectangle

		std::cout << "Intersecting!" << std::endl;
	}

	sf::Vector2f point(3.2360688f, 5.436564f);
	if(floatRectangle0.contains(point)) {//Checks if a given point is inside the rectangle

		std::cout << "Contains point (" << point.x << ", " << point.y << ")" << std::endl;
	}

	return 0;
}
