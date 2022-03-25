//
// Created by п on 24.03.2022.
//

#ifndef FIRST_ATTEMPT_POINTS_H
#define FIRST_ATTEMPT_POINTS_H
#include "Map_Draw.h"

class Points {
private:
    double size;
    double heat_capacity;
    double impurity;
    std::pair<unsigned, unsigned > coordinates;
public:
    Points();
    Points(double, double, double, double, double );
};


#endif //FIRST_ATTEMPT_POINTS_H
