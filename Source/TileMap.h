#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

/*************************************************************************

Instantiate, then set tile set (texture to use), then initialise board

*************************************************************************/

class TileMap : public sf::Drawable, public sf::Transformable
{
	private:
		sf::VertexArray vertices;
		sf::Texture tileSet;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	public:
		void setTileSet(const sf::Texture&);
		void initBoard(int rows, int columns, int cell_size, const std::vector<std::vector<int> >& noiseMap);
};

