#pragma once
#include <SFML/Audio.hpp>

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

private:
	sf::SoundBuffer fireBuffer;
	sf::SoundBuffer waterBuffer;
	sf::SoundBuffer jumpBuffer;

	sf::Sound fireSound;
	sf::Sound waterSound;
	sf::Sound jumpSound;
};
