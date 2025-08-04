#include <iostream>

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

int main() {

	sf::Clock clock;//May be thought of as a counter.
	clock.start();//Starts the clock.
	sf::Time time;//Holds onto and works with time from clock or other Time types.
	
	if(clock.isRunning()) {//Checks if clock is running.

		std::cout << "The clock is running!" << std::endl;
	}

	time = time.Zero;//Acts as a zero for sf::Time.
	std::cout << clock.reset().asSeconds() << std::endl;//Pauses the clock, sets the clock counter to zero, and returns elapsed time.
	
	for(unsigned int i = 0; i < 255; ++i) {

		//time = clock.getElapsedTime();
		time = clock.restart();//Works the same as clock.reset() but leaves the clock running.
		std::cout << time.asSeconds() << std::endl;//Returns time value as seconds.
	}
	clock.stop();//Stops the clock.
	return 0;
}
