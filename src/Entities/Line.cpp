#include <SFML/Graphics.hpp>

class Line{
    private:
        sf::Vector2f base;
        sf::Vector2f direction;
    
    public:
        Line(){
            
        }
        Line(sf::Vector2f base, sf::Vector2f direction){
            this->base = base;
            this->direction = direction;
        }

        void render(sf::RenderTarget* target){
            sf::Vertex line[] = {
                this->getBase(),
                this->getDirection()
            };
            target->draw(line, 2, sf::Lines);
        }

        //defining accessors and mutators
        void setBase(sf::Vector2f base){
            this->base = base;
        }
        void setDirection(sf::Vector2f direction){
            this->direction = direction;
        }
        sf::Vector2f getBase(){
            return this->base;
        }
        sf::Vector2f getDirection(){
            return this->direction;
        }
};