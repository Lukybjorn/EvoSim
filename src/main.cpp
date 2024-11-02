#include <SFML/Graphics.hpp>
#include <Eigen/Dense>
#include <iostream>
#include <random>


#include "resources.h"

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



struct WindowData {
    unsigned int width = 1920;
    unsigned int hight = 1020;
    unsigned int fps = 60;

    bool resized = false;

    void print_size() const {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space))
        {
            std::cout << "Width: " << width << ", Hight: " << hight << std::endl;
        }
    }
};

struct MouseData {
    unsigned int x = 0;
    unsigned int y = 0;
    bool left = false;
    bool right = false;
    bool moved = false;

    void print_location() const {
        if (left | right) {
            std::cout << "(x,y): (" << x << ", " << y << ")"  << std::endl;
        }
    }
};


int main() {
    // test_network();
    sf::Font arial;
    if (!arial.loadFromFile("C:/Windows/Fonts/times.ttf")) return 1;

    WindowData win_data;
    MouseData mouse_data;

    sf::RenderWindow window(sf::VideoMode(win_data.width, win_data.hight), "Test window");
    window.setFramerateLimit(win_data.fps);


    Textbox text1(20, sf::Color::Blue, true);
    text1.setPosition({ 100, 50 });
    text1.setLimit(true, 30);
    text1.setFont(arial);

    Button btn1("Play Game", { 170, 50 }, 17, sf::Color::Green, sf::Color::Black);
    btn1.setFont(arial);
    btn1.setPosition(sf::Vector2f(900 / 2.0f - 170, 900 / 2.0f));

    //Start of the window loop
    while (window.isOpen()) {

        // Start of the event loop
        sf::Event event;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
            text1.setSelected(true);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            text1.setSelected(false);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {

        }

        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            switch (event.type) {
                //Close event
                case sf::Event::Closed:
                    window.close();
                break;

                //Resize event - set it's new parameters in win_data
                case sf::Event::Resized:
                    win_data.width = event.size.width;
                    win_data.hight = event.size.height;
                break;

                //Mouse moved inside the window - set it's location in mouse_dat
                case sf::Event::MouseMoved:
                    mouse_data.x = event.mouseMove.x;
                    mouse_data.y = event.mouseMove.y;
                    if (btn1.isMouseOver(window)) {
                        // Highlight buttons when mouse is over them:
                        btn1.setBackColor(sf::Color(153, 204, 0));
                    }
                    else {
                        btn1.setBackColor(sf::Color(102, 102, 51));
                    }
                break;

                //Mouse Button pressed - set the data of the specific button to true
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        mouse_data.left = true;
                    }
                    else if (event.mouseButton.button == sf::Mouse::Right) {
                        mouse_data.right = true;
                    }
                    mouse_data.x = event.mouseButton.x;
                    mouse_data.y = event.mouseButton.y;
                    if (btn1.isMouseOver(window)) {
                        std::cout << text1.getText() << std::endl;
                    }
                break;

                //Mouse Button pressed - set the data of the specific button to false
                case sf::Event::MouseButtonReleased:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        mouse_data.left = false;
                    }
                    else if (event.mouseButton.button == sf::Mouse::Right) {
                        mouse_data.right = false;
                    }
                    mouse_data.x = event.mouseButton.x;
                    mouse_data.y = event.mouseButton.y;
                break;

                case sf::Event::TextEntered:
                    text1.typedOn(event);

                default:
                    break;
            }

            // if (event.type == sf::Event::Closed)
            //     window.close();
        }


        //Start of the display procedure
        window.clear(sf::Color::White);
        btn1.drawTo(window);
        text1.drawTo(window);
        window.display();

        mouse_data.print_location();
        win_data.print_size();
    }
    return 0;
}
