#include "Level.h"
#include "TextureHolder.h"
#include "sstream"
Level::Level()
{
	
}

void Level::readLevelFile(sf::VertexArray &textureZone, std::vector<std::vector<char>>& level) {
	//std::cout << "read level\n";
	std::string levelPath;
	switch (levelNum) {
	case 0:
		levelPath = "resources/level/level1.txt";
		m_StartPosition.x = 100;
		m_StartPosition.y = 100;
		break;
	case 1:
		levelPath = "resources\\level\\level2.txt";
		m_StartPosition.x = 100;
		m_StartPosition.y = 3600;
		break;
	case 2:
		levelPath = "resources\\level\\level3.txt";
		m_StartPosition.x = 1250;
		m_StartPosition.y = 0;
		break;
	case 3:
		levelPath = "resources\\level\\level4.txt";
		m_StartPosition.x = 50;
		m_StartPosition.y = 200;
		break;

	}
	std::ifstream file(levelPath);

	if (!file.is_open()) {
		throw std::exception("can't open file");
	}

	std::string buffer;
	int linesCount=0;
	int columnsCount=0;
	while (std::getline(file, buffer)) {
		linesCount++;
	}
	columnsCount = buffer.length();
	//Встаём на начало файла.
	file.clear();
	file.seekg(0, std::ios::beg);
	//Заполняем Level
	//std::vector<std::vector<char>> level;
	level.resize(linesCount);

	int i = 0;
	while (std::getline(file, buffer)) {
		//level[i].resize(columnsCount);

		for (auto j : buffer) {
			level[i].push_back(j-'0');
		}
		//level.push_back(std::move(secondBuffer));
		i++;
	}

	file.close();

	textureZone.setPrimitiveType(sf::PrimitiveType::Triangles);
	int width = level[0].size();
	int height = level.size();
	std::cout << width << ' ' << height << "\n";

	textureZone.resize(width * height * 6);

	//std::cout<< "LL: " << sizeof(0LL);
	
	// populate the vertex array, with two triangles per tile
	for (unsigned int i = 0; i < width; ++i){
		for (unsigned int j = 0; j < height; ++j){
			// get the current tile number
			const int tileNumber = level[j][i];//Матрица?

			// find its position in the tileset texture
			const int tv = tileNumber / (tileSetSize.x / tileSize.x);
			const int tu = tileNumber % (tileSetSize.x / tileSize.x);

			// get a pointer to the triangles' vertices of the current tile
			sf::Vertex* triangles = &textureZone[(i + j * width) * 6];

			// define the 6 corners of the two triangles
			triangles[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
			triangles[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			triangles[2].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
			triangles[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
			triangles[4].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			triangles[5].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);

			// define the 6 matching texture coordinates
			triangles[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
			triangles[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
			triangles[2].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
			triangles[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
			triangles[4].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
			triangles[5].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
		}
	}
	
	//for (unsigned int i = 0; i < height; ++i) {
	//	for (unsigned int j = 0; j < width; ++j) {
	//		// get a pointer to the triangles' vertices of the current tile
	//		//sf::Vertex* triangles = &textureZone[(i + j * width) * 6];
	//		std::cout << level[i][j] << ' ';
	//		//std::cout << textureZone[i * j * width].position.x <<' '<<textureZone[i * j * width].position.y << '\t';
	//	}
	//	std::cout << '\n';
	//}
}

Level::~Level()
{
}