#include "Headers.h"


void render(sf::RenderWindow &window, sf::Sprite &background, sf::Sprite &sprite, std::vector<sf::Sprite>& platforms, sf::Sprite& finish1)
{
	window.clear(sf::Color(255, 255, 255, 255));
	window.draw(background);
	window.draw(sprite);
    window.draw(finish1);
    for (int j = 0; j < size(platforms); j++) {
        window.draw(platforms[j]);
    }
	window.display();
}

bool events(sf::RenderWindow &window, sf::Sprite &sprite, std::vector<sf::Sprite>& platforms, sf::Sprite &background, sf::Sprite& finish1, sf::Vector2f coords, bool Jump, bool display, sf::Event event, bool check)
{
    switch (event.type) {
    case sf::Event::Closed:
        std::cout << "Closed" << "\n";
        window.close();
        break;
    case sf::Event::LostFocus:
        Pause();
        break;
    case sf::Event::GainedFocus:
        play();
        break;
    case sf::Event::KeyPressed:
        coords = sprite.getPosition();
        switch (event.key.code) {
        case sf::Keyboard::Left:
            if ((coords.x > (0 + 25)) && (istouchingrights(sprite, platforms) == false)) {
                sprite.move(-7.5, 0);
                sprite.rotate(-7.5);
            }
            break;
        case sf::Keyboard::Right:
            if (((coords.x) < (1024 - 25)) && (istouchinglefts(sprite, platforms) == false)) {
                sprite.move(7.5, 0);
                sprite.rotate(7.5);
            }
            break;
        case sf::Keyboard::Space:
            if ((Jump == false)) {
                display = jump(window, sprite, platforms, background, finish1, coords, Jump, display, event, check);
            }
            break;
        default:
            break;
        }
        coords = sprite.getPosition();
        
        if ((istouchingtops(sprite, platforms) == false) && coords.y < 430 && (Jump == false) && (check == false)) {
            check = true;
            while(coords.y < 430 && (istouchingtops(sprite, platforms) == false)){
                sprite.move(0, 4.5);
                render(window, background, sprite, platforms, finish1);
                std::cout << "Down" << "\n";
                coords = sprite.getPosition();
                while (window.pollEvent(event)) {
                    events(window, sprite, platforms, background, finish1,coords, Jump, display, event, check);
                }
                render(window, background, sprite, platforms, finish1);
            }
            check = false;
        }

        std::cout << coords.x << "," << coords.y << "\n\n";
        break;
    default:
        break;
    }
    return display;
}

void Pause()
{
	std::cout << "Paused" << "\n";
}

void play()
{
	std::cout << "Play"<<"\n";
}

bool jump(sf::RenderWindow &window, sf::Sprite &sprite, std::vector<sf::Sprite>& platforms, sf::Sprite &background, sf::Sprite& finish1, sf::Vector2f coords, bool Jump, bool display, sf::Event event, bool check)
{
	Jump = true;
	std::cout << "Jump" << "\n";
    bool touchingbottom = false;
    for (int i = 0; i < 30; i++) {
        if (istouchingbottoms(sprite, platforms) == false && coords.y >= 25) {
            sprite.move(0, -4);
            render(window, background, sprite, platforms, finish1);
            std::cout << "Up" << "\n";
            coords = sprite.getPosition();
        }
        else {
            touchingbottom = true;
        }
        while (window.pollEvent(event)) {
            events(window, sprite, platforms, background, finish1, coords, Jump, display, event, check);
        }
        render(window, background, sprite, platforms, finish1);
    }
    for (int i = 0; i < 20; i++) {
        Sleep(1.75);
        while (window.pollEvent(event)) {
            events(window, sprite, platforms, background, finish1, coords, Jump, display, event, check);
        }
        render(window, background, sprite, platforms, finish1);
    }
    /*if (touchingbottom == false) {
        for (int i = 0; i < 54; i++) {
            if (istouchingtops(sprite, platforms) == false) {
                sprite.move(0, 4);
                render(window, background, sprite, platforms);
                std::cout << "Down" << "\n";
            }
            while (window.pollEvent(event)) {
                events(window, sprite, platforms, background, coords, Jump, display, event, check);
            }
            render(window, background, sprite, platforms);
        }
    }*/
    while (coords.y < 430 && (istouchingtops(sprite, platforms) == false)) {
        sprite.move(0, 6);
        render(window, background, sprite, platforms, finish1);
        std::cout << "Down" << "\n";
        coords = sprite.getPosition();
        while (window.pollEvent(event)) {
            events(window, sprite, platforms, background, finish1, coords, Jump, display, event, check);
        }
        render(window, background, sprite, platforms, finish1);
    }
	Jump = false;
	return false;
}

