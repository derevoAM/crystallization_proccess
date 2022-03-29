
#include "Cells_Draw.h"
Cells_Draw::Cells_Draw(Cells &cell) {

    /*if(cell.Get_heat_capacity()>=50){
        circle.setPointCount(8);
        circle.setRadius(static_cast<float>(cell.Get_size()));
        circle.setPosition(cell.Get_coordinates().first, cell.Get_coordinates().second);
        circle.setFillColor(color_crystal);
    }
    else{
        circle.setPointCount(6);
        circle.setPosition(cell.Get_coordinates().first, cell.Get_coordinates().second);
        circle.setRadius(static_cast<float>(cell.Get_size()));
        circle.setFillColor(color_free);
    }*/

    circle.setPointCount(8);
    circle.setRadius(static_cast<float>(.3f));
    circle.setPosition(cell.Get_coordinates().first, cell.Get_coordinates().second);
    circle.setFillColor(color_crystal);

}