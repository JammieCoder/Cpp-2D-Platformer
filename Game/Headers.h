#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include"SFML/Network.hpp"
#include "SFML/OpenGL.hpp"
#include <iostream>
#include <Windows.h>

void render(sf::RenderWindow& window, sf::Sprite& background, sf::Sprite& sprite, std::vector<sf::Sprite>& platforms, sf::Sprite& finish1);
bool events(sf::RenderWindow& window, sf::Sprite& sprite, std::vector<sf::Sprite>& platforms, sf::Sprite& background, sf::Sprite& finish1, sf::Vector2f coords, bool Jump, bool display, sf::Event event, bool check);
void Pause();
void play();
bool jump(sf::RenderWindow &window, sf::Sprite &sprite, std::vector<sf::Sprite>& platforms, sf::Sprite &background, sf::Sprite& finish1, sf::Vector2f coords, bool Jump, bool display, sf::Event event, bool check);
sf::Sprite spriteinit(sf::Texture &pixels);
sf::Sprite bckgroundinit(sf::Texture &grassyland);
sf::Sprite platform1init(sf::Texture& stoneplatforms, float x, float y);
sf::Sprite finishinit(sf::Texture& flag, float x, float y);
bool istouchingtop(sf::Sprite &sprite1, sf::Sprite &sprite2);
bool istouchingbottom(sf::Sprite &sprite1, sf::Sprite &sprite2);
bool istouchingleft(sf::Sprite &sprite1, sf::Sprite &sprite2);
bool istouchingright(sf::Sprite &sprite1, sf::Sprite &sprite2);
bool istouchingtops(sf::Sprite &sprite, std::vector<sf::Sprite> &platforms);
bool istouchingbottoms(sf::Sprite &sprite, std::vector<sf::Sprite> &platforms);
bool istouchinglefts(sf::Sprite& sprite, std::vector<sf::Sprite>& platforms);
bool istouchingrights(sf::Sprite& sprite, std::vector<sf::Sprite>& platforms);
//bool nextlevel(sf::Sprite& sprite, sf::Sprite& finish);