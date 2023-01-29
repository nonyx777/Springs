#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../demos/BasicSpring/BasicSpring.hpp"

using namespace std;

class Engine{
    private:
        //initializer functions
        void initVariables();
        void initWindow();

        //window variables
        sf::RenderWindow* window;
        sf::VideoMode video_mode;
        sf::Event event;

        //instantiating objects
        BasicSpring basicSpring;

        //mouse position
        sf::Vector2i mouse_position;
        sf::Vector2f mouse_position_view;

    public:
        //constructor and destructor
        Engine();
        ~Engine();

        //window functions
        void pollEvent();
        void update(float dt);
        void render();

        //Accessors
        const bool running() const;
};