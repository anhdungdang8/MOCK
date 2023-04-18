
#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

const int width = 25;  // Width of Map
const int height = 12; // Height of Map

class Object
{
public:
    int x; // Position of Object in console map
    int y;



    Object(int startX, int startY)
    {
        x = startX;
        y = startY;
    }

    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }

    void moveLeft(char map[height][width])
    {
        if (x > 1 && map[y][x - 1] != 'H'&& map[y][x - 1] != '*')
        { // Check if the Object is not already at the left edge of the map and the target position is not an H obstacle
            x--;
        }
    }

    void moveRight(char map[height][width])
    {
        if (x < width - 2 && map[y][x + 1] != 'H'&& map[y][x + 1] != '*')
        { // Check if the Object is not already at the right edge of the map and the target position is not an H obstacle
            x++;
        }
    }

    void moveUp(char map[height][width])
    {
        if (y > 1 && map[y - 1][x] != 'H' && map[y - 1][x] != '*')
        { // Check if the Object is not already at the top edge of the map and the target position is not an H obstacle
            y--;
        }
    }

    void moveDown(char map[height][width])
    {
        if (y < height - 2 && map[y + 1][x] != 'H'&& map[y + 1][x] != '*')
        { // Check if the Object is not already at the bottom edge of the map and the target position is not an H obstacle
            y++;
        }
    }
};


class Map
{
public:
    Object P;
    //Monster M;

    char map[height][width];

    Map(int startX, int startY) : P(startX, startY)
    {

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
                {
                    map[i][j] = '#';//wall block
                }
                else if ((i % 2 == 0 && j % 4 == 0) && i != 0 && j != 0 && i != height - 1 && j != width - 1)
                {
                    map[i][j] = 'H';//hard block
                }
                else if( rand()%2)
                {
                     map[i][j] = '*';//soft block
                }
                else
                {
                    map[i][j] = ' ';// empty block
                }
            }
        }
    }

    void draw(int o_x, int o_y)
    {
        system("cls"); // Clear console screen


        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {

                if (i == P.getY() && j == P.getX())
                {
                    cout << 'P'; // Object
                }
                else if (i == o_y && j == o_x)
                {
                    cout << 'o'; // Boom
                }


                else
                {
                    cout << map[i][j];
                }
            }
            cout << endl;
        }


    }
};

int main()
{
    Map m(width / 2, height / 2);


    // Hide cursor
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);


    int o_x = -1, o_y = -1;

    while (true)
    {
     // ClearScreen();
        switch (_getch())
        {
        case 'a':
            m.P.moveLeft(m.map);
            break;
        case 'd':
            m.P.moveRight(m.map);
            break;
        case 'w':
            m.P.moveUp(m.map);
            break;
        case 's':
            m.P.moveDown(m.map);
            break;
        case ' ':
            o_x = m.P.getX();
            o_y = m.P.getY();

            break;
        default:
            continue; // Ignore other keys
        }

        m.draw(o_x, o_y);
    }
    return 0;
}
