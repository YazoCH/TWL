#include "Bob.h"
#include "TextureHolder.h"

Bob::Bob()
{
	texture = TextureHolder::GetTexture("resources/images/bob.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect({ 0,0 }, { 50, 100 }));
	jumpDuration = .25;
}

//гибридный подход :

//Прыжок начинается при нажатии W.

//    Высота прыжка зависит от времени удержания W
// (чем дольше держишь, тем выше прыжок).

//    Но есть максимальная длительность прыжка
// (m_JumpDuration), даже если игрок продолжает 
// удерживать W.

bool Bob::handleInput() {
	//Зачем возвращать значение? -- Чтобы проиграть звук в самом начале прыжка
	//bool goesLeft;
	//bool goesRight;
	//bool justJumped;
	//bool falling;
	//bool jumping;
	//Перехватить нажатие стрелок и изменить значение переменных
	justJumped = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
		//Если сейчас прыгаем или падаем, то обнуление времени невозможно
		if (!jumping && !falling) {
			thisJumpTime = 0;
			jumping = true;
			justJumped = true;
		}
	}
	else{
		jumping = false;
		falling = true;
	}
	//Если в следующий вызов handleItput, то персонаж начинает падать
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		goesLeft = true;
	}	
	else {
		goesLeft = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		goesRight = true;
	}
	else {
		goesRight = false;
	}

	return justJumped;
}

Bob::~Bob()
{
}