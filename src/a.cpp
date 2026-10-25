
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace sf;
using namespace std;

struct  Patical
{
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    bool alive;
    float age;
    float lifetime;
    /* data */
};
sf::Vector2f startPos(400.f, 500.f);
float basevelocity = 100.0;
float baseangle = -90.0;
const float pi = 3.14159265358979f;
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
        paricales[i].shape.setSize(sf::Vector2f(5,6));
        paricales[i].shape.setFillColor(sf::Color::Green);
        //paricales[i].shape.setPosition(rand()% window.getSize().x,rand()% window.getSize().y);
        paricales[i].shape.setPosition(startPos);
        paricales[i].alive = false;
        float offserdeg = static_cast<float>((rand()%96)-45);
        float angle = baseangle+offserdeg;
        float anglered = angle*pi/180.0;
        float vx = cos(anglered)*basevelocity;
        float vy = sin(anglered)*basevelocity;
        paricales[i].velocity = sf::Vector2f(vx,vy);
        float liferand = static_cast<float>(rand()%5+1.f);
        paricales[i].lifetime = liferand;
        paricales[i].age = 0;

    }
    sf::Clock clock;
    window.setFramerateLimit(60);
    float emittime = 0.f;
    float testtime = 0.015f;
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
        
        emittime +=datatime;
        
        while(emittime>=testtime)
        {
            emittime -=testtime;
            for (int i = 0; i < 100; ++i)
            {
                if (paricales[i].alive)
                    continue; 
                paricales[i].alive = true;
                paricales[i].age = 0.f;
                break;

                                            
            }
            

        }
        for(int i=0;i<particalCount;++i)
        {   
            if (paricales[i].age >= paricales[i].lifetime)   // 寿终 → 回收
            {
                paricales[i].alive = false;
                paricales[i].shape.setPosition(startPos);
                continue;
            }

            if(paricales[i].alive)
            {
                paricales[i].shape.move(paricales[i].velocity*datatime);
                paricales[i].age+=datatime;
            }
                
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
            if(paricales[i].alive||paricales[i].age<paricales[i].lifetime)
                window.draw(paricales[i].shape);
        }
        
        window.display();
        
    }
    
//ne
    return 0;
}
