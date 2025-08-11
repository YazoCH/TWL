#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>

class Level
{
public:
	Level();
	~Level();

	void readLevelFile(sf::VertexArray& textureZone, std::vector<std::vector<char>> &level);

	sf::Vector2u getTileSize() const { return tileSize; }
	sf::Vector2f getStartPosition() const { return m_StartPosition; }


	//sf::VertexArray getTextureZone() const { return textureZone; }	

private:
	

	//sf::VertexArray textureZone;

	int levelNum = 3;

	sf::Vector2u tileSetSize = { 50, 250 };
	sf::Vector2u tileSize = { 50, 50 };

	sf::Vector2f m_StartPosition;
};
