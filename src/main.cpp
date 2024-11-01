#include <SFML/Graphics.hpp>
#include <Eigen/Dense>
#include <iostream>
#include <random>


#include "Network.h"
#include "Object.h"

void test_network() {
    std::srand(time(nullptr));

    const int depth = 10;
    std::vector<int> vec;
    for (int i = 0; i < depth; i++) {
        vec.push_back(depth);
    }

    Network network(2, depth, vec,2, false);
    Eigen::VectorXf in(2);
    in.setRandom();
    network.set_input_vector(in);
    std::cout << "input vector: \n" << network.input_vector() << std::endl;

    network.calculate_output_vector();

    std::cout << "output vector: \n" << network.output_vector()<< std::endl;
    // std::cout << network << std::endl;


    Eigen::Vector3i color;
    color << 0, 0, 0;

    Eigen::Vector2f location_1;
    location_1 << 0, 0;
    Eigen::Vector2f location_2;
    location_2 << 0, 10;

    Object obj_1(location_1, 5, color);
    Object obj_2(location_2, 2, color);

    std::cout << "collision: " << obj_1.collision(obj_2) << std::endl;

}

int main() {
    // test_network();
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test window");
    window.setFramerateLimit(60);

    //Start of the window loop
    while (window.isOpen()) {

        // Start of the event loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //Start of the display procedure
        window.clear();
        window.display();
    }

    Eigen::Vector2f new_v;
    new_v << 0.3, 0.4;
    std::cout << "Nevo: \n" << new_v <<std::endl;

    return 0;
}
