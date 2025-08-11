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

//sf::View для худа
//
class Engine {
private:
    sf::RenderWindow window;
    sf::Sprite bgSprite;
    sf::Texture bgTexture;

    TextureHolder textureHolder;
    SoundManager soundManager;
    //Когда играем двумя игроками, один управляется через WASD, а другой стрелочками
    //Разделение по кнопке (e) 
    bool isCharacter1 = true;
    bool isSplitScreen = false;

    //https://www.sfml-dev.org/tutorials/3.0/graphics/view/#defining-how-the-view-is-viewed
    //Для отрисовки фона
    sf::View  m_BGMainView;//Координаты и размеры
    sf::View  m_BGLeftView;
    sf::View  m_BGRightView;

    //Фон не отрисовываем
    sf::View  m_MainView;//Координаты и размеры
    sf::View m_LeftView;
    sf::View  m_RightView;

    sf::View HUDview;//Координаты и размеры

    //Нужна ли информация о уровне?
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
