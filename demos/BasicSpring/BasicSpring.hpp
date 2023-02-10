#include <SFML/Graphics.hpp>
#include <iostream>
#include "../../src/logic/CollisionDetectionOperation.h"

class BasicSpring{
    private:
        std::vector<Ball> balls;
        std::vector<Line> lines;

        //hooks law
        sf::Vector2f force;
        sf::Vector2f displacement;
        float rest_distance;
        sf::Vector2f force1;
        sf::Vector2f displacement1;
        float rest_distance1;
        float spring_coefficient = 0.3f;
        //..D'alembert's force
        sf::Vector2f resultant_force;

        //instantiating objects
        CollisionDetectionOperation cod;
        Operation operation;
        Ball ball_big;

        //window boundary(line)
        Line low_boundary = Line(sf::Vector2f(0.f, 360.f), sf::Vector2f(640.f, 360.f));

        //..
        void initVariables();

    public:
        BasicSpring();

        //custom functions
        void springCalc();
        void lineAdjust();
        void collision();
        void createLine();

        //integrator and displayer
        void update(float dt, sf::Vector2f mouse_position);
        void render(sf::RenderTarget* target);
};