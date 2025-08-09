#pragma once
#include <SFML/Graphics.hpp>
//Абстрактный класс, хранит общие поля и функции
//От абстрактного класса нельзя создать объект

//От этого абстрактного класса будет создано дочерних класса, наследующие все поля и методы.
//В этом классе будет описано общее между давумя дочерними классами,
//Например: форма
class Personage
{
public:
	Personage();
	~Personage();
	void spawn(sf::Vector2f startPos, float verticalSpeed);
	void update(const float dt);
	void draw(sf::RenderWindow &window);

	void stopLeft(float pos);
	void stopRight(float pos);
	void stopFalling(float pos);
	void stopJump();

	//Скорее всего будет типа bool
	virtual bool handleInput() = 0;//Если после объявления функции стоит: "= 0", 
	// то функция не имеет тела
	//Если в классе есть хоть одна виртуальная функция, 
	// то объект этого класса создать невозможно
	
	//Get-теры
	//Spawn(pos, gravity), Update(), Draw
	//Надо как-то понимать положение, направление движения (вверх, вниз, влево, вправо)
	// Сколько времени отводим на движние вверх, и падение
	//Дочерние классы будем описывать в отдельных файлах

	sf::RectangleShape getHead() const { return head; }
	sf::RectangleShape getFoots() const { return foots; }
	sf::RectangleShape getLeft() const { return left; }
	sf::RectangleShape getRight() const { return right; }

	sf::FloatRect getPos() const { return sprite.getGlobalBounds(); }

	int getSpeed() const { return speedHorizontal; }//////////
	int getGravity() const { return speedVertical; }///////////

	sf::Color getColor() const { return color; }//////////

	sf::Vector2f getCenter() const { return sprite.getGlobalBounds().getCenter(); }
protected:
	//Персонаж разделён на четыре составляющих прямоугольника: head, foots, left,right
	sf::RectangleShape head;
	sf::RectangleShape foots;
	sf::RectangleShape left;
	sf::RectangleShape right;

	sf::Sprite sprite;
	sf::Texture texture;
	sf::Color color;

	sf::Vector2f position;

	int speedHorizontal;//горизонтальное движение
	int speedVertical;

	//
	bool goesLeft;
	bool goesRight;
	bool justJumped;
	bool falling;
	bool jumping;

	float jumpDuration;
	float thisJumpTime;
};
