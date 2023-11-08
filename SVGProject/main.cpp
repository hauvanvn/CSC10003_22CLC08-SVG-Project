#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(1000, 500), "HAU", Style::Default);

	RectangleShape rect;
	rect.setFillColor(Color::Green);
	rect.setSize(Vector2f(100, 100));

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
		window.draw(rect);

		// Finished drawing
		window.display();
	}

	return 0;
}