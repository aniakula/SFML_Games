#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
    sf::RectangleShape shape(sf::Vector2f(50.f, 50.f));
    shape.setOrigin(sf::Vector2f(0.f, 0.f));
    shape.setFillColor(sf::Color::Blue);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type){
                case(sf::Event::Closed):
                    window.close();
                    break;
                
            }
        }

        // Key press detection and shape movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            shape.move(0.1f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            shape.move(-0.1f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            shape.move(0.f, -0.1f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            shape.move(0.f, 0.1f);

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
