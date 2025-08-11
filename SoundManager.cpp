#include "SoundManager.h"


SoundManager::SoundManager():
	fireSound(fireBuffer),
	waterSound(waterBuffer),
	jumpSound(jumpBuffer)
{
	if (!fireBuffer.loadFromFile("resources/sound/fallinfire.wav")) {
		throw std::exception("Error load wav");
	}
	if (!waterBuffer.loadFromFile("resources/sound/fallinwater.wav")) {
		throw std::exception("Error load wav");
	}
	if (!jumpBuffer.loadFromFile("resources/sound/jump.wav")) {
		throw std::exception("Error load wav");
	}
	//Sound-у задать буфер, создать три функции для проигрывания, вызвать функции
}

SoundManager::~SoundManager()
{
}