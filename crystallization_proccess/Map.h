//
// Created by п on 24.03.2022.
//
//Это класс отвечающий за карту и что происходит с кружочкам,
// думаю это главный класс, в котором  будет вся математика( я так вижу)
#ifndef FIRST_ATTEMPT_MAP_H
#define FIRST_ATTEMPT_MAP_H

#include "Cells.h"

//template<unsigned T>
class Map : public Cells {
protected:
    unsigned Height;
    unsigned Width;
    unsigned number_of_Cells;
    std::vector<Cells> cell;
public:
    Map();

    Map(unsigned, unsigned, unsigned);

    Map(const Map &);

    Map& operator=(const Map &map);

    ~Map() = default;

    unsigned Get_Height() const { return Height; };

    unsigned Get_Width() const { return Width; };

    void Set_cell_coordinates(unsigned i, double x, double y) {
        cell[i].Set_coordinates(x, y);
    };

    void Set_cell_impurity(unsigned i, double impurity) {
        cell[i].Set_impurity(impurity);
    }

    std::pair<double, double> Get_cell_coordinates(unsigned i) const {
        return cell[i].Get_coordinates();
    }

    double Get_cell_impurity(unsigned i) const {
        return cell[i].Get_impurity();
    }

    Cells &Get_cell_i(unsigned i) {
        return cell[i];
    }
    Cells Get_cell_i(unsigned i) const{
        return cell[i];
    }

    unsigned Get_number_of_Cells() {
        return number_of_Cells;
    }

    void Set_cell_concentration_capacity_iterative();

    void Set_cell_coordinates_iterative();
};


#endif //FIRST_ATTEMPT_MAP_H
