
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;
using namespace sf;

#define screenWidth 1440
#define screenHeight 900
#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight] =
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

// Player position
double posX = 12.0, posY = 12.0;

// Player direction
double dirX = -1.0, dirY = 0.0;

// Camera plane
double planeX = 0.0, planeY = 0.66;

// Check whether a map cell is empty
bool canMove(double x, double y)
{
    int mapX = static_cast<int>(floor(x));
    int mapY = static_cast<int>(floor(y));

    if (mapX < 0 || mapX >= mapWidth ||
        mapY < 0 || mapY >= mapHeight)
    {
        return false;
    }

    return worldMap[mapX][mapY] == 0;
}

// Draw a vertical line
void verLine(RenderWindow& window, int x, int y1, int y2, const Color& color)
{
    if (y2 < y1)
    {
        std::swap(y1, y2);
    }

    VertexArray line(Lines, 2);

    line[0].position = Vector2f(x, y1);
    line[0].color = color;

    line[1].position = Vector2f(x, y2);
    line[1].color = color;

    window.draw(line);
}

void DDA_algorithm(RenderWindow& window)
{
    for (int x = 0; x < screenWidth; x++)
    {
        // Calculate ray position and direction
        double cameraX = 2 * x / (double)screenWidth - 1;
        double rayDirX = dirX + planeX * cameraX;
        double rayDirY = dirY + planeY * cameraX;

        // Current map cell
        int mapX = int(posX);
        int mapY = int(posY);

        double sideDistX;
        double sideDistY;

        double deltaDistX =
            (rayDirX == 0) ? 1e30 : abs(1 / rayDirX);

        double deltaDistY =
            (rayDirY == 0) ? 1e30 : abs(1 / rayDirY);

        double perpWallDist;

        int stepX;
        int stepY;

        int hit = 0;
        int side = 0;

        // Calculate initial side distances
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - posX) * deltaDistX;
        }

        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - posY) * deltaDistY;
        }

        // Perform DDA
        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }

            // Prevent out-of-bounds access
            if (mapX < 0 || mapX >= mapWidth ||
                mapY < 0 || mapY >= mapHeight)
            {
                hit = 1;
                break;
            }

            if (worldMap[mapX][mapY] > 0)
                hit = 1;
        }

        // Calculate perpendicular wall distance
        if (side == 0)
            perpWallDist = sideDistX - deltaDistX;
        else
            perpWallDist = sideDistY - deltaDistY;

        if (perpWallDist < 0.0001)
            perpWallDist = 0.0001;

        // Calculate wall height
        int lineHeight = int(screenHeight / perpWallDist);

        // Calculate drawing boundaries
        int drawStart = -lineHeight / 2 + screenHeight / 2;
        if (drawStart < 0)
            drawStart = 0;

        int drawEnd = lineHeight / 2 + screenHeight / 2;
        if (drawEnd >= screenHeight)
            drawEnd = screenHeight - 1;

        // Choose wall color
        Color color;

        switch (worldMap[mapX][mapY])
        {
        case 1: color = Color::Red;    break;
        case 2: color = Color::Green;  break;
        case 3: color = Color::Blue;   break;
        case 4: color = Color::White;  break;
        default: color = Color::Yellow; break;
        }

        // Darken Y-side walls
        if (side == 1)
        {
            color.r /= 2;
            color.g /= 2;
            color.b /= 2;
        }

        verLine(window, x, drawStart, drawEnd, color);
    }
}

void Move(RenderWindow& window, double frameTime)
{
    if (!window.hasFocus())
        return;

    double moveSpeed = frameTime * 5.0;
    double rotSpeed = frameTime * 3.0;
    double strafeSpeed = moveSpeed * 0.75;

    // Move forward
    if (Keyboard::isKeyPressed(Keyboard::Up) ||
        Keyboard::isKeyPressed(Keyboard::W))
    {
        if (canMove(posX + dirX * moveSpeed, posY))
            posX += dirX * moveSpeed;

        if (canMove(posX, posY + dirY * moveSpeed))
            posY += dirY * moveSpeed;
    }

    // Move backward
    if (Keyboard::isKeyPressed(Keyboard::Down) ||
        Keyboard::isKeyPressed(Keyboard::S))
    {
        if (canMove(posX - dirX * moveSpeed, posY))
            posX -= dirX * moveSpeed;

        if (canMove(posX, posY - dirY * moveSpeed))
            posY -= dirY * moveSpeed;
    }

    // Strafe right
    if (Keyboard::isKeyPressed(Keyboard::D))
    {
        double nextX = posX + dirY * strafeSpeed;
        double nextY = posY - dirX * strafeSpeed;

        if (canMove(nextX, posY))
            posX = nextX;

        if (canMove(posX, nextY))
            posY = nextY;
    }

    // Strafe left
    if (Keyboard::isKeyPressed(Keyboard::A))
    {
        double nextX = posX - dirY * strafeSpeed;
        double nextY = posY + dirX * strafeSpeed;

        if (canMove(nextX, posY))
            posX = nextX;

        if (canMove(posX, nextY))
            posY = nextY;
    }

    // Rotate right
    if (Keyboard::isKeyPressed(Keyboard::Right))
    {
        double oldDirX = dirX;

        dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
        dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);

        double oldPlaneX = planeX;

        planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
        planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
    }

    // Rotate left
    if (Keyboard::isKeyPressed(Keyboard::Left))
    {
        double oldDirX = dirX;

        dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
        dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);

        double oldPlaneX = planeX;

        planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
        planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
    }
}

int main()
{
    RenderWindow window(
        VideoMode(screenWidth, screenHeight),
        "Raycasting"
    );

    window.setFramerateLimit(60);

    Clock frameClock;

    int debugFrames = 0;

    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if (!window.isOpen())
            break;

        // Calculate frame time
        double frameTime = frameClock.restart().asSeconds();

        // Prevent large movement after a long frame
        frameTime = std::min(frameTime, 0.05);

        // Update player before rendering
        Move(window, frameTime);

        window.clear();

        DDA_algorithm(window);

        window.display();

        // Print position every 30 frames
        if (++debugFrames >= 30)
        {
            debugFrames = 0;

            cout << "posX: " << posX
                 << " posY: " << posY
                 << " dirX: " << dirX
                 << " dirY: " << dirY
                 << " D: " << Keyboard::isKeyPressed(Keyboard::D)
                 << " A: " << Keyboard::isKeyPressed(Keyboard::A)
                 << endl;
        }
    }

    return 0;
}
