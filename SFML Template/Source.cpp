#include <SFML/Graphics.hpp>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "PerlinNoise.hpp"
#include <iostream>

using namespace std;
const int Width = 600;
const int Height = 600;

int main()
{

	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(Width, Height), "PerlinNoise 2D");
	//window.setFramerateLimit(60);

	sf::Uint8* pixels = new sf::Uint8[Width * Height * 4];
	sf::Texture texture;
	texture.create(Width, Height);

	sf::Sprite sprite(texture); // needed to draw the texture on screen

	int RANDOM = rand() % 100000;
	cout << RANDOM << endl;

	siv::PerlinNoise Noise;
	Noise.reseed(RANDOM);

	float inc = 0.01;

	float yoff = 0.0;
	for (int y = 0; y < Height; y++) {
		float xoff = 0.0;
		for (int x = 0; x < Width; x++) {

			int index = (x + y * Width) * 4;
			//cout << index << endl;
			int r = Noise.octaveNoise0_1(xoff, yoff, 8) * 255;
			int g = Noise.octaveNoise0_1(xoff, yoff, 8) * 255;
			int b = Noise.octaveNoise0_1(xoff, yoff, 8) * 255;
			
			pixels[index] = r;
			pixels[index + 1] = g;
			pixels[index + 2] = b;
			pixels[index + 3] = 255;

			xoff += inc;
		}
		yoff += inc;
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		} 
  
		window.clear();
		texture.update(pixels);
		window.draw(sprite);
		window.display();
	}

	return 0;
}