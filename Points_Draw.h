//
// Created by п on 25.03.2022.
//

#ifndef FIRST_ATTEMPT_POINTS_DRAW_H
#define FIRST_ATTEMPT_POINTS_DRAW_H
#include <SFML/Graphics.hpp>
#include "Map.h"
class Points_Draw  {
protected:
    sf::Color color_free = sf:: Color(255, 0, 0, 200);
    sf:: Color color_crystal =sf:: Color(0, 255, 0, 255);
    sf:: CircleShape circle;
public:
    Points_Draw() = default;
    Points_Draw(Points& point);
    sf:: CircleShape Get_circle(){
        return circle;
    };

};


#endif //FIRST_ATTEMPT_POINTS_DRAW_H
