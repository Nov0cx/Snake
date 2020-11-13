#include <iostream>
#include <Windows.h>
#include <vector>
#include <algorithm>
#include <ctime>

enum Direction {
    UP, LEFT, RIGHT, DOWN, START
};

int snake_row = 12, snake_column = 30, snake_lenght = 1;
int current_food_x, current_food_y;
bool f = false;
int points = -1;
Direction snake_direction = START;

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

void clearScreen();
void draw();
bool collide();
bool collidedFood();
void makeFood();

int main()
{
    draw();
    int seconds = 0, a = 0, c = 0;
    while (!GetAsyncKeyState(VK_ESCAPE) && !collide()) {
        if (seconds >= 19) {
            if (GetAsyncKeyState('D')) {
                snake_direction = LEFT;
            }
            if (GetAsyncKeyState('A')) {
                snake_direction = RIGHT;
            }
            if (GetAsyncKeyState('S')) {
                snake_direction = DOWN;
            }
            if (GetAsyncKeyState('W')) {
                snake_direction = UP;
            }            
            switch (snake_direction) {
                case UP:
                    c++;
                    if (c == 2) {
                        snake_row--;
                        c = 0;
                    }
                    break;
                case DOWN: 
                    a++;
                    if (a == 2) {
                        snake_row++;
                        a = 0;
                    } 
                    break;
                case RIGHT:
                    snake_column--;
                    break;
                case LEFT:
                    snake_column++;
                    break;
            }
            draw();
            seconds = 0;
            continue;
        }
        seconds++;
        Sleep(1);
    }
    return 0;
}

void clearScreen()
{
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

bool collide() {
    if (snake_column >= 78) {
        return true;
    }

    if (snake_column <= 0) {
        return true;
    }

    if (snake_row >= 25) {
        return true;
    }

    if (snake_row <= 0) {
        return true;
    }
    return false;
}

bool collidedFood() {
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 78; j++) {
            if (i + 1 == snake_row && j == snake_column && i + 1 == current_food_y && j == current_food_y)
                return true;
        }
    }
    return false;
}

void draw() {
    clearScreen();
    if (!collide()) {
        if (!f) {
            f = 1;
            makeFood();
        }
        if (collidedFood()) {
            makeFood();
        }
        for (int i = 0; i < 25; i++) {
            std::cout << " ";
        }
        std::cout << "Snake by Niklas | Coded in C++" << std::endl;
        std::cout << "Points: " << points << std::endl;
        for (int i = 0; i < 80; i++) {
            std::cout << "#";
        }
        std::cout << std::endl;
        for (int i = 0; i < 25; i++) {
            std::cout << "#";
            for (int j = 0; j < 78; j++) {
                int k = 0;
                if (i + 1 == snake_row && j == snake_column) {
                    k = 1;                   
                }
                if (i + 1 == current_food_y && j == current_food_y) {
                    k = 2;                   
                }
                switch (k)
                {
                    case 0: {
                        std::cout << " ";
                        break;
                    }
                    case 1: {
                        std::cout << "o";
                        break;
                    }
                    case 2: {
                        std::cout << "f";
                        break;
                    }
                }
            }
            std::cout << "#" << std::endl;
        }
        for (int i = 0; i < 80; i++) {
            std::cout << "#";
        }
    }
    else
    {
        system("cls");
        std::cout << "You collied with a wall! Points: " << points << std::endl;
    }
}

void makeFood() {
    srand(static_cast<unsigned int>(time(nullptr)));
    current_food_x = rand() % (78 - 1 + 1) + 1;
    current_food_y = rand() % (24 - 1 + 1) + 1;
    points++;
}
