//
// Created by п on 24.03.2022.
//

#include "Map_Draw.h"
template <typename T>
Map_Draw<T>:: Map_Draw(T Width,T Height){
    (sf::VideoMode(Width, Height), "Particles");
    window.setFramerateLimit(30);
    window.setVerticalSyncEnabled(true);
}
void Map_Draw<T>::  Creat_Window(T Width,T Height){
    //window(sf::VideoMode(Width, Height), "Particles");
    window.setFramerateLimit(30);
    window.setVerticalSyncEnabled(true);
}

template<typename T>
void Map_Draw<T>:: Creat_Shapes(T size){

}

template<typename T>
void Map_Draw<T>:: Set_Position(T x, T y){

}

template<typename T>
void Map_Draw<T>:: Display(){
    while (window.isOpen())
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }


        window.clear();




        //moving random particles
        for (std::size_t i = 0; i < circle_free.size(); i++) {
            sf::Vector2f offset;
            float speed = 10;
            std::pair<float, float>vel;
            //offset.x = ( speed / 2.0 - static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / speed)) );
            //offset.y = ( speed / 2.0 - static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / speed)) );
            vel.first = ( speed / 2.0 - static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / speed)) );
            vel.second = ( speed / 2.0 - static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / speed)) );
            circle_free[i].move(vel.first, vel.second);

            //printf("%i\n", sz);
            //back particles to window
            if (circle_free[i].getPosition().x > W) circle_free[i].setPosition(W-10, circle_free[i].getPosition().y);
            if (circle_free[i].getPosition().y > H) circle_free[i].setPosition(circle_free[i].getPosition().x, H-10);
            if (circle_free[i].getPosition().x < 0) circle_free[i].setPosition(10, circle_free[i].getPosition().y);
            if (circle_free[i].getPosition().y < 0) circle_free[i].setPosition(circle_free[i].getPosition().x, 10);
        }

        for (std::size_t i = 0; i < circle_free.size(); i++) {
            for (std::size_t j = 0; j < circle_stucked.size(); j++) {
                //printf("OK");
                double dist = pow(circle_free[i].getPosition().x - circle_stucked[j].getPosition().x, 2) +
                              pow(circle_free[i].getPosition().y - circle_stucked[j].getPosition().y, 2);
                dist = sqrt(dist);

                if (dist <= (r * 2) ) {//here we stuck moving particles
                    sf::Color color = sf::Color(0, 255, 0, 200);
                    circle_free[i].setFillColor(color);

                    //add moving particle to stucked vector
                    circle_stucked.push_back(circle_free[i]);
                    //delete moving particles from vector

                    circle_free.erase(circle_free.begin() + i);
                    break;
                }
            }
        }

        //draw moving particles
        for (std::size_t i = 0; i < circle_free.size(); i++) {
            window.draw(circle_free[i]);
        }
        //draw stucked particles
        for (std::size_t i = 0; i < circle_stucked.size(); i++) {
            window.draw(circle_stucked[i]);
        }

        window.display();
    }

}
