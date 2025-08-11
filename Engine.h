#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

#include "TextureHolder.h"
#include "SoundManager.h"
#include "Level.h"

#include "Personage.h"//
#include "Bob.h"
#include "Thomas.h"

//sf::View ��� ����
//
class Engine {
private:
    sf::RenderWindow window;
    sf::Sprite bgSprite;
    sf::Texture bgTexture;

    TextureHolder textureHolder;
    SoundManager soundManager;
    //����� ������ ����� ��������, ���� ����������� ����� WASD, � ������ �����������
    //���������� �� ������ (e) 
    bool isCharacter1 = true;
    bool isSplitScreen = false;

    //https://www.sfml-dev.org/tutorials/3.0/graphics/view/#defining-how-the-view-is-viewed
    //��� ��������� ����
    sf::View  m_BGMainView;//���������� � �������
    sf::View  m_BGLeftView;
    sf::View  m_BGRightView;

    //��� �� ������������
    sf::View  m_MainView;//���������� � �������
    sf::View m_LeftView;
    sf::View  m_RightView;

    sf::View HUDview;//���������� � �������

    //����� �� ���������� � ������?
    float timeLevel = 10;
    bool isNewLevel = true;

    const int VERTICAL_SPEED = 300;

    bool playing;


    void input();
    void update(sf::Time dt);
    void draw();

    bool detectCollsion(Personage &p_personage);


    Level level;
    Bob Bob;
    Thomas Thomas;

    const sf::Vector2u TILE_SIZE;
    sf::VertexArray textureZone;
    std::vector<std::vector<char>> levelMatrix;

    sf::Texture tilesTexture;
public:
    Engine();
    ~Engine();

    void run();
};
