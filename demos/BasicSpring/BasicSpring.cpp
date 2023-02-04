#include "BasicSpring.hpp"

void BasicSpring::initVariables(){
    //creating balls and adding them to a container
    Ball ball1;
    ball1.setMass(3.f);
    ball1.setDamping(0.3f);
    ball1.particle_property.setFillColor(sf::Color::White);
    ball1.particle_property.setRadius(5.f);
    ball1.particle_property.setOrigin(ball1.particle_property.getRadius(), ball1.particle_property.getRadius());
    ball1.setPosition(sf::Vector2f(640.f/2.f, 50.f));
    Ball ball2;
    ball2.setMass(3.f);
    ball2.setDamping(0.3f);
    ball2.setAcceleration(sf::Vector2f(0.f, 5.f));
    ball2.particle_property.setFillColor(sf::Color::White);
    ball2.particle_property.setRadius(5.f);
    ball2.particle_property.setOrigin(ball2.particle_property.getRadius(), ball2.particle_property.getRadius());
    ball2.setPosition(sf::Vector2f(640.f/2.f, 55.f));
    Ball ball3;
    ball3.setMass(3.f);
    ball3.setDamping(0.3f);
    ball3.setAcceleration(sf::Vector2f(0.f, 5.f));
    ball3.particle_property.setFillColor(sf::Color::White);
    ball3.particle_property.setRadius(5.f);
    ball3.particle_property.setOrigin(ball3.particle_property.getRadius(), ball3.particle_property.getRadius());
    ball3.setPosition(sf::Vector2f(640.f/2.f, 60.f));
    Ball ball4;
    ball4.setMass(3.f);
    ball4.setDamping(0.3f);
    ball4.setAcceleration(sf::Vector2f(0.f, 5.f));
    ball4.particle_property.setFillColor(sf::Color::White);
    ball4.particle_property.setRadius(5.f);
    ball4.particle_property.setOrigin(ball4.particle_property.getRadius(), ball4.particle_property.getRadius());
    ball4.setPosition(sf::Vector2f(640.f/2.f, 65.f));
    Ball ball5;
    ball5.setMass(3.f);
    ball5.setDamping(0.3f);
    ball5.setAcceleration(sf::Vector2f(0.f, 5.f));
    ball5.particle_property.setFillColor(sf::Color::White);
    ball5.particle_property.setRadius(5.f);
    ball5.particle_property.setOrigin(ball5.particle_property.getRadius(), ball5.particle_property.getRadius());
    ball5.setPosition(sf::Vector2f(640.f/2.f, 70.f));
    Ball ball6;
    ball6.setMass(3.f);
    ball6.setDamping(0.3f);
    ball6.setAcceleration(sf::Vector2f(0.f, 5.f));
    ball6.particle_property.setFillColor(sf::Color::White);
    ball6.particle_property.setRadius(5.f);
    ball6.particle_property.setOrigin(ball6.particle_property.getRadius(), ball6.particle_property.getRadius());
    ball6.setPosition(sf::Vector2f(640.f/2.f, 75.f));
    this->ball_big;
    this->ball_big.setMass(30.f);
    this->ball_big.setDamping(0.3f);
    this->ball_big.particle_property.setFillColor(sf::Color::White);
    this->ball_big.particle_property.setRadius(50.f);
    this->ball_big.particle_property.setOrigin(this->ball_big.particle_property.getRadius(), this->ball_big.particle_property.getRadius());
    this->ball_big.setPosition(sf::Vector2f(0.f, 0.f));

    this->balls.push_back(ball1);
    this->balls.push_back(ball2);
    this->balls.push_back(ball3);
    this->balls.push_back(ball4);
    this->balls.push_back(ball5);
    this->balls.push_back(ball6);

    //...    
    // this->lines.push_back(this->line);
    // this->lines.push_back(this->line1);
    for(int i = 0; i < this->balls.size()-1; i++){
        this->createLine();
    }

    //resting position the two balls
    this->displacement = this->balls[0].getPosition() - this->balls[1].getPosition();
    this->rest_distance = this->operation._magnitude(this->displacement);
}

BasicSpring::BasicSpring(){
    this->initVariables();
}

//defining custom functions
void BasicSpring::springCalc(){
    for(int i = 1; i < this->balls.size()-1; i++){
        sf::Vector2f displacement_1 = this->balls[i-1].getPosition() - this->balls[i].getPosition();
        float distance_1 = this->operation._magnitude(displacement_1);
        this->force = this->spring_coefficient * (distance_1 - this->rest_distance) * this->operation._unitVector(displacement_1);
        
        sf::Vector2f displacement_2 = this->balls[i].getPosition() - this->balls[i+1].getPosition();
        float distance_2 = this->operation._magnitude(displacement_2);
        this->force1 = this->spring_coefficient * (distance_2 - this->rest_distance) * this->operation._unitVector(displacement_2);

        this->resultant_force = -this->force1/2.f + this->force;

        this->balls[i].setVelocity(this->resultant_force);
        int j = i+1;
        this->balls[j].setVelocity(this->force1);
    }
}

void BasicSpring::lineAdjust(){
    for(int i = 0; i < this->lines.size(); i++){
        this->lines[i].setBase(this->balls[i].getPosition());
        this->lines[i].setDirection(this->balls[i+1].getPosition());
    }
}

void BasicSpring::collision(){
    for(int i = 0; i < this->balls.size(); i++){
        for(int j = 0; j < this->balls.size(); j++){
            if(this->cod._ballCollide(this->balls[i], this->balls[j]) && i != j){
                this->cod._ballBallPenetrationResolution(this->balls[i], this->balls[j]);
                this->balls[i].particle_property.move(this->cod.a_position);
                this->balls[j].particle_property.move(this->cod.b_position);
            }
            if(this->cod._ballCollide(this->balls[j], this->ball_big)){
                this->cod._ballBallPenetrationResolution(this->balls[j], this->ball_big);
                this->balls[j].particle_property.move(this->cod.a_position);
                this->ball_big.particle_property.move(this->cod.b_position);
            }
        }
    }
}
void BasicSpring::createLine(){
    Line line;
    this->lines.push_back(line);
}

//defining integrator and constructor
void BasicSpring::update(float dt, sf::Vector2f mouse_position){
    this->balls[0].setPosition(sf::Vector2f(640.f/2.f, 50.f));
    this->springCalc();
    this->lineAdjust();
    this->collision();
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        this->balls[1].setPosition(mouse_position);
    if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
        this->balls[2].setPosition(mouse_position);
    if(sf::Mouse::isButtonPressed(sf::Mouse::Middle)){
        this->ball_big.setPosition(mouse_position);
    }

    for(auto &ball : this->balls){
        ball.update(dt);
    }

    this->ball_big.update(dt);
}
void BasicSpring::render(sf::RenderTarget* target){
    for(auto &ball : this->balls)
        ball.render(target);

    //..
    for(auto &line : this->lines)
        line.render(target);
    
    this->ball_big.render(target);
    // this->lines[0].render(target);
    // this->lines[1].render(target);
    // line.render(target);
    // line1.render(target);
}