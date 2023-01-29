#include "BasicSpring.hpp"

void BasicSpring::initVariables(){
    //creating balls and adding them to a container
    Ball ball1;
    ball1.setMass(10.f);
    ball1.setDamping(0.3f);
    ball1.particle_property.setFillColor(sf::Color::White);
    ball1.particle_property.setRadius(20.f);
    ball1.particle_property.setOrigin(ball1.particle_property.getRadius(), ball1.particle_property.getRadius());
    ball1.setPosition(sf::Vector2f(640.f/2.f, 50.f));
    Ball ball2;
    ball2.setMass(10.f);
    ball2.setDamping(0.3f);
    ball2.setAcceleration(sf::Vector2f(0.f, 10.f));
    ball2.particle_property.setFillColor(sf::Color::White);
    ball2.particle_property.setRadius(20.f);
    ball2.particle_property.setOrigin(ball2.particle_property.getRadius(), ball2.particle_property.getRadius());
    ball2.setPosition(sf::Vector2f(640.f/2.f, 100.f));
    Ball ball3;
    ball3.setMass(10.f);
    ball3.setDamping(0.3f);
    ball3.setAcceleration(sf::Vector2f(0.f, 10.f));
    ball3.particle_property.setFillColor(sf::Color::White);
    ball3.particle_property.setRadius(20.f);
    ball3.particle_property.setOrigin(ball3.particle_property.getRadius(), ball3.particle_property.getRadius());
    ball3.setPosition(sf::Vector2f(640.f/2.f, 150.f));

    this->balls.push_back(ball1);
    this->balls.push_back(ball2);
    this->balls.push_back(ball3);

    //adjusting the line
    this->line.setBase(this->balls[0].getPosition());
    this->line.setDirection(this->balls[1].getPosition());
    this->line1.setBase(this->balls[1].getPosition());
    this->line1.setDirection(this->balls[2].getPosition());

    //resting position the two balls
    this->displacement = this->balls[0].getPosition() - this->balls[1].getPosition();
    this->rest_distance = this->operation._magnitude(this->displacement);
    this->displacement1 = this->balls[1].getPosition() - this->balls[2].getPosition();
    this->rest_distance1 = this->operation._magnitude(this->displacement1); 
}

BasicSpring::BasicSpring(){
    this->initVariables();
}

//defining custom functions
void BasicSpring::springCalc(){
    sf::Vector2f displacement_1 = this->balls[0].getPosition() - this->balls[1].getPosition();
    float distance_1 = this->operation._magnitude(displacement_1);

    this->force = this->spring_coefficient * (distance_1 - this->rest_distance) * this->operation._unitVector(displacement_1);
    // this->balls[0].setVelocity(-this->force);
    this->balls[1].setVelocity(this->force);
}
void BasicSpring::springCalc1(){
    sf::Vector2f displacement_1 = this->balls[1].getPosition() - this->balls[2].getPosition();
    float distance_1 = this->operation._magnitude(displacement_1);
    this->force1 = this->spring_coefficient * (distance_1 - this->rest_distance1) * this->operation._unitVector(displacement_1);

    // this->balls[1].setVelocity(-this->force1);
    this->balls[2].setVelocity(this->force1);
}
void BasicSpring::lineAdjust(Ball a, Ball b){
    this->line.setBase(a.getPosition());
    this->line.setDirection(b.getPosition());
}
void BasicSpring::lineAdjust1(Ball a, Ball b){
    this->line1.setBase(a.getPosition());
    this->line1.setDirection(b.getPosition());
}

void BasicSpring::collision(){
    for(int i = 0; i < this->balls.size(); i++){
        for(int j = 0; j < this->balls.size(); j++){
            if(this->cod._ballCollide(this->balls[i], this->balls[j]) && i != j){
                this->cod._ballBallPenetrationResolution(this->balls[i], this->balls[j]);
                this->balls[i].particle_property.move(this->cod.a_position);
                this->balls[j].particle_property.move(this->cod.b_position);
            }
        }
    }
}

//defining integrator and constructor
void BasicSpring::update(float dt, sf::Vector2f mouse_position){
    this->springCalc();
    this->springCalc1();
    this->lineAdjust(this->balls[0], this->balls[1]);
    this->lineAdjust1(this->balls[1], this->balls[2]);
    this->collision();

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        this->balls[1].setPosition(mouse_position);
    if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
        this->balls[2].setPosition(mouse_position);

    for(auto &ball : this->balls){
        ball.update(dt);
    }
}
void BasicSpring::render(sf::RenderTarget* target){
    for(auto &ball : this->balls)
        ball.render(target);
    
    this->line.render(target);
    this->line1.render(target);
}