#include <iostream>
#include "Thomas.h"
#include "TextureHolder.h"

Thomas::Thomas()
{
	texture = TextureHolder::GetTexture("resources/images/thomas.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect({ 0,0 }, { 50, 150 }));
	jumpDuration = .45;
}

//��������� ������ :

//������ ���������� ��� ������� W.

//    ������ ������ ������� �� ������� ��������� W
// (��� ������ �������, ��� ���� ������).

//    �� ���� ������������ ������������ ������
// (m_JumpDuration), ���� ���� ����� ���������� 
// ���������� W.

bool Thomas::handleInput() {
	//����� ���������� ��������? -- ����� ��������� ���� � ����� ������ ������
	//bool goesLeft;
	//bool goesRight;
	//bool justJumped;
	//bool falling;
	//bool jumping;
	//����������� ������� ������� � �������� �������� ����������
	justJumped = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		//���� ������ ������� ��� ������, �� ��������� ������� ����������
		if (!jumping && !falling) {
			std::cout << "just jumped\n";
			thisJumpTime = 0;
			jumping = true;
			justJumped = true;
		}
	}
	else{
		jumping = false;
		falling = true;
	}
	//���� � ��������� ����� handleItput, �� �������� �������� ������
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		goesLeft = true;
	}	
	else {
		goesLeft = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		goesRight = true;
	}
	else {
		goesRight = false;
	}

	return justJumped;
}

Thomas::~Thomas()
{
}