#include "include/Particle.hpp"

Particle::Particle(){
    //...
}

//defining integrator and displayer
void Particle::update(float dt){
    //...
}
void Particle::render(sf::RenderTarget* target){
    target->draw(this->particle_property);
}

//defining accessors and mutators
void Particle::setMass(float mass){
    this->mass = mass;
}
float Particle::getMass(){
    return this->mass;
}
float Particle::getInverseMass(){
    this->inverse_mass = this->mass == 0.f ? 0.f : 1.f/this->mass;
    return this->inverse_mass;
}
void Particle::setDamping(float damping){
    this->damping = damping;
}
float Particle::getDamping(){
    return this->damping;
}
void Particle::setPosition(sf::Vector2f position){
    this->particle_property.setPosition(position);
    this->position = position;
}
sf::Vector2f Particle::getPosition(){
    return this->particle_property.getPosition();
}
void Particle::setVelocity(sf::Vector2f velocity){
    this->velocity = velocity;
}
sf::Vector2f Particle::getVelocity(){
    return this->velocity;
}
void Particle::setAcceleration(sf::Vector2f acceleration){
    this->acceleration = acceleration;
}
sf::Vector2f Particle::getAcceleration(){
    return this->acceleration;
}
void Particle::setElasticity(float elasticity){
    this->elasticity = elasticity;
}
float Particle::getElasticity(){
    return this->elasticity;
}