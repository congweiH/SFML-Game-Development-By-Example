#include <SFML/Graphics.hpp>

int main() {
    // create window
    sf::RenderWindow window(sf::VideoMode(640, 480), "First window!");

    // game loop
    while (window.isOpen()) {
        sf::Event event;
        // check events
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                // Close window button clicked.
                window.close();
            }
        }
        // 清屏，用黑色填充
        window.clear(sf::Color::Black);

        // Draw here.

        // 展示画的内容
        window.display();
    }
    return 0;
}