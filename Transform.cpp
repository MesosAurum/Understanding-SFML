#include <iostream>
#include <SFML/Graphics/Transform.hpp>

int main() {

	//This theta variable represents the angle in radians.
	sf::Angle theta;

	//Initializing vector variable to translate the matrix later.
	sf::Vector2f vectorT = { 1.618f, 2.718f };
	//Initializing vector variable to scale the matrix later.
	sf::Vector2f scaleT = { 2.0f, 2.0f };

	//Making a for loop to go through degrees of rotation.
	for(unsigned int i = 0; i < 255; ++i) {

		//3 * 3 transformation matrix.
		//Scale.x Shear.x Translation.x
		//Shear.y Scale.y Translation.y
		//proj.x  proj.y  proj.z
		//We will ignore this last row and set proj.x and proj.y to 0 while proj.z is set to 1.
		//This transform is an identity matrix.
		sf::Transform transform = { 1.0f, 0.0f, 0.0f,
									0.0f, 1.0f, 0.0f,
									0.0f, 0.0f, 1.0f };

		//An transform may be set as an identity matrix with the .Identity keyword.
		//A * I = A
		transform = transform.Identity;

		//Array for the positions of a square.
		sf::Vector2f pos[4] = {
							{ 0.0f, 0.0f},
							{ 0.0f, 1.0f },
							{ 1.0f, 0.0f },
							{ 1.0f, 1.0f } };

		//Initializing a rectangle to transform.
		sf::FloatRect rectangle = { {0.0f, 0.0f}, {1.0f, 1.0f} };

		//Setting theta to i * ~0.017453 radians.
		theta = i * sf::degrees(1);

		//This is a rotation matrix.
		//All points will be rotated around the origin.
		sf::Transform rotationT = { cos(theta.asRadians()), -sin(theta.asRadians()), 0.0f,
									sin(theta.asRadians()),  cos(theta.asRadians()), 0.0f,
									0.0f,					 0.0f,		             1.0f };

		//Combine is the same as multiplying matrices.
		//This will not work the same as regular multiplication.
		//Here a10 is the element in the second row and first column.
		//a12 would be the element in the second row and third column.
		//For a(m*n) m is the row - 1 and n is the column - 1.
		//2-D:
		//|a00 a01|	  |b00 b01|   |(b00*b00 + a01*b10) (b00*b01 + a01*b11)|
		//|a10 a11| * |b10 b11| = |(a10*b00 + a11*b10) (a10*b01 + a11*b11)|
		//3-D:
		//|a00 a01 a02|   |b00 b01 b02|   |(a00*b00 + a01*b10 + a02*b20) (a00*b01 + a01*b11 + a02*b21) (a00*b02 + a01*b12 + a02*b22)|
		//|a10 a11 a12| * |b10 b11 b12| = |(a10*b00 + a11*b10 + a12*b20) (a10*b01 + a11*b11 + a12*b21) (a10*b02 + a11*b12 + a12*b22)|
		//|a20 a21 a22|   |b20 b21 b22|   |(a20*b00 + a21*b10 + a22*b20) (a20*b01 + a21*b11 + a22*b21) (a20*b02 + a21*b12 + a22*b22)|
		transform = transform.combine(rotationT);

		//Transforming the rectangle based on the transform.
		rectangle = transform.transformRect(rectangle);
		//Displaying rectangle position.
		std::cout << "Rectangle Pos: ";
		std::cout << "( " << rectangle.position.x << ", ";
		std::cout << rectangle.position.y << " )" << std::endl;
		//Displaying rectangle size.
		std::cout << "Rectangle Size: ";
		std::cout << "( " << rectangle.size.x << ", ";
		std::cout << rectangle.size.y << " )" << std::endl;

		//Rotates the transformation matrix.
		//|a00 a01 a02|   |(cos(theta)) (-sin(theta) 0|   |(a00*cos(theta) + a01*sin(theta)) (a00*-sin(theta) + a01*cos(theta)) a02|
		//|a10 a11 a12| * |(sin(theta)) (cos(theta)) 0| = |(a10*cos(theta) + a11*sin(theta)) (a10*-sin(theta) + a11*cos(theta)) a12|
		//|a20 a21 a22|   |     0            0       1|   |(a20*cos(theta) + a21*sin(theta)) (a20*-sin(theta) + a21*cos(theta)) a22|
		//Since a20 and a21 are 0 and a22 is 1:
		//  |(a00*cos(theta) + a01*sin(theta)) (a00*-sin(theta) + a01*cos(theta)) a02|
		//= |(a10*cos(theta) + a11*sin(theta)) (a10*-sin(theta) + a11*cos(theta)) a12|
		//  |                0                                  0                  1 |
		transform = transform.rotate(theta);

		//Transforms the transformation matrix (moving the coordinates along the (x,y)-axes.
		//Vector input v.x will become t_x and v.y will become t_y.
		//|a00 a01 a02|   |1 0 t_x|   |a00 a01 (a00*t_x + a01*t_y + a02)|
		//|a10 a11 a12| * |0 1 t_y| = |a10 a11 (a10*t_x + a11*t_y + a12)|
		//|a20 a21 a22|   |0 0  1 |   |a20 a21 (a20*t_x + a21*t_y + a22)|
		//Since a20 and a21 are 0 and a22 is 1:
		//  |a00 a01 (a00*t_x + a01*t_y + a02)|
		//= |a10 a11 (a10*t_x + a11*t_y + a12)|
		//  |0    0              1            |
		transform = transform.translate(vectorT);

		//Scales the transformation matrix (stretches or squeezes all distances in a specific direction).
		//Vector input v.x will become Scale.x and v.y will become Scale.y.
		//|a00 a01 a02|   |Scale.x    0    0|   |(a00*Scale.x) (a01*Scale.y) a02|
		//|a10 a11 a12| * |0       Scale.y 0| = |(a10*Scale.x) (a11*Scale.y) a12|
		//|a20 a21 a22|   |0          0    1|   |(a20*Scale.x) (a21*Scale.y) a22|
		//Since a20 and a21 are 0 and a22 is 1:
		//|(a00 * Scale.x) (a01 * Scale.y) a02|
		//|(a10 * Scale.x) (a11 * Scale.y) a12|
		//|       0               0         1 |
		transform = transform.scale(scaleT);

		//Showing how the transformations change 4 different points on a 2-D plane.
		std::cout << "Positions: " << std::endl;
		for(unsigned int j = 0; j < 4; ++j) {

			//Transforms point dependant of the transformation matrix.
			//|a00 a01|	  |x|   |a00*x + a01*y|
			//|a10 a11| * |y| = |a10*x + a11*y|
			pos[j] = rotationT.transformPoint(pos[j]);
			
			//Displaying positions.
			std::cout << "pos " << j << ": ";
			std::cout << "( " << pos[j].x << ", ";
			std::cout << pos[j].y << " )" << std::endl;
		}

		//.getInverse returns the inverse of the matrix.
		//An inverse matrix(M^-1) is only an inverse if when we perform matrix multiplication with the original matrix(M)
		//Then the result will be an identity matrix(I).
		//A * A^-1 = I
		transform = transform.getInverse();

		std::cout << std::endl;
	}
	return 0;
}
