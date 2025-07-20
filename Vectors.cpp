#include <iostream>
#include <SFML/Graphics/Glsl.hpp>

int main() {

	sf::Vector2f vec0 = { -0.737368f, 0.675490f };//Input values may be declared in curly brackets after an equals sign
	sf::Vector2f vec1 = sf::Vector2f(0.473070f, 0.881025f);//Or input values may be cast in their type in parenthesis
	sf::Vector2f vec2(3.0f, 4.0f);//Or input values may be declared adjacent to the variable name in parenthesis

	std::cout << "angle: " << vec0.angle().asRadians() << std::endl;//Angle from the x-axis
	std::cout << "v_0 angleTo v_1: " << vec0.angleTo(vec1).asRadians() << std::endl;//v_1 angle - v_0 angle
	std::cout << "cross product: " << vec0.cross(vec1) << std::endl;//v_0.x * v_1.y - v_0.y * v_1.x
	std::cout << "v_0 dot v_1: " << vec0.dot(vec1) << std::endl;//v_0.x * v_1.x + v_0.y * v_1.y
	std::cout << "length of v_0: " << vec0.length() << std::endl;//length of vector = sqrt(v_0.x * v_0.x + v_0.y * v_0.y)
	std::cout << "length squared of v_0: " << vec0.lengthSquared() << std::endl;//v_0.length() * v_0.length()

	vec0 = vec0.normalized();//v_0 / v_0.length(), the vector becomes a unit vector (1.0 in length)

	//v0 = (v_0.x * cos(pi / 2) - v_0.y * sin(pi / 2), v_0.x * sin(pi / 2) + v_0.y * cos(pi / 2))
	//Rotates the vector by pi/2 radians (or 90 degrees)
	vec0 = vec0.perpendicular();

	vec0 = vec0.projectedOnto(vec1);//(v_1 Dot v_0 / v_1.length) * v_1

	//v_0 = (v_0.x * cos(theta) - v_0.y * sin(theta), v_0.x * sin(theta) + v_0.y * cos(theta))
	//Rotates the vector by theta radians (or theta * (180 / pi) degrees)
	vec0 = vec0.rotatedBy(sf::Angle(sf::radians(2.718282f)));

	vec0 = vec0.componentWiseDiv(vec1);//(v_0.x / v_1.x, v_0.y / v_1.y)
	vec0 = vec0.componentWiseMul(vec1);//(v_0.x * v_1.x, v_0.y * v_1.y)

	std::cout << "x: " << vec0.x << std::endl;
	std::cout << "y: " << vec0.y << std::endl;

	sf::Vector2i vecI(-7, 2);//sf::Vector2i can work with any signed int value
	sf::Vector2u vecU(3, 5);//sf::Vector2u can work with any unsigned int value

	sf::Vector3f vec3f(1.0f, 2.0f, 3.0f);//sf::Vector3f is a 3-dimensional version of sf::Vector2f
	sf::Vector3i vec3i(-12, 24, -32);//Same as above but with sf::Vector2i

	return 0;
}
