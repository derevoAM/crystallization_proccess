//
// Created by п on 24.03.2022.
//

#include "Map.h"
//default constructor
Map::Map(): Height(600), Width(800), number_of_points(1000) {
    point.resize(1000);
}

//constructor
Map::Map(unsigned int H, unsigned int W, unsigned int N): Height(H), Width(W), number_of_points(N) {
    point.resize(N);
}
//copy constructor
Map:: Map(const Map& map):Height(map.Height), Width(map.Width), number_of_points(map.number_of_points) {
    point.resize(map.number_of_points);
    //надо бы еще значения из вектора скопировать, но мне лень
}
//operataor overload
Map& Map::  operator = (const Map& map)
{
    if(this == &map){
        return *this;
    }
    Height = map.Height;
    Width = map.Width;
    number_of_points = map.number_of_points;
    point.resize(map.number_of_points);
    //надо бы еще значения скопировать, но мне лень
    return *this;
}
//присваиваю теплоемкости рандомное значение, никакой математики, просто рандомом балуюсь
void Map::Set_Point_heat_capacity_iterative() {
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);

    std::random_device rd;
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> distrib(1, 100);
    for(unsigned i=0; i<Height;i+=10){
        for(unsigned j=0; j<Width; j+=10){

            Set_point_heat_capacity(i/10*Width/10+j/10, distrib(gen));//вообще это можно сделать в конструкторе point
        }
    }
}
// спорная фигня, прости кружочкам даю координаты, где то можно как то в конструктор сунуть, но хз пусть так
void Map::Set_Point_coordinates_iterative() {
    //
    for(unsigned i=0; i<Height; i+=10) {
        for (unsigned j = 0; j < Width; j += 10) {
            Set_point_coordinates(i / 10 * Width/10 + j / 10, j, i);
        }
    }
}