sf::Sprite spriteinit(sf::Texture &pixels)
{
    sf::Sprite sprite;
	sprite.setTexture(pixels);
	sprite.setOrigin(25, 25);
	sprite.setPosition(25, 430);
	return sprite;
}

sf::Sprite bckgroundinit(sf::Texture &grassyland)
{
	sf::Sprite background;
	background.setTexture(grassyland);
	return background;
}

sf::Sprite platform1init(sf::Texture &stoneplatforms, float x, float y)
{
    sf::Sprite platform1;
    sf::IntRect texturesection(0, 0, 150, 30);
    platform1.setTexture(stoneplatforms);
    platform1.setTextureRect(texturesection);
    platform1.setPosition(x, y);
    return platform1;
}

sf::Sprite finishinit(sf::Texture& flag, float x, float y)
{
    sf::Sprite checkpoint;
    checkpoint.setTexture(flag);
    checkpoint.setPosition(x, y);
    checkpoint.scale(0.1, 0.1);
    return checkpoint;
}

bool istouchingtop(sf::Sprite& sprite1, sf::Sprite& sprite2) {
    sf::FloatRect size1 = sprite1.getGlobalBounds();
    sf::FloatRect size2 = sprite2.getGlobalBounds();
    sf::FloatRect size1l = sprite1.getLocalBounds();


    sf::Vector2f bottomleft((size1.left), (size1.top + size1l.height));
    sf::Vector2f bottomright((size1.left + size1l.width), (size1.top + size1l.height));

    bool BL = false;
    bool BR = false;
    if ((bottomleft.x > size2.left) && (bottomleft.x < (size2.left + size2.width)) && (bottomleft.y > (size2.top - 12.5)) && (bottomleft.y < (size2.top + 7.5))) {
        BL = true;
    }
    if ((bottomright.x > size2.left) && (bottomright.x < (size2.left + size2.width)) && (bottomright.y > (size2.top - 12.5)) && (bottomright.y < (size2.top + 7.5))) {
        BR = true;
    }
    if (BL || BR) {
        return true;
    }
    else {
        return false;
    }
}

bool istouchingbottom(sf::Sprite& sprite1, sf::Sprite& sprite2)
{
    sf::FloatRect size1 = sprite1.getGlobalBounds();
    sf::FloatRect size2 = sprite2.getGlobalBounds();
    sf::FloatRect size1l = sprite1.getLocalBounds();

    sf::Vector2f topleft(size1.left, (size1.top));
    sf::Vector2f topright((size1.left + size1l.width), (size1.top));

    bool TL = false;
    bool TR = false;
    if ((topleft.x > size2.left) && (topleft.x < (size2.left + size2.width)) && (topleft.y < (size2.top + (size2.height) + 7.5)) && (topleft.y > (size2.top + size2.height - 7.55))) {
        TL = true;
    }
    if ((topright.x > size2.left) && (topright.x < (size2.left + size2.width)) && (topright.y < (size2.top + (size2.height) + 7.5)) && (topright.y > (size2.top + size2.height - 7.5))) {
        TR = true;
    }
    if (TL || TR) {
        return true;
    }
    else {
        return false;
    }
}

