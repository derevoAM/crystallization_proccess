//
// Created by п on 24.03.2022.
//
//Класс отвечающий за то что будет происходить с кружочками
//Точнее за то, какие значения они будут принимать, хранить данные о каждом кружочке
#ifndef FIRST_ATTEMPT_POINTS_H
#define FIRST_ATTEMPT_POINTS_H
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>
class Points {
protected:
    double size;
    double impurity;
    std::pair<double, double > coordinates;
    double heat_capacity;
public:

    Points();
    Points(double, double, double, double, double );
    void Set_coordinates(double x, double y){
        coordinates.first = x;
        coordinates.second = y;
    }
    void Set_size(double size){
        this->size = size;
    }
    void Set_heat_capacity (double heat_capacity){
        this->heat_capacity = heat_capacity;

    }
    void Set_impurity(double impurity){
        this->impurity = impurity;
    }
    std:: pair<double, double> Get_coordinates() const{
        return coordinates;
    }
    double Get_size()const{
        return size;
    }
    double Get_heat_capacity()const{
        return heat_capacity;
    }
    double Get_impurity() const{
        return impurity;
    }
};


#endif //FIRST_ATTEMPT_POINTS_H
