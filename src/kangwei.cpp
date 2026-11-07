#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <SFML/Graphics.hpp>
const int ROW = 100;
const int DEX = 80;
const int GENG = 200;

int maxt[ROW][DEX][GENG];
void gengnerate();
void draw(int gen);
void next(int gen);
int justfor_next(int i,int j,int gen);
sf::RectangleShape drawpratical(int x,int y);
using namespace std;
using namespace sf;
int main()
{   
    //初始化，创建一个数组的函数；
    //绘制他们的初始状态；
    //更新状态；
    //绘制他们的状态；
    
    gengnerate();
    
    
    RenderWindow window(
        VideoMode(800, 600),
        "my first window",
        Style::Resize
    );
    sf::Event event;
    
    int first_gen = 0;
    window.setFramerateLimit(60);
    while(window.isOpen())
    {
 
        while (window.pollEvent(event))
        {
            // "close requested" event: 关闭窗口
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::RectangleShape cell(sf::Vector2f(5.f, 5.f));
        cell.setFillColor(sf::Color::Green);
        window.clear();
        for(int i=0;i<ROW;i++)
        {
            for(int j=0;j<DEX;j++)
            {   if(maxt[i][j][first_gen]==1)
                    cell.setPosition(i*6,j*6);
                    window.draw(cell);
            }
        }
        window.display();
        next(first_gen);
        first_gen++;
        if(first_gen>=GENG-1)
            break;
    }
    


    return 0;
    
}

void gengnerate(){
    //生成一个最初的三维数组，其中最后一位指代第几代；
    //在原先的基础上我们还需要加入一些随机的状态通过对随机数对2取余数；
    for(int i=0;i<ROW;i++)
        for(int j=0;j<DEX;j++)
            maxt[i][j][0] = rand()%2;
}
void next(int gen)
{
    //此函数主要用于更新其状态，借用康威生命游戏的含义，我们这里需要变量count来记录临近元素的数量；
    //此函数输入值为代数，根据当前代推算下一代
    //这里简单谈一谈我们的另一个想法，已有的是ai提出的一个算法统一的条件来判断所有位置
    //我们可以试着在外面外加一层一直赋值为0内圈进行迭代
    int count=0;
    for(int i=0;i<ROW;i++)
    {
        for(int j=0;j<DEX;j++)
        {
            int c = 0;
            c =  justfor_next(i,j,gen);
            if (maxt[i][j][gen] == 1 && (c == 2 || c == 3))
                maxt[i][j][gen+1] = 1;
            else if (maxt[i][j][gen] == 0 && c == 3)
                maxt[i][j][gen+1] = 1;
            else
                maxt[i][j][gen+1] = 0;
                        
        }
    }

}
int justfor_next(int i,int j,int gen)
{
    //对输入的每一个位置（for循环偏移量）的四周进行判断是否越界；
    int count = 0;
    for(int p=-1;p<=1;p++)
    {
        for(int u=-1;u<=1;u++)
        {
            if(p==0&&u==0)
                continue;
            if(i+p<0||i+p>ROW-1||j+u<0||j+u>DEX-1)
                continue;
            
            if(maxt[i+p][j+u][gen]==1)
                count++;
            
        }
    }
    return count;

}
sf::RectangleShape drawpratical(int x,int y)
{
    sf::RectangleShape a ;
    a.setSize(sf::Vector2f(5,5));
    a.setFillColor(sf::Color::Green);
    a.setPosition(x,y);
    return a;

}