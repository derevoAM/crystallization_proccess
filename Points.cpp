//
// Created by п on 24.03.2022.
//

#include "Points.h"
Points:: Points (): size(3),heat_capacity(0), impurity(0), coordinates(0, 0)  {}
Points::Points(double size, double heat_capacity, double impurity, double x, double y): size(size),heat_capacity(heat_capacity), impurity(impurity), coordinates(x, y) {}
