#include "Engine.h"
#include <iomanip>

Engine::Engine()
    :bgTexture(sf::Vector2u(1, 1)),
    bgSprite(bgTexture),
    playing(false),
    TILE_SIZE(level.getTileSize())
{
    //sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::Vector2f resolution = sf::Vector2f(sf::VideoMode::getDesktopMode().size);
    window.create(
        sf::VideoMode(sf::Vector2u(resolution.x, resolution.y)),
        "Thomas was late",
        sf::State::Windowed
    );
    window.setFramerateLimit(128);

    bgTexture = TextureHolder::GetTexture("resources/images/background.png");
    tilesTexture = TextureHolder::GetTexture("resources/images/tiles_sheet.png");

    bgSprite.setTexture(bgTexture);
    bgSprite.setTextureRect(sf::IntRect({ 0,0 }, { 1920, 1080 }));

    m_MainView = window.getDefaultView();//Получаем все параметры у окна
    m_BGMainView = HUDview = m_MainView;
    m_MainView.setSize(sf::Vector2f{ resolution.x, resolution.y });
    m_MainView.setCenter(sf::Vector2f{ resolution.x / 2, resolution.y / 2 });
    HUDview.setSize(sf::Vector2f{ resolution.x, resolution.y });
    HUDview.setCenter(sf::Vector2f{ resolution.x / 2, resolution.y / 2 });
    //m_BGMainView?

    //Задаём разбивку экрана
    m_BGLeftView.setViewport(sf::FloatRect({ 0.0f, 0.0f }, { 0.5f, 1.0f }));
    m_LeftView.setViewport(sf::FloatRect({ 0.0f, 0.0f }, { 0.5f, 1.0f }));

    m_BGRightView.setViewport(sf::FloatRect({ 0.5f, 0.0f }, { 0.5f, 1.0f }));
    m_RightView.setViewport(sf::FloatRect({ 0.5f, 0.0f }, { 0.5f, 1.0f }));
}

Engine::~Engine() {}

void Engine::run() {

    window.setFramerateLimit(144);

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        input();
        update(dt);

        draw();
        //Не видим персонажа
    }
}

void Engine::input() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        if (event->is<sf::Event::KeyPressed>()) {

            const auto key = event->getIf<sf::Event::KeyPressed>()->code;

            if (key == sf::Keyboard::Key::Enter) {
                playing = true;
            }
            //Обработать нажатие на кнопки (E), isSplitScreen поменять на противоположное.
            //Томас -- WASD, Боб -- стрелки
            if (key == sf::Keyboard::Key::E) {
                isSplitScreen = !isSplitScreen;
            }

            if (key == sf::Keyboard::Key::Q) {
                isCharacter1 = !isCharacter1;//Переключение управления на другого игрока
            }

            if (key == sf::Keyboard::Key::Escape) {
                window.close();
            }


            //Управление 1-м и 2-м игроком

            //!!!!!!!!!!!!!!!!
            // Handle input specific to Thomas
            if (Thomas.handleInput())
            {
                // Play a jump sound
            }
            // Handle input specific to Bob
            if (Bob.handleInput())
            {
                // Play a jump sound
            }
        }

 

    }
}

void Engine::update(sf::Time dt) {
    if (playing)
    {
        //timeLevel -= dt.asSeconds();
        if (0 == timeLevel) {
            isNewLevel = true;
        }
    }
    if (isNewLevel) {
        try
        {
            level.readLevelFile(textureZone, levelMatrix);
            //std::cout << levelMatrix[0].size() << '\n';
            //for (int x = 0; x < levelMatrix.size(); x++) {
            //    for (int y = 0; y < levelMatrix[0].size(); y++) {
            //        std::cout << levelMatrix[x][y] << ' ';
            //    }
            //    std::cout << '\n';
            //}
            Bob.spawn(level.getStartPosition(), VERTICAL_SPEED);
            Thomas.spawn(level.getStartPosition(), VERTICAL_SPEED);
            isNewLevel = false;//Управление загрузкой уровня происходит в detect collision

        }
        catch (const std::exception& err)
        {
            //throw std::exception("error here1");
            std::cout << err.what() << '\n';
        }


    }

    //Координаты игроков меняются, а камера остаётся на одном месте
    //(не фокусируемся на игроках)
    Bob.update(dt.asSeconds());
    Thomas.update(dt.asSeconds());
    //Если оба достигли конца уровня - загрузка нового уровня
    //Иначе - остановить падение, прыжок и т.д.
    if (detectCollsion(Bob) && detectCollsion(Thomas)) {
        isNewLevel = true;
    }
    else {
        //
        detectCollsion(Thomas);
    }

    sf::FloatRect BobFootBox = Bob.getFoots().getGlobalBounds();
    sf::FloatRect BobHeadBox = Bob.getHead().getGlobalBounds();
    sf::FloatRect ThomasFootBox = Thomas.getFoots().getGlobalBounds();
    sf::FloatRect ThomasHeadBox = Thomas.getHead().getGlobalBounds();

    if (BobFootBox.findIntersection(ThomasHeadBox)) {
        Bob.stopFalling(ThomasHeadBox.position.y);
    }
    if (ThomasFootBox.findIntersection(BobHeadBox)) {
        Thomas.stopFalling(BobHeadBox.position.y);
    }



    if (isSplitScreen) {
        m_LeftView.setCenter(Thomas.getCenter());
        m_RightView.setCenter(Bob.getCenter());
    }
    else {
        if (isCharacter1) {
            m_MainView.setCenter(Thomas.getCenter());

        }
        else {
            m_MainView.setCenter(Bob.getCenter());

        }
    }
}

