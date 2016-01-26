#pragma once
#include "TileMap.h"
#include <iostream>

void TileMap::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	states.texture = &tileSet;

	target.draw(vertices, states);
}

void TileMap::setTileSet(const sf::Texture &tileSet)
{
	this->tileSet = tileSet;
}

void TileMap::initBoard(int rows, int columns, int tileSize, const std::vector<std::vector<int> > &noiseMap)
{
	vertices.setPrimitiveType(sf::Quads);
	vertices.resize(rows * columns * 4);

	// Column-wise traversal for vertex array
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			int tileNumber = noiseMap[i][j];

			// tu and tv get row and column number of tileNumber in tileSet
			int tu = tileNumber % (tileSet.getSize().x / tileSize);		// safe overflow 
			int tv = tileNumber / (tileSet.getSize().x / tileSize);

			// Get pointer to current quad's first vertex
			sf::Vertex* quad = &vertices[(i * columns + j) * 4];

			// Define vertex positions. We need to progress along (SFML's) x-axis first, then y-axis after each run of "columns" x-axis values. 
			// Hence j is used for x, and i for y.
			quad[0].position = sf::Vector2f(j * tileSize, i * tileSize);
			quad[1].position = sf::Vector2f((j + 1) * tileSize, i * tileSize);
			quad[2].position = sf::Vector2f((j + 1) * tileSize, (i + 1) * tileSize);
			quad[3].position = sf::Vector2f(j * tileSize, (i + 1) * tileSize);

			// Define texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * tileSize, tv * tileSize);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize, tv * tileSize);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize, (tv + 1) * tileSize);
			quad[3].texCoords = sf::Vector2f(tu* tileSize, (tv + 1) * tileSize);
		}
	}
}

