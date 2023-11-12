#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

#include "Shape.h"

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(1000, 600), "HAU", Style::Default);

	Drawer shape;
	shape.read("sample.svg");



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
		shape.Draw(window);

		// Finished drawing
		window.display();
	}

	return 0;
}