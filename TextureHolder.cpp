#include <iostream>
#include "TextureHolder.h"
#include <cassert>

int TextureHolder::counter = 0;
TextureHolder* TextureHolder::Instance = nullptr;

TextureHolder::TextureHolder(){
    counter++;
    //Singleton Pattern, ������� ������������ �������� ����� ������ ������� TextureHolder
    assert(("There are five lights", Instance == nullptr));
    Instance = this;
}

//getTexture() - ����� ������ � ������� �������� �� ����� �����, 
// ���� ����� - ����� ����� ��������,
// � ���� ��� - ������� �������� � ����� � �����

sf::Texture& TextureHolder::GetTexture(std::string const& filename) {
    auto& m = Instance->textures;//����� ��������� �����, �� ���������� ������ ������ � ��� �������, ���������� � �����
    auto search = m.find(filename);
    if (search != m.end()){//���� �� �� ����� �� �����, �� ���� ����� ������
        return m[filename];//���������� ����� �������� �������, � ������ ���������� ������������, ���� �� ����� ������ ����������(���� �� ����� ������ ���������)
    }
    else {
        sf::Texture& texture = m[filename];
        //���������� ����� ��������� ����������
        if (!texture.loadFromFile(filename)) std::cout << "Error -- can't load texture, texture path: " << filename << '\n';
        return texture;
    }
}