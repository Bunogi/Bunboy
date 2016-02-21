#include <iostream>

#include <SFML/Graphics.hpp>

#include "gb.hpp"

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cout << "Error: Specify a file\n";
		return 1;
	}

	sf::RenderWindow window(sf::VideoMode(160, 144), "bunboy");
	window.setFramerateLimit(60);
	GB::reset();
	GB::RAM::loadROM(std::string(argv[1]));
	sf::Event event;

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		GB::update();
	}

}
