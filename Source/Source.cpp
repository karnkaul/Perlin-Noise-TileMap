#include <iostream>

#include "TileMap.h"
#include "NoiseGenerator2D.h"

const unsigned int rows = 20, columns = 32;

const std::string tileSetPath = "./Assets/tileSet.png";
const unsigned int tileSize = 32, numTiles = 6;						// based on texture in tileSetPath
const double xMin = 0.0f, xMax = 2.2f, zMin = 0.0f, zMax = 3.0f;	// based on rows * columns

// Splits [-1, 1] into 'divisions' buckets and returns corresponding bucket 'frac' belongs to (array index format).
unsigned int getBucket(const double&, const unsigned int&);

int main()
{
	std::vector<std::vector<int> > bucketValues;

	srand(time(0));

	NoiseGenerator generator;
	NoiseMap noiseMap = generator.setBounds(xMin, xMax, zMin, zMax).buildMap(rows, columns, rand());

	std::cout.precision(1);
	for (int x = 0; x < rows; ++x)
	{
		bucketValues.push_back(std::vector<int>());
		for (int y = 0; y < columns; ++y)
		{
			double noiseValue = noiseMap.GetValue(x, y);
			int bucket = getBucket(noiseValue, numTiles);
			bucketValues[x].push_back(bucket);
		}
	}

	// Set TileMap's tileSet texture
	TileMap tileMap;
	sf::Texture tileSet;
	if (!tileSet.loadFromFile(tileSetPath))
	{
		std::cout << "Could not load texture. Quitting." << std::endl;
		return 1;
	}
	tileMap.setTileSet(tileSet);
	
	// Initialise board
	tileMap.initBoard(rows, columns, tileSize, bucketValues);

	// Draw window
	sf::ContextSettings _settings;
	_settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[2], "Tile Map", sf::Style::Default, _settings);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			default:
				break;
			}
		}

		window.clear();
		
		// Set a border
		sf::RenderStates states;
		states.transform = sf::Transform().translate(sf::Vector2f(20, 20));

		// Draw tile map
		window.draw(tileMap, states);
		
		window.display();
	}

	return 0;
}

unsigned int getBucket(const double& frac, const unsigned int& divisions)
{
	// Noise value is [-1, +1]
	double bucketSize = 2.0f / (double)divisions;

	double currentBucket = -1.0f;
	unsigned int ret = 0;
	do {
		currentBucket += bucketSize;
		if (frac <= currentBucket)
			return ret;
		ret++;
	} while (ret < divisions);

	return ret - 1;
}
