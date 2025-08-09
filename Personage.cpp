#include "Personage.h"
#include "TextureHolder.h"
Personage::Personage():
	texture(sf::Texture()),
	sprite(texture),
	speedHorizontal(512),
	speedVertical(128)
{
	//≈сли бы у персонажей были бы одинаковые текстуры, то их можено было бы инициализировать пр€мо здесь
}

void Personage::spawn(sf::Vector2f startPos, float verticalSpeed) {
	head.setFillColor(sf::Color::Red);
	foots.setFillColor(sf::Color::Cyan);
	left.setFillColor(sf::Color::Green);
	right.setFillColor(sf::Color::Magenta);

	sprite.setPosition(startPos);

	speedVertical = verticalSpeed;
}

void Personage::update(const float dt) {
	if (goesLeft) position.x -= speedHorizontal * dt;
	else if (goesRight) position.x += speedHorizontal * dt;



	



	if (jumping) {
		thisJumpTime += dt;
		position.y -= speedVertical * dt;
		if (thisJumpTime > jumpDuration) {
			jumping = false;
			falling = true;//≈сли не прыгаем, то нужно ли падать?
		}
	}
	if (falling) position.y += speedVertical * dt;

	sf::FloatRect bounds = sprite.getGlobalBounds();
	head.setPosition(bounds.position);//Ћевый верхний угол спрайта
	sf::Vector2f size(bounds.size.x, 1);
	head.setSize(size);

	left.setPosition(bounds.position);
	size = { 1, bounds.size.y };
	left.setSize(size);

	right.setPosition(sf::Vector2f{ bounds.position.x + bounds.size.x -1, bounds.position.y });
	size = { 1, bounds.size.y };
	right.setSize(size);

	foots.setPosition(sf::Vector2f{ bounds.position.x, bounds.position.y + bounds.size.y -1});
	size = { bounds.size.x, 1 };
	foots.setSize(size);

	sprite.setPosition(position);
}

void Personage::stopLeft(float pos) {
	sf::FloatRect bounds = sprite.getGlobalBounds();
	position.x = pos + bounds.size.x;
	sprite.setPosition(position);
	goesLeft = false;
}

void Personage::stopRight(float pos) {
	sf::FloatRect bounds = sprite.getGlobalBounds();
	position.x = pos - bounds.size.x;
	sprite.setPosition(position);
	goesRight = false;

}

void Personage::stopFalling(float pos) {
	sf::FloatRect bounds = sprite.getGlobalBounds();
	position.y = pos - bounds.size.y;
	sprite.setPosition(position);
	falling = false;
}

void Personage::stopJump() {
	
	jumping = false;
	falling = true;
}

void Personage::draw(sf::RenderWindow& window) {
	window.draw(sprite);
	window.draw(head);
	window.draw(foots);
	window.draw(right);
	window.draw(left);
}


Personage::~Personage()
{
}
