//
// Created by п on 24.03.2022.
//

#ifndef FIRST_ATTEMPT_MAP_H
#define FIRST_ATTEMPT_MAP_H
#include "Points.h"
//template<unsigned T>
class Map: protected Points {
protected:
    unsigned Height;
    unsigned Width;
    unsigned number_of_points;
    std:: vector<Points> point;
public:
    Map();
    Map( unsigned ,  unsigned, unsigned );
    Map(const Map&);
    Map& operator = (const Map& map);
    ~Map() = default;
    unsigned Get_Height()const{ return Height; };
    unsigned Get_Width() const {return Width;};
    void Set_point_coordinates(unsigned i, double x, double y){
        point[i].Set_coordinates(x,y);
    };
    void Set_point_heat_capacity (unsigned i, double heat_capacity){
        point[i].Set_heat_capacity(heat_capacity);
    }
    void Set_point_impurity(unsigned i, double impurity){
        point[i].Set_impurity(impurity);
    }
    std:: pair<double, double> Get_point_coordinates(unsigned i) const{
        return point[i].Get_coordinates();
    }
    double Get_point_size(unsigned i)const{
        return point[i].Get_size();
    }
    double Get_point_heat_capacity(unsigned i)const{
        return point[i].Get_heat_capacity();
    }
    double Get_point_impurity(unsigned i) const{
        return point[i].Get_impurity();
    }
    Points& Get_point_i(unsigned i){
        return point[i];
    }
    unsigned Get_number_of_points(){
        return number_of_points;
    }
    void Set_Point_heat_capacity_iterative();
    void Set_Point_coordinates_iterative();
};




#endif //FIRST_ATTEMPT_MAP_H
