
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
sf::RectangleShape drawpratical(int x,int y);
using namespace sf;
using namespace std;
int main()
{
    RenderWindow window(
        VideoMode(800, 600),
        "my first window",
        Style::Resize
    );
    sf::Event event;
    while (window.pollEvent(event))
    {
        // "close requested" event: 关闭窗口
        if (event.type == sf::Event::Closed)
            window.close();
    }

    window.setFramerateLimit(60);
    while(window.isOpen())
    {
        for(int i=0;i<=100;)
        {
            window.draw(drawpratical(i,i+100));
            i+=20;
        }
        
        
        window.display();
        
    }
    return 0;
}

sf::RectangleShape drawpratical(int x,int y)
{
    sf::RectangleShape a ;
    a.setSize(sf::Vector2f(20,20));
    a.setFillColor(sf::Color::Green);
    a.setPosition(x,y);
    return a;

}