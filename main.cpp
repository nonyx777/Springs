#include "interface/Engine.h"

using namespace std;

float dt;

int main()
{
    //instantiate object
    Engine engine;
    sf::Clock clock;

    //engine loop
    while(engine.running()){

        dt = clock.restart().asSeconds();

        //update frame by frame
        engine.update(dt);
        //render frame
        engine.render();
    }

    return 0;
}