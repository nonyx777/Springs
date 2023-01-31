#include <SFML/Graphics.hpp>
#include "../../include/Particle.hpp"

class Ball : public Particle{
    public:
        void update(float dt){
            this->velocity += this->acceleration;
            this->particle_property.move(this->velocity);
        }
};