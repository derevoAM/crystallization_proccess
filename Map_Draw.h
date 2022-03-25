#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#ifndef FIRST_ATTEMPT_MAP_DRAW_H
#define FIRST_ATTEMPT_MAP_DRAW_H

template<typename T>
class Map_Draw {
private:
    sf::RenderWindow window;
public:
    Map_Draw(T Width,T Height);
void Creat_Window(T, T);
void Creat_Shapes(T);
void Set_Position(T, T);
void Display();
};


#endif //FIRST_ATTEMPT_MAP_DRAW_H
