#include <SFML/Graphics.hpp>
#include <iostream>
#include "../../src/logic/CollisionDetectionOperation.h"

class BasicSpring{
    private:
        std::vector<Ball> balls;

        //hooks law
        sf::Vector2f force;
        sf::Vector2f displacement;
        float rest_distance;
        sf::Vector2f force1;
        sf::Vector2f displacement1;
        float rest_distance1;
        float spring_coefficient = 0.2f;

        //instantiating objects
        CollisionDetectionOperation cod;
        Operation operation;
        Line line;
        Line line1;

        //..
        void initVariables();

    public:
        BasicSpring();

        //custom functions
        void springCalc();
        void springCalc1();
        void lineAdjust(Ball a, Ball b);
        void lineAdjust1(Ball a, Ball b);
        void collision();

        //integrator and displayer
        void update(float dt, sf::Vector2f mouse_position);
        void render(sf::RenderTarget* target);
};