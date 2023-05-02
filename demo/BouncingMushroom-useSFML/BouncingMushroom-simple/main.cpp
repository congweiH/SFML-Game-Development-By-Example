#include <SFML/Graphics.hpp>

int main(){
    // create window
    sf::RenderWindow window(sf::VideoMode(640,480),"BouncingMushroom-simple");

    /////////// create texture  ////////////////
    sf::Texture mushroomTexture;
    mushroomTexture.loadFromFile("Mushroom.png");
    // getsize
    sf::Vector2u size = mushroomTexture.getSize();

    //////////// create sprite  ////////////////
    sf::Sprite mushroom(mushroomTexture);
    // set origin
    mushroom.setOrigin(size.x/2, size.y/2);
    ////////////////////////////////////////////

    // create increment
    sf::Vector2f increment(0.04f, 0.04f);

    //////////////// game loop /////////////////
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

        /////////////// update /////////////////
        if((mushroom.getPosition().x + size.x/2 > window.getSize().x && increment.x > 0) || 
            (mushroom.getPosition().x - size.x/2 < 0 && increment.x < 0)){
            increment.x = -increment.x;
        }

        if((mushroom.getPosition().y + size.y/2 > window.getSize().y && increment.y > 0) ||
            (mushroom.getPosition().y - size.y/2 < 0 && increment.y < 0)){
            increment.y = -increment.y;
        }        
        // reset mushroom position
        mushroom.setPosition(mushroom.getPosition() + increment);

        /////////////// clear /////////////////
        window.clear();

        ////////////// render /////////////////
        window.draw(mushroom);

        ////////////// display ////////////////
        window.display();
    }

    return 0;
}