//
// Created by п on 24.03.2022.
//
//Класс отвечающий за то что будет происходить с кружочками
//Точнее за то, какие значения они будут принимать, хранить данные о каждом кружочке
#ifndef FIRST_ATTEMPT_Cells_H
#define FIRST_ATTEMPT_Cells_H

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>

const double dt = 0.00001; // 10 в -5 секунд
const double dx = 0.0001; // 100 мкм

class Cells {
protected:
    std::pair<double, double> coordinates;
    bool state; // state = 1 - if crystallized, otherwise state = 0
    double solution;
    double impurity;
    double crys_prob; // in short use crystallization probability
    double dis_prob; // in short use dissolution probability
    double crys_rate; // crystallization rate
    double dis_rate; // dissolution rate
    double max_density = 10;
    double equilibrium_concentration = 10;
    double basic_rate = 10;
public:


    Cells();

    Cells(double, double, bool, double, double);

    void Set_coordinates(double x, double y) {
        coordinates.first = x;
        coordinates.second = y;
    }

    void Set_state(bool state) {
        this->state = state;
    }

    void Set_impurity(double impurity) {
        this->impurity = impurity;
    }

    void Set_solution(double solution) {
        this->solution = solution;
    }

    bool Get_state() const {
        return this->state;
    }

    std::pair<double, double> Get_coordinates() const {
        return this->coordinates;
    }


    double Get_impurity() const {
        return this->impurity;
    }

    double Get_solution() const {
        return this->solution;
    }

    double Get_crys_prob() const {
        return this->crys_prob;
    }

    double Get_dis_prob() const {
        return this->dis_prob;
    }


};


#endif //FIRST_ATTEMPT_Cells_H
