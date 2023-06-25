
// -I/usr/local/Cellar/sfml/2.5.1_2/include -L/usr/local/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio -lsfml-window

#include <SFML/Graphics.hpp>
#include <vector>

int main()
{
    const unsigned WINDOW_WIDTH = 2000;
    const unsigned WINDOW_HEIGHT = 1000;
    const float grid = 100;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");

    // Make 2 circles (will be tanks)
    std::vector<sf::Shape*> tanks;

    sf::RectangleShape* tank1 = new sf::RectangleShape(sf::Vector2f(grid,grid));
    sf::Vector2f tank1pos = sf::Vector2f(100,400);
    tank1->setPosition(tank1pos);
    tank1->setFillColor(sf::Color::Green);
    tanks.push_back(tank1);

    sf::RectangleShape* tank2 = new sf::RectangleShape(sf::Vector2f(grid,grid));
    sf::Vector2f tank2pos = sf::Vector2f(1800,400);
    tank2->setPosition(tank2pos);
    tank2->setFillColor(sf::Color::Cyan);
    tanks.push_back(tank2);

    // Make Obstacles
    std::vector<sf::Shape*> obstacles;

    sf::RectangleShape* rect1 = new sf::RectangleShape(sf::Vector2f(grid, 4*grid));
    sf::Vector2f rect1pos = sf::Vector2f(300,300);
    rect1->setPosition(rect1pos);
    obstacles.push_back(rect1);

    sf::RectangleShape* rect2 = new sf::RectangleShape(sf::Vector2f(2*grid, grid));
    sf::Vector2f rect2pos = sf::Vector2f(900,200);
    rect2->setPosition(rect2pos);
    obstacles.push_back(rect2);

    sf::RectangleShape* rect3 = new sf::RectangleShape(sf::Vector2f(2*grid, grid));
    sf::Vector2f rect3pos = sf::Vector2f(900,700);
    rect3->setPosition(rect3pos);
    obstacles.push_back(rect3);

    sf::RectangleShape* rect4 = new sf::RectangleShape(sf::Vector2f(grid, 4*grid));
    sf::Vector2f rect4pos = sf::Vector2f(1600,300);
    rect4->setPosition(rect4pos);
    obstacles.push_back(rect4);

    sf::Texture brickwall;
    brickwall.loadFromFile("brickwall.jpeg");
    
    int l1 = tanks.size();
    int l2 = obstacles.size();

    for (int i=0; i<l2; i++) {
        obstacles[i]->setTexture(&brickwall);
    }

    // Create booleans for movement conditions
    //bool countdown = false;
    bool touchingOpp = false;
    bool rightOpen1 = true;
    bool leftOpen1 = true;
    bool upOpen1 = true;
    bool downOpen1 = true;
    bool rightOpen2 = true;
    bool leftOpen2 = true;
    bool upOpen2 = true;
    bool downOpen2 = true;
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Check if Tank 1 is allowed to move
        if ( !(tank1pos.x >= 0) ) {
            leftOpen1 = false;
        } else {
            leftOpen1 = true;
        }
        if ( !(tank1pos.x <= WINDOW_WIDTH - grid) ) {
            rightOpen1 = false;
        } else {
            rightOpen1 = true;
        }
        if ( !(tank1pos.y >= 0) ) {
            upOpen1 = false;
        } else {
            upOpen1 = true;
        }
        if ( !(tank1pos.y <= WINDOW_HEIGHT - grid) ) {
            downOpen1 = false;
        } else {
            downOpen1 = true;
        }

        // Check if Tank 2 is allowed to move
        if ( !(tank2pos.x >= 0) ) {
            leftOpen2 = false;
        } else {
            leftOpen2 = true;
        }
        if ( !(tank2pos.x <= WINDOW_WIDTH - grid) ) {
            rightOpen2 = false;
        } else {
            rightOpen2 = true;
        }
        if ( !(tank2pos.y >= 0) ) {
            upOpen2 = false;
        } else {
            upOpen2 = true;
        }
        if ( !(tank2pos.y <= WINDOW_HEIGHT - grid) ) {
            downOpen2 = false;
        } else {
            downOpen2 = true;
        }

        // Tank 1 Movement using WASD
        if (leftOpen1) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
                tank1->move(sf::Vector2f(-0.25,0));
                tank1pos.x -= 0.25;
            } 
        }
        if (rightOpen1) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
                tank1->move(sf::Vector2f(0.25,0));
                tank1pos.x += 0.25;
            } 
        }
        if (upOpen1) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
                tank1->move(sf::Vector2f(0,-0.25));
                tank1pos.y -= 0.25;
            } 
        }
        if (downOpen1) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
                tank1->move(sf::Vector2f(0,0.25));
                tank1pos.y += 0.25;
            }
        }

        // Tank 2 Movement using Arrow Keys
        if (leftOpen2) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
                tank2->move(sf::Vector2f(-0.25,0));
                tank2pos.x -= 0.25;
            } 
        }
        if (rightOpen2) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
                tank2->move(sf::Vector2f(0.25,0));
                tank2pos.x += 0.25;
            } 
        }
        if (upOpen2) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
                tank2->move(sf::Vector2f(0,-0.25));
                tank2pos.y -= 0.25;
            } 
        }
        if (downOpen2) {
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