//
// Created by п on 24.03.2022.
//

#include "Map.h"
#include <iomanip>
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
    for (int i = 0; i < map.number_of_Cells; i++) cell[i] = map.cell[i];
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
    for (int i = 0; i < map.number_of_Cells; i++) cell[i] = map.cell[i];
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
void Map::Set_cell_origin() {
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);
    tot_solution = 0.0;
    std::random_device rd;
    std::mt19937 gen(seed);
    std::uniform_real_distribution<double> distrib(0, 1);
    for (unsigned i = 0; i < Height; i += 2) {
        for (unsigned j = 0; j < Width; j += 2) {
            if (i / 2 * Width / 2 + j / 2 < number_of_Cells) {
                double prob = distrib(gen);
                Set_cell_coordinates(i / 2 * Width / 2 + j / 2, j, i);
                cell[i / 2 * Width / 2 + j / 2].Set_solution(max_density * prob);
                tot_solution += max_density * prob;
                cell[i / 2 * Width / 2 + j / 2].Set_impurity(max_density - cell[i].Get_solution());
                state = false;
                std::cout << cell[i / 2 * Width / 2 + j / 2].Get_solution() << " ";
            }
        }
    }
    std::cout << "\n" << tot_solution << "\n";
}

/*
void Map::Differential_equation_iteration1() {
    double total_solution = 0.0;
    //double total_impurity = 0.0;
    double x = 0, y = 0;
    for (int i = 0; i < number_of_Cells; i++) {
        total_solution = Get_cell_solution(i) * (1 - 4 * diffusion_coef * dt / (dx * dx));
        //total_impurity = Get_cell_impurity(i) * (1 - 4 * diffusion_coef) * dt / (dx * dx);
        x = Get_cell_coordinates(i).first;
        y = Get_cell_coordinates(i).second;
        if (x - 2 >= 0) {
            total_solution += Get_cell_solution(i - 1) * diffusion_coef * dt / (dx * dx);
            //total_impurity += Get_cell_impurity(i - 1) * diffusion_coef * dt / (dx * dx);
            //std::cout<< "L";
        }
        if (x + 2 <= Width - 2) {
            total_solution += Get_cell_solution(i + 1) * diffusion_coef * dt / (dx * dx);
            //total_impurity += Get_cell_impurity(i + 1) * diffusion_coef * dt / (dx * dx);
            //std::cout<< "R";
        }
        if (y - 2 >= 0) {
            total_solution += Get_cell_solution(i - Width / 2) * diffusion_coef * dt / (dx * dx);
            //total_impurity += Get_cell_impurity(i - Width / 2) * diffusion_coef * dt / (dx * dx);
        }
        if (y + 2 <= Height - 2) {
            total_solution += Get_cell_solution(i + Width / 2) * diffusion_coef * dt / (dx * dx);
            //total_impurity += Get_cell_impurity(i + Width / 2) * diffusion_coef * dt / (dx * dx);
        }
        Set_cell_solution(i, total_solution);
        //Set_impurity(total_impurity);
    }
    double tot_solution = 0.0;
    for(int i = 0; i < number_of_Cells; i ++)
    {
        std::cout << cell[i].Get_solution() << " ";
        //tot_solution += cell[i].Get_solution();
    }
    std::cout << "\n";
}*/


void Map::Differential_equation_iteration2() {
    Map map1(Height, Width, number_of_Cells);
    double total_solution = 0.0;
    //double total_impurity = 0.0;
    double x = 0, y = 0;
    map1 = *this;
//    for(int i = 0; i < number_of_Cells; i ++)
//    {
//        std::cout << cell[i].Get_solution() << " ";
//    }
//    std::cout << "\n";
    for (int i = 0; i < number_of_Cells; i++) {
        total_solution = 0.0;
        total_solution = Get_cell_solution(i) * (1 - 4 * diffusion_coef * dt / (dx * dx));
        //total_impurity = Get_cell_impurity(i) * (1 - 4 * diffusion_coef) * dt / (dx * dx);
        x = Get_cell_coordinates(i).first;
        y = Get_cell_coordinates(i).second;
        if (x - 2 >= 0) {
            total_solution += Get_cell_solution(i - 1) * diffusion_coef * dt / (dx * dx);
            //total_impurity += Get_cell_impurity(i - 1) * diffusion_coef * dt / (dx * dx);
        }
        if (x + 2 <= Width - 2) {
            total_solution += Get_cell_solution(i + 1) * diffusion_coef * dt / (dx * dx);
            //total_impurity += Get_cell_impurity(i + 1) * diffusion_coef * dt / (dx * dx);
        }
        if (y - 2 >= 0) {
            total_solution += Get_cell_solution(i - Width / 2) * diffusion_coef * dt / (dx * dx);
            //total_impurity += Get_cell_impurity(i - Width / 2) * diffusion_coef * dt / (dx * dx);
        }
        if (y + 2 <= Height - 2) {
            total_solution += Get_cell_solution(i + Width / 2) * diffusion_coef * dt / (dx * dx);
            //total_impurity += Get_cell_impurity(i + Width / 2) * diffusion_coef * dt / (dx * dx);
        }
        map1.Set_cell_solution(i, total_solution);
        //Set_impurity(total_impurity);
    }

    for(int i = 0; i < number_of_Cells; i ++)
    {
        std::cout << cell[i].Get_solution() << " ";
    }
    std::cout << "\n";
    *this = map1;
}

void Map::Crystallization_dissolution_check() {
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);

    std::random_device rd;
    std::mt19937 gen(seed);
    std::uniform_real_distribution<double> distrib(0, 1);

    for (int i = 0; i < number_of_Cells; i++) {
        cell[i].Set_crys_rate_prob();
        cell[i].Set_dis_rate_prob();
        double prob = distrib(gen);
        if (prob <= dis_prob) state = false;
        if (prob > dis_prob && prob <= dis_prob + crys_prob) {
            state = true;
            // тут можно процесс кристализации вынести в отдельную функцию, но мне лень
            double total_solution = 0; // итоговая концентрация, которую собираем с соседних ячеек
            int j = 1; // номер группы ячеек, в цикле они возрастают
            while (total_solution < cell[i].Get_impurity()) {

            }

        }
    }
};

void Map::Crystallization_process() {

}