void Engine::draw() {
    window.clear(sf::Color::White);
    if (!isSplitScreen) {
        window.setView(m_BGMainView);
        window.draw(bgSprite);

        window.setView(m_MainView);
        //Что-то тут будем отрисовывать.

        window.draw(textureZone, &tilesTexture);
        
        Bob.draw(window);
        Thomas.draw(window);
    }
    else {
        //////////////
        //ЛЕВОЕ ОКНО//
        //////////////
        window.setView(m_BGLeftView);
        window.draw(bgSprite);
        window.setView(m_LeftView);

        //Персонажи, всё остальное для левой части окна
        window.draw(textureZone, &tilesTexture);
        Thomas.draw(window);
        Bob.draw(window);



        ///////////////
        //ПРАВОЕ ОКНО//
        ///////////////
        window.setView(m_BGRightView);
        window.draw(bgSprite);
        window.setView(m_RightView);

        //Персонажи, всё остальное, для правой части окна
        window.draw(textureZone, &tilesTexture);
        Thomas.draw(window);
        Bob.draw(window);
    }
    window.setView(HUDview);
    //Когда сделаем HUD будем отрисовывать его
    window.display();
}



bool Engine::detectCollsion(Personage &p_personage) {
    bool reachedEnd = false;
    //Если значение клетки == 4, то это выход с уровня.

    //Это - чтобы просто понимать стоит персонаж на платформе или нет.

    sf::FloatRect levelBox(
        { 0.0f, 0.0f }, 
        { (float)levelMatrix[0].size() * TILE_SIZE.x,(float)levelMatrix.size() * TILE_SIZE.y }
    );

    //playerBounds не расширенный, но, возможно, это будет необходимо.
    sf::FloatRect playerBounds = p_personage.getPos();
    int startX = playerBounds.position.x/TILE_SIZE.x - 1;
    int startY = playerBounds.position.y / TILE_SIZE.y - 1;
    int endX = (playerBounds.size.x / TILE_SIZE.x) + startX + 2;
    int endY = (playerBounds.size.y / TILE_SIZE.y) + startY + 3;

    if (startX < 0) {
        startX = 0;
        
    }
    if (startY < 0) {
        startY = 0;
    }
    if (endY > levelMatrix.size()) {
        endY = levelMatrix.size();
    }
    if (endX > levelMatrix[0].size()) {
        endX = levelMatrix[0].size();
    }
    //std::cout << "Start x: " << startX << " End x: " << endX <<
        //"\nStart y: " << startY << " End y: " << endY << "\n\n";

    if (!levelBox.findIntersection(playerBounds)){
        std::cout<<"Falling out of map\n";
        p_personage.spawn(level.getStartPosition(), VERTICAL_SPEED);
    }
    sf::FloatRect block;
    block.size.x = TILE_SIZE.x;
    block.size.y = TILE_SIZE.y;

    
    //Поискать ошибку
    for (int x = startX; x < endX; x++) {
        for (int y = startY; y < endY; y++) {
            block.position.x = x * TILE_SIZE.x;
            block.position.y = y * TILE_SIZE.y;
            std::cout << x * TILE_SIZE.x << ' ' << y * TILE_SIZE.y << '\n' << block.size.x << ' ' << block.size.y << "\n\n";
            std::cout << "Cell 0: " << (int)levelMatrix[y][x] << "\n";

            //Поиск пересечения блока с головой, ногами, справа, слева, если клетка = 1,2,3,4
            if (levelMatrix[y][x] == 1) {
                std::cout << "Cell 1: " << (int)levelMatrix[y][x] << "\n";
                //Обычная клетка

                sf::FloatRect leftBox = p_personage.getLeft().getGlobalBounds();;
                sf::FloatRect rightBox = p_personage.getRight().getGlobalBounds();;

                if (leftBox.findIntersection(block)) {
                    p_personage.stopLeft(block.position.x);
                }

                if (rightBox.findIntersection(block)) {
                    p_personage.stopRight(block.position.x);
                }

                sf::FloatRect feetBox = p_personage.getFoots().getGlobalBounds();
                /*std::cout << "Pos: " << feetBox.position.x << ' ' << feetBox.position.y
                    << "\n Size: " << feetBox.size.x << ' ' << feetBox.size.y << "\n\n";*/
                sf::FloatRect headBox = p_personage.getHead().getGlobalBounds();

                if (feetBox.findIntersection(block)) {
                    p_personage.stopFalling(block.position.y);
                    std::cout << "stop falling\n";
                    getchar();
                }
                if (headBox.findIntersection(block)) {
                    p_personage.stopJump();
                }

            }
            else if (levelMatrix[y][x] == 2 || levelMatrix[y][x] == 3) {
                if (levelMatrix[y][x] == 2) {
                    std::cout << (int)levelMatrix[y][x] << " 2\n";
                    //Сгорел
                }
                else {
                    std::cout << (int)levelMatrix[y][x] << " 3\n";
                    //Утонул
                }
                p_personage.spawn(level.getStartPosition(), VERTICAL_SPEED);
            }
            else if (levelMatrix[y][x] == 4) {
                std::cout << (int)levelMatrix[y][x] << "\n";
                reachedEnd = true;
            }

        }
    }

    return reachedEnd;
}
