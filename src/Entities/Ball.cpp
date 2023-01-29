#include <SFML/Graphics.hpp>
#include "../../include/Particle.hpp"

class Ball : public Particle{
    public:
        Ball(){
            // this->acceleration = sf::Vector2f(0.f, 10.f);
        }

        void update(float dt){
            this->velocity += this->acceleration;
            this->particle_property.move(this->velocity * this->damping);
        }
};