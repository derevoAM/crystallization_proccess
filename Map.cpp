//
// Created by п on 24.03.2022.
//

#include "Map.h"
#include <iomanip>

//default constructor
Map::Map() : Height(600), Width(800), number_of_Cells(1000) {
    cell.resize(Height / 2);
    for (auto &it: cell) {
        it.resize(Width / 2);
    }
}

//constructor
Map::Map(unsigned int H, unsigned int W, unsigned int N) : Height(H), Width(W), number_of_Cells(N) {
    cell.resize(Height / 2);
    for (auto &it: cell) {
        it.resize(Width / 2);
    }
}

//copy constructor
Map::Map(const Map &map) : Height(map.Height), Width(map.Width), number_of_Cells(map.number_of_Cells) {
    cell.resize(map.Height / 2);
    for (auto &it: cell) {
        it.resize(map.Width / 2);
    }
    for (int i = 0; i < map.Height / 2; i++) {
        for (int j = 0; j < map.Width / 2; j++) cell[i][j] = map.cell[i][j];
    }
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
    cell.resize(map.Height);
    for (auto &it: cell) {
        it.resize(map.Width);
    }
    for (int i = 0; i < map.Height / 2; i++) {
        for (int j = 0; j < map.Width / 2; j++) cell[i][j] = map.cell[i][j];
    }
    //надо бы еще значения скопировать, но мне лень - готово
    return *this;
}

// рандомно задает начальные значения ячейкам карты
void Map::Set_cell_origin() {
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);
    //tot_solution = 0.0;
    std::random_device rd;
    std::mt19937 gen(seed);
    std::uniform_real_distribution<double> distrib(0, 1);
    for (unsigned i = 0; i < Height / 2; i++) {
        for (unsigned j = 0; j < Width / 2; j++) {

            cell[i][j].Set_coordinates(i, j);
            double rand_temp = distrib(gen);
            if (i == 0 || i == Height / 2 - 1 || j == 0 || j == Width / 2 - 1)
                rand_temp = 0; // граничные условия(пока поставил 0 в граничных ячейках 0 концентрацию вещества, но нужно подумать)
            cell[i][j].Set_solution(max_density * rand_temp / 2);
            //cell[i][j].Set_impurity(max_density - cell[i][j].Get_solution());
            cell[i][j].Set_next_step_solution(max_density * rand_temp / 2);
            cell[i][j].Set_state(false);
            //std::cout << i << " " << j << "\n";
        }
    }
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

//Тут чуть подправил, идея в чем:
//Завели новое поле со значением следущего шага
//И присваиваем значение для следущего шага
void Map::Differential_equation_iteration2() {
    double total_solution = 0.0;
    std::pair<double, double> coordinates_temp;

    // перезаписываем концентрацию в каждой ячейке
    for (int i = 1; i < Height / 2 - 1; i++) {
        for (int j = 1; j < Width / 2 - 1; j++) {
            Set_cell_solution(i, j, Get_cell_next_step_solution(i, j));
        }
    }
    // используем решение дифура для задания концентрации и состояния ячейки на следующей итерации
    for (int i = 1; i < Height / 2 - 1; i++) {
        for (int j = 1; j < Width / 2 - 1; j++) {
            total_solution = 0.0;
            coordinates_temp.first = i;
            coordinates_temp.second = j;

            total_solution = Get_cell_solution(i, j) * (1 - 4 * diffusion_coef * dt / (dx * dx));
            // блок с if при отсутствии граничных условий
            /*
            if (i - 1 >= 0) {
                total_solution += Get_cell_solution(i - 1, j) * diffusion_coef * dt / (dx * dx);
            }
            if (i + 1 < Height / 2) {
                total_solution += Get_cell_solution(i + 1, j) * diffusion_coef * dt / (dx * dx);
            }

            if (j - 1 >= 0) {
                total_solution += Get_cell_solution(i, j - 1) * diffusion_coef * dt / (dx * dx);
            }
            if (j + 1 < Width / 2) {
                total_solution += Get_cell_solution(i, j + 1) * diffusion_coef * dt / (dx * dx);
            }*/

            total_solution += Get_cell_solution(i - 1, j) * diffusion_coef * dt / (dx * dx);
            total_solution += Get_cell_solution(i + 1, j) * diffusion_coef * dt / (dx * dx);
            total_solution += Get_cell_solution(i, j - 1) * diffusion_coef * dt / (dx * dx);
            total_solution += Get_cell_solution(i, j + 1) * diffusion_coef * dt / (dx * dx);

            Set_cell_next_step_solution(i, j, total_solution);
            //std::cout << i << " " << j << "\n";
        }
    }

//    double tot_solution = 0.0;
//    for (int i = 0; i < Height / 2; i++) {
//        for (int j = 0; j < Width; j++) tot_solution += cell[i][j].Get_solution();
//    }
    //std::cout << tot_solution << "\n";
}

