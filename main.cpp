
// -I/usr/local/Cellar/sfml/2.5.1_2/include -L/usr/local/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio -lsfml-window

#include <SFML/Graphics.hpp>
#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    sf::CircleShape shape(100.f);
    sf::Vector2f circlePos(500,500);
    shape.setPosition(circlePos);
    shape.setFillColor(sf::Color::Green);

    std::vector<sf::Shape*> obstacles;
    sf::RectangleShape* rect1 = new sf::RectangleShape(sf::Vector2f(50, 200));
    rect1->setPosition(725,400);
    rect1->setFillColor(sf::Color::Red);
    obstacles.push_back(rect1);
    sf::RectangleShape* rect2 = new sf::RectangleShape(sf::Vector2f(100, 100));
    obstacles.push_back(rect2);
    rect2->setPosition(200,700);
    rect2->setFillColor(sf::Color::Red);
    sf::RectangleShape* rect3 = new sf::RectangleShape(sf::Vector2f(100, 100));
    obstacles.push_back(rect3);
    rect3->setPosition(200,200);
    rect3->setFillColor(sf::Color::Red);
    

    int l = obstacles.size();


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
        for (int i=0; i<l; i++) {
            window.draw(*obstacles[i]);
        }
        window.display();
    }

    return 0;
}