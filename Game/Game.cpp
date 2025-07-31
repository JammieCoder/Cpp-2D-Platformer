#include "Headers.h"

int main()
{
    sf::Texture pixels;
    sf::Texture grassyland;
    sf::Texture stoneplatforms;
    sf::Texture flag;
    sf::Texture level2;
    pixels.loadFromFile("pixelated thingy.jpg", sf::IntRect(0, 0, 50, 50));
    grassyland.loadFromFile("background.jpg", sf::IntRect(128, 144, 1024, 576));
    stoneplatforms.loadFromFile("stoneplatform.png");
    flag.loadFromFile("flag.png");
    level2.loadFromFile("background2.jpg", sf::IntRect(124, 244, 1024, 576));

    sf::RenderWindow window(sf::VideoMode(1024, 576), "My Game");
    sf::Vector2f coords;
    sf::Sprite background = bckgroundinit(grassyland);
    sf::Sprite sprite = spriteinit(pixels);
    sf::Sprite platform1 = platform1init(stoneplatforms, 500, 300);
    sf::Sprite platform2 = platform1init(stoneplatforms, 680, 250);
    sf::Sprite platform3 = platform1init(stoneplatforms, 850, 200);
    sf::Sprite platform4 = platform1init(stoneplatforms, 350, 350);
    sf::Sprite finish = finishinit(flag, 925, 114.6);

    std::vector<sf::Sprite> platforms = {platform1,platform2, platform3, platform4};
    bool Jump = false;
    bool display = true;
    bool check = false;
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        window.clear(sf::Color(255, 255, 255, 255));
        window.draw(background); window.draw(sprite); window.draw(finish);
        for (int j = 0; j < size(platforms); j++) {
            window.draw(platforms[j]);
        }
        Jump = false;
        display = true;
        sf::Event event;
        while (window.pollEvent(event)) {
            display = events(window, sprite, platforms, background, finish, coords, Jump, display, event, check);
        }
        if (display == true) {
            window.display();
        }
        //level2
        {
            if ((istouchingleft(sprite, finish) || istouchingright(sprite, finish)) && (background.getTexture() == &grassyland)) {
                window.clear(sf::Color(255, 255, 255, 255));
                background = bckgroundinit(level2);
                finish = finishinit(flag, 755, 164.6);
                platform1 = platform1init(stoneplatforms, 500, 300);
                platform2 = platform1init(stoneplatforms, 680, 250);
                platform4 = platform1init(stoneplatforms, 350, 350);
                platforms = { platform1,platform2, platform4 };
                sprite.setPosition(25, 430);
                std::cout << "LEVEL 2" << "\n";
            }}
    }
    return 0;
}