// процесс растворения и кристаллизации
void Map::Crystallization_dissolution_check() {
    //std::cout << "check ok" << "\n";
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);
    std::vector<std::pair<int, int>> true_state;
    std::random_device rd;
    std::mt19937 gen(seed);
    std::uniform_real_distribution<double> distrib(0, 1);
    std::pair<int, int> coord;
    int counter_state = 0;
    for (int i = 1; i < Height / 2 - 1; i++) {
        for (int j = 1; j < Width / 2 - 1; j++) {
            cell[i][j].Set_crys_rate_prob();
            cell[i][j].Set_dis_rate_prob();
            double prob = distrib(gen);
            if (prob <= cell[i][j].Get_dis_prob()) cell[i][j].Set_state(false);
            if (prob > cell[i][j].Get_dis_prob() && prob <= cell[i][j].Get_dis_prob() + cell[i][j].Get_crys_prob()) {
                cell[i][j].Set_state(true);
                coord.first = i;
                coord.second = j;
                true_state.push_back(coord);
                counter_state++;

            }
            //std::cout << cell[i][j].Get_crys_prob() << "\n";
        }
    }
    //std::cout << counter_state << "\n";
    for (int count = 0; count < counter_state; count++) {
        int i = true_state[count].first;
        int j = true_state[count].second;
        //double total_solution = 0; // итоговая концентрация, которую собираем с соседних ячеек
        int k = 1; // номер группы ячеек, в цикле они возрастают
        double needed_solution = max_density - cell[i][j].Get_next_step_solution();
        double summary_group_solution;
        int x, y;
        double ratio = 0.0; // коэффициент пропорциональности
        while (needed_solution > 0) {

            summary_group_solution = 0; // количество вещества, находящееся в ячейках данной группы
            // сначала вычисление суммарного количества вещества в ячейках данной группы
            if (j - k >= 0) {
                if (!cell[i][j - k].Get_state()) summary_group_solution += cell[i][j - k].Get_next_step_solution();

            }
            if (j + k <= Width / 2 - 1) {
                if (!cell[i][j + k].Get_state()) summary_group_solution += cell[i][j + k].Get_next_step_solution();
            }
            for (y = j - k + 1; y < j + k; y++) {
                x = i + k - abs(j - y);
                if (x >= 0 && x < Height / 2 && y >= 0 && y < Width / 2) {
                    if (!cell[x][y].Get_state()) summary_group_solution += cell[x][y].Get_next_step_solution();
                }
                x = i - k + abs(j - y);
                if (x >= 0 && x < Height / 2 && y >= 0 && y < Width / 2) {
                    if (!cell[x][y].Get_state()) summary_group_solution += cell[x][y].Get_next_step_solution();
                }
            }
            //std::cout << summary_group_solution << "\n";
            // проверяем, хватает ли вещества в данной группе для кристаллизующейся ячейки
            if (summary_group_solution >= needed_solution) {
                ratio = needed_solution / summary_group_solution;
                cell[i][j].Set_next_step_solution(max_density);
                //cell[i][j].Set_impurity(0.0);
            } else {
                ratio = 1;
                cell[i][j].Set_next_step_solution(cell[i][j].Get_next_step_solution() + summary_group_solution);
                //cell[i][j].Set_impurity(max_density - cell[i][j].Get_solution());
            }
            // собираем с ячеек данной группы нужное количество вещества
            double current_solution; // для удобства - количество вещества в конкретной ячейке
            if (j - k >= 0) {
                if (!cell[i][j - k].Get_state()){
                    current_solution = cell[i][j - k].Get_next_step_solution();
                    cell[i][j - k].Set_next_step_solution(current_solution * (1 - ratio));
                }
            }
            if (j + k <= Width / 2 - 1) {
                if (!cell[i][j + k].Get_state()) {
                    current_solution = cell[i][j + k].Get_next_step_solution();
                    cell[i][j + k].Set_next_step_solution(current_solution * (1 - ratio));
                }
            }
            for (y = j - k + 1; y < j + k; y++) {
                x = i + k - abs(j - y);
                if (x >= 0 && x < Height / 2 && y >= 0 && y < Width / 2) {
                    if (!cell[x][y].Get_state()) {
                        current_solution = cell[x][y].Get_next_step_solution();
                        cell[x][y].Set_next_step_solution(current_solution * (1 - ratio));
                    }
                }
                x = i - k + abs(j - y);
                if (x >= 0 && x < Height / 2 && y >= 0 && y < Width / 2) {
                    if (!cell[x][y].Get_state()) {
                        current_solution = cell[x][y].Get_next_step_solution();
                        cell[x][y].Set_next_step_solution(current_solution * (1 - ratio));
                    }
                }
            }



            needed_solution -= summary_group_solution;
            k++;
        }
        //std::cout << i << " " << j << "\n";
    }

};
