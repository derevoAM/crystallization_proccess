
#include "Map_Draw.h"

int main() {
    unsigned Height = 1020;
    unsigned Width = 1920;
    unsigned number_of_points = 1000;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 100);
    Map map(Height, Width, number_of_points);
    Map_Draw a(map);
    a.Display();
    return 0;
}
