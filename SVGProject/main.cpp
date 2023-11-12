#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

#include "Shape.h"

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(1000, 500), "HAU", Style::Default);


	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
		}

		// Update

		// Draw
		window.clear();

		// Draw stuff

		// Finished drawing
		window.display();
	}

	return 0;
}
