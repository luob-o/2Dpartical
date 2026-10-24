
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace sf;
using namespace std;

struct  Patical
{
    sf::CircleShape shape;
    sf::Vector2f velocity;
    /* data */
};

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    const int particalCount = 100;
    Patical paricales[particalCount];
    RenderWindow window(
        VideoMode(800, 600),
        "my first window",
        Style::Resize
    );
    for(int i=0;i<particalCount;i++)
    {
        paricales[i].shape.setRadius(5);
        paricales[i].shape.setFillColor(sf::Color::Green);
        paricales[i].shape.setPosition(rand()% window.getSize().x,rand()% window.getSize().y);
        paricales[i].velocity = sf::Vector2f((rand()%200)-100,(rand()-200)%100);
    }
    sf::Clock clock;
    window.setFramerateLimit(60);
    while(window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            
            if(event.type == Event::Closed)
            {
                window.close();
            }
        }
        float datatime = clock.restart().asSeconds();
        for(int i=0;i<particalCount;++i)
        {
            paricales[i].shape.move(paricales[i].velocity*datatime);
            if(paricales[i].shape.getPosition().x<0||paricales[i].shape.getPosition().x>window.getSize().x)
            {
                paricales[i].velocity.x = -paricales[i].velocity.x;
            }
            if(paricales[i].shape.getPosition().y<0||paricales[i].shape.getPosition().y>window.getSize().y)
            {
                paricales[i].velocity.y = -paricales[i].velocity.y;
            }
        }
        
        window.clear();
        for(int i=0;i<particalCount;i++)
        {
            window.draw(paricales[i].shape);
        }
        window.display();
        
    }
    

    return 0;
}
