
// -I/usr/local/Cellar/sfml/2.5.1_2/include -L/usr/local/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio -lsfml-window

#include <SFML/Graphics.hpp>
#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");

    // Make 2 circles (will be tanks)
    std::vector<sf::Shape*> tanks;

    sf::CircleShape* tank1 = new sf::CircleShape(50);
    sf::Vector2f tank1pos = sf::Vector2f(250,500);
    tank1->setPosition(tank1pos);
    tank1->setFillColor(sf::Color::Green);
    tanks.push_back(tank1);

    sf::CircleShape* tank2 = new sf::CircleShape(50);
    sf::Vector2f tank2pos = sf::Vector2f(750,500);
    tank2->setPosition(tank2pos);
    tank2->setFillColor(sf::Color::Cyan);
    tanks.push_back(tank2);

    // Make Obstacles
    std::vector<sf::Shape*> obstacles;

    sf::RectangleShape* rect1 = new sf::RectangleShape(sf::Vector2f(50, 200));
    sf::Vector2f rect1pos = sf::Vector2f(750,400);
    rect1->setPosition(rect1pos);
    rect1->setFillColor(sf::Color::Red);
    obstacles.push_back(rect1);

    sf::RectangleShape* rect2 = new sf::RectangleShape(sf::Vector2f(100, 100));
    sf::Vector2f rect2pos = sf::Vector2f(200,700);
    rect2->setPosition(rect2pos);
    rect2->setFillColor(sf::Color::Red);
    obstacles.push_back(rect2);

    sf::RectangleShape* rect3 = new sf::RectangleShape(sf::Vector2f(100, 100));
    sf::Vector2f rect3pos = sf::Vector2f(200,200);
    rect3->setPosition(rect3pos);
    rect3->setFillColor(sf::Color::Red);
    obstacles.push_back(rect3);
    
    int l1 = tanks.size();
    int l2 = obstacles.size();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Tank 1 Movement using WASD
        if (tank1pos.x >= 0) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
                tank1->move(sf::Vector2f(-0.25,0));
                tank1pos.x -= 0.25;
            } 
        }

        if (tank1pos.x <= 1000 - 100) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
                tank1->move(sf::Vector2f(0.25,0));
                tank1pos.x += 0.25;
            } 
        }
        
        if (tank1pos.y >= 0) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
                tank1->move(sf::Vector2f(0,-0.25));
                tank1pos.y -= 0.25;
            } 
        }
        
        if (tank1pos.y <= 1000 - 100) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
                tank1->move(sf::Vector2f(0,0.25));
                tank1pos.y += 0.25;
            }
        }

        // Tank 2 Movement using Arrow Keys
        if (tank2pos.x >= 0) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
                tank2->move(sf::Vector2f(-0.25,0));
                tank2pos.x -= 0.25;
            } 
        }

        if (tank2pos.x <= 1000 - 100) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
                tank2->move(sf::Vector2f(0.25,0));
                tank2pos.x += 0.25;
            } 
        }
        
        if (tank2pos.y >= 0) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
                tank2->move(sf::Vector2f(0,-0.25));
                tank2pos.y -= 0.25;
            } 
        }
        
        if (tank2pos.y <= 1000 - 100) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
                tank2->move(sf::Vector2f(0,0.25));
                tank2pos.y += 0.25;
            }
        }

        window.clear();
        for (int i=0; i<l1; i++) {
            window.draw(*tanks[i]);
        }
        for (int i=0; i<l2; i++) {
            window.draw(*obstacles[i]);
        }
        window.display();
    }

    return 0;
}