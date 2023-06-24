
// -I/usr/local/Cellar/sfml/2.5.1_2/include -L/usr/local/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio -lsfml-window

#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    sf::CircleShape shape(100.f);
    sf::Vector2f circlePos(500,500);
    shape.setPosition(circlePos);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (circlePos.x >= 0) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
                shape.move(sf::Vector2f(-0.25,0));
                circlePos.x -= 0.25;
            } 
            shape.setPosition(circlePos);
        }

        if (circlePos.x <=800) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
                shape.move(sf::Vector2f(0.25,0));
                circlePos.x += 0.25;
            } 
            shape.setPosition(circlePos);
        }
        
        if (circlePos.y >= 0) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
                shape.move(sf::Vector2f(0,-0.25));
                circlePos.y -= 0.25;
            } 
            shape.setPosition(circlePos);
        }
        
        if (circlePos.y <= 800) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
                shape.move(sf::Vector2f(0,0.25));
                circlePos.y += 0.25;
            }
            shape.setPosition(circlePos);
        }
        

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}