bool istouchingleft(sf::Sprite& sprite1, sf::Sprite& sprite2)
{
    sf::FloatRect size1 = sprite1.getGlobalBounds();
    sf::FloatRect size2 = sprite2.getGlobalBounds();
    sf::FloatRect size1l = sprite1.getLocalBounds();
    //std::cout << size2.left << ", " << size2.top << "\n";

    sf::Vector2f bottomright((size1.left + size1l.width), (size1.top + size1l.height));
    sf::Vector2f topright((size1.left + size1l.width), (size1.top));

    bool BR = false;
    bool TR = false;
    if ((bottomright.y > (size2.top - 10)) && (bottomright.y < (size2.top + size2.height + 10)) && (bottomright.x >= (size2.left - 7.5)) && (bottomright.x <= (size2.left + 25))) {
        BR = true;
    }
    if ((topright.y > (size2.top - 10)) && (topright.y < (size2.top + size2.height + 10)) && (topright.x >= (size2.left - 7.5)) && (topright.x <= (size2.left + 25))) {
        TR = true;
    }
    //std::cout << "TR:" << TR << "\n";
    //std::cout << "BR:" << BR << "\n";
    if (TR || BR) {
        return true;
    }
    else {
        return false;
    }
}

bool istouchingright(sf::Sprite& sprite1, sf::Sprite& sprite2)
{
    sf::FloatRect size1 = sprite1.getGlobalBounds();
    sf::FloatRect size2 = sprite2.getGlobalBounds();
    sf::FloatRect size1l = sprite1.getLocalBounds();
    //std::cout << size2.left << ", " << size2.top << "\n";


    sf::Vector2f bottomleft((size1.left), (size1.top + size1l.height));
    sf::Vector2f topleft(size1.left, (size1.top));

    bool BL = false;
    bool TL = false;
    if ((bottomleft.y > (size2.top - 10)) && (bottomleft.y < (size2.top + size2.height + 10)) && (bottomleft.x <= (size2.left + size2.width + 7.5)) && (bottomleft.x >= (size2.left + size2.width - 25))) {
        BL = true;
    }
    if ((topleft.y > (size2.top - 10)) && (topleft.y < (size2.top + size2.height + 10)) && (topleft.x <= (size2.left + size2.width + 7.5)) && (topleft.x >= (size2.left + size2.width - 25))) {
        TL = true;
    }
    //std::cout << "TR:" << BL << "\n";
    //std::cout << "BR:" << TL << "\n";
    if (BL || TL) {
        return true;
    }
    else {
        return false;
    }
}

bool istouchingtops(sf::Sprite& sprite, std::vector<sf::Sprite> &platforms)
{
    sf::FloatRect size1 = sprite.getGlobalBounds();
    bool touchingtops = false;
    for (int i = 0; i < size(platforms); i++) {
        if (istouchingtop(sprite, platforms[i]) == true){
            touchingtops = true;
        }
    }
    std::cout << size1.left << ", " << size1.top << "\n";
    return touchingtops;
}

bool istouchingbottoms(sf::Sprite& sprite, std::vector<sf::Sprite> &platforms){
    sf::FloatRect size1 = sprite.getGlobalBounds();
    bool touchingbottoms = false;
    for (int i = 0; i < size(platforms); i++) {
        if (istouchingbottom(sprite, platforms[i]) == true) {
            touchingbottoms = true;
        }
    }
    std::cout << size1.left << ", " << size1.top << "\n";
    return touchingbottoms;
}

bool istouchinglefts(sf::Sprite& sprite, std::vector<sf::Sprite>& platforms)
{
    sf::FloatRect size1 = sprite.getGlobalBounds();
    sf::FloatRect size1l = sprite.getLocalBounds();

    sf::Vector2f bottomright((size1.left + size1l.width), (size1.top + size1l.height));
    sf::Vector2f topright((size1.left + size1l.width), (size1.top));

    bool touchinglefts = false;
    for (int i = 0; i < size(platforms); i++) {
        if (istouchingleft(sprite, platforms[i]) == true) {
            touchinglefts = true;
        }
    }
    std::cout << size1.left << ", " << size1.top << "\n";
    //std::cout << "BR:" << bottomright.x << ", " << bottomright.y << "\n";
    //std::cout << "TR:" << topright.x << ", " << topright.y << "\n";
    return touchinglefts;
}

bool istouchingrights(sf::Sprite& sprite, std::vector<sf::Sprite>& platforms)
{
    sf::FloatRect size1 = sprite.getGlobalBounds();
    bool touchingrights = false;
    for (int i = 0; i < size(platforms); i++) {
        if (istouchingright(sprite, platforms[i]) == true) {
            touchingrights = true;
        }
    }
    std::cout << size1.left << ", " << size1.top << "\n";
    return touchingrights;
}
    