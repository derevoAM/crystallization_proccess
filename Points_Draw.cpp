
#include "Points_Draw.h"
Points_Draw::Points_Draw(Points &point) {

    if(point.Get_heat_capacity()>=50){
        circle.setPointCount(8);
        circle.setRadius(static_cast<float>(point.Get_size()));
        circle.setPosition(point.Get_coordinates().first, point.Get_coordinates().second);
        circle.setFillColor(color_crystal);
    }
    else{
        circle.setPointCount(6);
        circle.setPosition(point.Get_coordinates().first, point.Get_coordinates().second);
        circle.setRadius(static_cast<float>(point.Get_size()));
        circle.setFillColor(color_free);
    }
}