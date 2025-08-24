#include <iostream>
#include <SFML/Graphics/Transformable.hpp>

int main() {

	//Declaring the transformable class.
	sf::Transformable transformable;

	//Sets the center of the transformable, this is the pivot point of rotation, 
	//where all points are scaled from, 
	//and where position is centered upon.
	transformable.setOrigin({ 2.0f, 3.0f });

	//Position is where the transformable is located in n-Dimensional space 
	//(Usually 2-Dimensional space in S.F.M.L.s case).
	transformable.setPosition(sf::Vector2f(144.0f, 256.0f));

	//Scale is how much all points have been stretched away from (or toward if under zero) the origin.
	transformable.setScale({ 1.75f, 0.50f });

	//Rotation is how much our transformable has turned around the origin of the transformable.
	transformable.setRotation(sf::degrees(90));

	//getOrigin will retrieve the coordinates of the origin of the transformable as a Vector2f.
	std::cout << "Origin: ";
	std::cout << "( " << transformable.getOrigin().x << ", ";
	std::cout << transformable.getOrigin().y << " )" << std::endl;

	//getScale will retrieve the size of the scale of the transformable as a Vector2f.
	std::cout << "Scale: ";
	std::cout << "( " << transformable.getScale().x << ", ";
	std::cout << transformable.getScale().y << " )" << std::endl;
	std::cout << std::endl;

	for(unsigned int i = 0; i < 255; ++i) {
		
		//move will translate the transformable by the Vector2f input.
		//This is the same as saying: position = position + vector.
		transformable.move({ 0.001f, 0.002f });
		//Rotate will rotate the tranformable as many degrees or radians as specified by the Angle input.
		//This is the same as saying: rotation = rotation + theta (Where theta is how many radians or degrees are input.
		transformable.rotate(sf::radians(0.01f));
		//Scale will scale the transformable by the same amount as the Vector2f input.
		//This is the same as saying scale = (scale.x * vector.x, scale.y * vector.y). 
		transformable.scale({ 1.001f, 1.001f });
		
		//getPosition returns the position of the transformable (relative to the origin).
		std::cout << "Position: ";
		std::cout << "( " << transformable.getPosition().x << ", ";
		std::cout << transformable.getPosition().y << " )" << std::endl;
		
		//getRotation returns the rotation amount of the transformable in either degrees or radians.
		std::cout << "Rotation: ";
		std::cout << transformable.getRotation().asDegrees() << std::endl;

		//getScale returns the scale of the transformable.
		std::cout << "Scale: ";
		std::cout << "( " << transformable.getScale().x << ", ";
		std::cout << transformable.getScale().y << " )" << std::endl;

		std::cout << std::endl;
	}
	return 0;
}
