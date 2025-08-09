#pragma once
#include <SFML/Graphics.hpp>
#include <map>

//Ограничить создание объектов, в количестве одного
class TextureHolder
{
public:
    TextureHolder();
    static sf::Texture& GetTexture(std::string const& filename);


    static int getCounter() { return counter; }

private:
    static int counter;
    static TextureHolder* Instance;

    std::map <std::string, sf::Texture> textures;
    //Объявление словаря, подключение библиотек. Ключ -- имя файла, значение -- текстура
};
