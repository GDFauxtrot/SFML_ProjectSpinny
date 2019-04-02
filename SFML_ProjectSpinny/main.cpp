#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	
	shape.setFillColor(sf::Color::Green);
	
	// Establish update loop timer
	sf::Clock clock;
	sf::Time delta = clock.getElapsedTime();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Game loop here!
		window.clear();
		window.draw(shape);
		window.display();

		// Stop the clock and restart immediately
		delta = clock.restart();

		// DEBUG - print out the time (this is probably a performance sink at the micro level the project is at currently)
		//char buffer[64];
		//sprintf_s(buffer, "%d microsecs elapsed", delta.asMicroseconds());
		//std::cout << buffer << std::endl;
	}

	return 0;
}