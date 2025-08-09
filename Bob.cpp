#include "Bob.h"
#include "TextureHolder.h"

Bob::Bob()
{
	texture = TextureHolder::GetTexture("resources/images/bob.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect({ 0,0 }, { 50, 100 }));
	jumpDuration = .25;
}

//��������� ������ :

//������ ���������� ��� ������� W.

//    ������ ������ ������� �� ������� ��������� W
// (��� ������ �������, ��� ���� ������).

//    �� ���� ������������ ������������ ������
// (m_JumpDuration), ���� ���� ����� ���������� 
// ���������� W.

bool Bob::handleInput() {
	//����� ���������� ��������? -- ����� ��������� ���� � ����� ������ ������
	//bool goesLeft;
	//bool goesRight;
	//bool justJumped;
	//bool falling;
	//bool jumping;
	//����������� ������� ������� � �������� �������� ����������
	justJumped = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
		//���� ������ ������� ��� ������, �� ��������� ������� ����������
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
	//���� � ��������� ����� handleItput, �� �������� �������� ������
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