//
// Created by п on 24.03.2022.
//

#include "Map.h"

//default constructor
Map::Map() : Height(600), Width(800), number_of_Cells(1000) {
    cell.resize(1000);
}

//constructor
Map::Map(unsigned int H, unsigned int W, unsigned int N) : Height(H), Width(W), number_of_Cells(N) {
    cell.resize(N);
}

//copy constructor
Map::Map(const Map &map) : Height(map.Height), Width(map.Width), number_of_Cells(map.number_of_Cells) {
    cell.resize(map.number_of_Cells);
    for(int i = 0; i < map.number_of_Cells; i ++) cell[i] = map.cell[i];
    //надо бы еще значения из вектора скопировать, но мне лень - готово
}

//operataor overload - присваивание одному мапу, другой
Map &Map::operator=(const Map &map) {
    if (this == &map) {
        return *this;
    }
    Height = map.Height;
    Width = map.Width;
    number_of_Cells = map.number_of_Cells;
    cell.resize(map.number_of_Cells);
    for(int i = 0; i < map.number_of_Cells; i ++) cell[i] = map.cell[i];
    //надо бы еще значения скопировать, но мне лень - готово
    return *this;
}


//присваиваю теплоемкости рандомное значение, никакой математики, просто рандомом балуюсь
//void Map::Set_cell_concentration_capacity_iterative() {
    //unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
//    std::default_random_engine e(seed);
//
//    std::random_device rd;
//    std::mt19937 gen(seed);
//    std::uniform_int_distribution<int> distrib(1, 100);
//    for (unsigned i = 0; i < Height; i += 10) {
//        for (unsigned j = 0; j < Width; j += 10) {
//
//            Set_cell_concentration_capacity(i / 10 * Width / 10 + j / 10,
//                                   distrib(gen));//вообще это можно сделать в конструкторе cell
//        }
//    }



//}

// спорная фигня, прости кружочкам даю координаты, где то можно как то в конструктор сунуть, но хз пусть так
void Map::Set_cell_coordinates_iterative() {
    //
    for (unsigned i = 0; i < Height; i += 10) {
        for (unsigned j = 0; j < Width; j += 10) {
            if(i / 10 * Width / 10 + j / 10 < number_of_Cells)
            {
                Set_cell_coordinates(i / 10 * Width / 10 + j / 10, j, i);
            }
        }
    }
}