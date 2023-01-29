#include <SFML/Graphics.hpp>

class Particle{
    protected:
        float mass, damping, elasticity;
        float inverse_mass;
        sf::Vector2f position, velocity, acceleration;
    
    public:
        Particle();
        sf::CircleShape particle_property;

        //integrator and displayer
        virtual void update(float dt);
        void render(sf::RenderTarget* target);

        //declaring accessors and mutators
        void setMass(float mass);
        float getMass();
        float getInverseMass();
        void setDamping(float damping);
        float getDamping();
        void setPosition(sf::Vector2f position);
        sf::Vector2f getPosition();
        void setVelocity(sf::Vector2f velocity);
        sf::Vector2f getVelocity();
        void setAcceleration(sf::Vector2f acceleration);
        sf::Vector2f getAcceleration();
        void setElasticity(float elasticity);
        float getElasticity();
};