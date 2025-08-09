#pragma once
#include <SFML/Graphics.hpp>
//����������� �����, ������ ����� ���� � �������
//�� ������������ ������ ������ ������� ������

//�� ����� ������������ ������ ����� ������� �������� ������, ����������� ��� ���� � ������.
//� ���� ������ ����� ������� ����� ����� ������ ��������� ��������,
//��������: �����
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

	//������ ����� ����� ���� bool
	virtual bool handleInput() = 0;//���� ����� ���������� ������� �����: "= 0", 
	// �� ������� �� ����� ����
	//���� � ������ ���� ���� ���� ����������� �������, 
	// �� ������ ����� ������ ������� ����������
	
	//Get-����
	//Spawn(pos, gravity), Update(), Draw
	//���� ���-�� �������� ���������, ����������� �������� (�����, ����, �����, ������)
	// ������� ������� ������� �� ������� �����, � �������
	//�������� ������ ����� ��������� � ��������� ������

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
	//�������� ������� �� ������ ������������ ��������������: head, foots, left,right
	sf::RectangleShape head;
	sf::RectangleShape foots;
	sf::RectangleShape left;
	sf::RectangleShape right;

	sf::Sprite sprite;
	sf::Texture texture;
	sf::Color color;

	sf::Vector2f position;

	int speedHorizontal;//�������������� ��������
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
