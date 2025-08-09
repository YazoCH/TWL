#include <iostream>
#include "TextureHolder.h"
#include <cassert>

int TextureHolder::counter = 0;
TextureHolder* TextureHolder::Instance = nullptr;

TextureHolder::TextureHolder(){
    counter++;
    //Singleton Pattern, функция ограничивает создание более одного объекта TextureHolder
    assert(("There are five lights", Instance == nullptr));
    Instance = this;
}

//getTexture() - будет искать в словаре текстуру по имени файла, 
// если найдёт - вернёт адрес текстуры,
// а если нет - добавит текстуру и вернёт её адрес

sf::Texture& TextureHolder::GetTexture(std::string const& filename) {
    auto& m = Instance->textures;//Когда сохраняем адрес, мы продолжаем работу именно с тем словарём, сохранённым в файле
    auto search = m.find(filename);
    if (search != m.end()){//Если мы не дошли до конца, то есть такая запись
        return m[filename];//Возвращаем адрес элемента массива, а массив продолжает существовать, пока не будет вызван деструктор(пока не конец работы программы)
    }
    else {
        sf::Texture& texture = m[filename];
        //Возвращаем адрес локальной переменной
        if (!texture.loadFromFile(filename)) std::cout << "Error -- can't load texture, texture path: " << filename << '\n';
        return texture;
    }
}