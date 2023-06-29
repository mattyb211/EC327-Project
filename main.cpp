
// -I/usr/local/Cellar/sfml/2.5.1_2/include -L/usr/local/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio -lsfml-window

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <sstream>
#include <list>

using namespace std;

class Timer {
    sf::Clock clock;
    sf::Time targetTime;
    bool finished = false;
public:
    Timer(const sf::Time& countdown_time) : targetTime(countdown_time) {}

    void reset() {
        clock.restart();
        finished = false;
    }

    bool isFinished() {
        if (!finished) {
            if (clock.getElapsedTime() >= targetTime) {
                finished = true;
            }
        }
        return finished;
    }

    sf::Time getRemainingTime() {
        if (finished) {
            return sf::Time::Zero;
        }
        sf::Time remaining = targetTime - clock.getElapsedTime();
        return remaining;
    }
};


struct Scoreboard {
    int Player1Score = 0;
    int Player2Score = 0;

    sf::Font font;
    sf::Text Player1Text;
    sf::Text Player2Text;

    Scoreboard() {
        if (!font.loadFromFile("Arial.ttf")) {
            std::cerr << "Failed to load font" << std::endl;
            return;
        }

        Player1Text.setFont(font);
        Player1Text.setCharacterSize(24);
        Player1Text.setFillColor(sf::Color::Red);
        Player1Text.setPosition(10, 10);

        Player2Text.setFont(font);
        Player2Text.setCharacterSize(24);
        Player2Text.setFillColor(sf::Color::Blue);
        Player2Text.setPosition(10, 50);

        update();
    }

    void update() {
        Player1Text.setString("Player1: " + std::to_string(Player1Score));
        Player2Text.setString("Player2: " + std::to_string(Player2Score));
    }

    void draw(sf::RenderWindow &window) {
        window.draw(Player1Text);
        window.draw(Player2Text);
    }
};

// void moveRight(std::vector<sf::Shape*> tankvec, sf::Vector2f tankpos ) {
//     int size = tankvec.size();
//     tankpos.x += 0.25;

//     for (int i=0; i<size; i++) {
//         tankvec.at(i)->move(sf::Vector2f(0.25,0));
//     }
// }

// void moveLeft(std::vector<sf::Shape*> tankvec, sf::Vector2f tankpos ) {
//     int size = tankvec.size();
//     tankpos.x -= 0.25;

//     for (int i=0; i<size; i++) {
//         tankvec.at(i)->move(sf::Vector2f(-0.25,0));
//     }
// }

// void moveUp(std::vector<sf::Shape*> tankvec, sf::Vector2f tankpos ) {
//     int size = tankvec.size();
//     tankpos.y -= 0.25;

//     for (int i=0; i<size; i++) {
//         tankvec.at(i)->move(sf::Vector2f(0,-0.25));
//     }
// }

// void moveUp(std::vector<sf::Shape*> tankvec, sf::Vector2f tankpos ) {
//     int size = tankvec.size();
//     tankpos.y -= 0.25;

//     for (int i=0; i<size; i++) {
//         tankvec.at(i)->move(sf::Vector2f(0,-0.25));
//     }
// }

int main()
{
    const unsigned WINDOW_WIDTH = 2000;
    const unsigned WINDOW_HEIGHT = 1000;
    const float grid = 100;
    const float bulletspeed = 2;

    int countdownValue = 3;
    bool countdownRunning = false;

    sf::RenderWindow countdownWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Countdown");
    sf::Font font;
    if (!font.loadFromFile("Arial.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return -1;
    }
    sf::Text countdownText;
    countdownText.setFont(font);
    countdownText.setCharacterSize(24);
    countdownText.setFillColor(sf::Color::White);
    countdownText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    Timer countdown(sf::seconds(4)); // 4 second countdown
    Timer finalCountdown(sf::seconds(1)); // 1 second final message

    // Countdown loop
    while (countdownWindow.isOpen()) {
        sf::Event event;
        while (countdownWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                countdownWindow.close();
                return 0;  // Close the program if countdown window is closed
            }
        }

        if (!countdown.isFinished()) {
            // Update countdown text and draw it
            int remainingSeconds = static_cast<int>(countdown.getRemainingTime().asSeconds());
            countdownText.setString(std::to_string(remainingSeconds));
        } else {
            if (!finalCountdown.isFinished()) {
                // Show final message
                countdownText.setString("Here we go!");
            } else {
                countdownWindow.close();
                break;  // Break out of the countdown loop
            }
        }

        countdownWindow.clear();
        countdownWindow.draw(countdownText);
        countdownWindow.display();
    }
    sf::RenderWindow window3(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");

    // Make 2 circles (will be tanks)
    


    std::vector<sf::Shape*> tanks;

    std::vector<sf::Shape*> tank1;
    std::vector<sf::Shape*> tank2;

    sf::RectangleShape* tank1body = new sf::RectangleShape(sf::Vector2f(grid,grid));
    sf::Vector2f tank1pos = sf::Vector2f(100,400);
    tank1body->setPosition(tank1pos);
    tank1body->setFillColor(sf::Color::Green);
    tank1.push_back(tank1body);
    sf::RectangleShape* tank1gun = new sf::RectangleShape(sf::Vector2f(10,50));
    tank1gun->setPosition(tank1pos);
    tank1gun->setFillColor(sf::Color::Green);
    tank1.push_back(tank1gun);

    sf::RectangleShape* tank2body = new sf::RectangleShape(sf::Vector2f(grid,grid));
    sf::Vector2f tank2pos = sf::Vector2f(1800,400);
    tank2body->setPosition(tank2pos);
    tank2body->setFillColor(sf::Color::Cyan);
    tank2.push_back(tank2body);
    sf::RectangleShape* tank2gun = new sf::RectangleShape(sf::Vector2f(10,50));
    tank2gun->setPosition(sf::Vector2f(tank2pos.x-50,tank2pos.y+50));
    tank2gun->setFillColor(sf::Color::Cyan);
    tank2gun->rotate(270);
    tank2.push_back(tank2gun);
    


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

    Scoreboard scoreboard;

    // Bullet Shape
    sf::CircleShape bullet1(10);
    bullet1.setFillColor(sf::Color::White);
    sf::Vector2f bullet1pos = sf::Vector2f(tank1pos);
    

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

    
    while (window3.isOpen())
    {
        sf::Event event;
        while (window3.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window3.close();
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
                tank1body->move(sf::Vector2f(-0.25,0));
                tank1gun->move(sf::Vector2f(-0.25,0));
                tank1pos.x -= 0.25;
            } 
        }
        if (rightOpen1) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
                tank1body->move(sf::Vector2f(0.25,0));
                tank1gun->move(sf::Vector2f(0.25,0));
                tank1pos.x += 0.25;
            } 
        }
        if (upOpen1) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
                tank1body->move(sf::Vector2f(0,-0.25));
                tank1gun->move(sf::Vector2f(0,-0.25));
                tank1pos.y -= 0.25;
            } 
        }
        if (downOpen1) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
                tank1body->move(sf::Vector2f(0,0.25));
                tank1gun->move(sf::Vector2f(0,0.25));
                tank1pos.y += 0.25;
            }
        }

        // Tank 2 Movement using Arrow Keys
        if (leftOpen2) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
                tank2body->move(sf::Vector2f(-0.25,0));
                tank2gun->move(sf::Vector2f(-0.25,0));
                tank2pos.x -= 0.25;
            } 
        }
        if (rightOpen2) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
                tank2body->move(sf::Vector2f(0.25,0));
                tank2gun->move(sf::Vector2f(0.25,0));
                tank2pos.x += 0.25;
            } 
        }
        if (upOpen2) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
                tank2body->move(sf::Vector2f(0,-0.25));
                tank2gun->move(sf::Vector2f(0,-0.25));
                tank2pos.y -= 0.25;
            } 
        }
        if (downOpen2) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
                tank2body->move(sf::Vector2f(0,0.25));
                tank2gun->move(sf::Vector2f(0,0.25));
                tank2pos.y += 0.25;
            }
        }

        // Shoot Bullet 1
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
            bullet1pos.x += bulletspeed;
            bullet1.setPosition(bullet1pos);
        }


        sf::Clock countdownClock;
        bool countdownRunning = true;
        bool hereWeGoDisplayed = false;

        sf::Text countdownText;
        countdownText.setFont(font);
        countdownText.setCharacterSize(32);
        countdownText.setFillColor(sf::Color::White);
        countdownText.setPosition(window3.getSize().x / 2, window3.getSize().y / 2);

        if (countdownRunning) {
            sf::Time elapsed = countdownClock.getElapsedTime();

            // Display "Here we go" for the first 2 seconds
            if (elapsed.asSeconds() < 2) {
                countdownText.setString("Here we go!");
                hereWeGoDisplayed = true;
            }
            // Display the countdown from 3 to 1
            else if (elapsed.asSeconds() < 5) {
                if (!hereWeGoDisplayed) {
                    countdownText.setString("3");
                    hereWeGoDisplayed = true;
                }
                else if (elapsed.asSeconds() > 3 && elapsed.asSeconds() < 4) {
                    countdownText.setString("2");
                }
                else if (elapsed.asSeconds() > 4 && elapsed.asSeconds() < 5) {
                    countdownText.setString("1");
                }
            }
            // Stop the countdown and start the game
            else {
                countdownRunning = false;
            }
        }

        window3.clear();
        for (int i=0; i<tank1.size(); i++) {
            window3.draw(*tank1[i]);
            window3.draw(*tank2[i]);
        }
        for (int i=0; i<l2; i++) {
            window3.draw(*obstacles[i]);
        }
        scoreboard.draw(window3);

        //Draw Bullet for Tank 1
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
            bullet1pos = tank1pos;
            bullet1pos.x += bulletspeed;
            bullet1.setPosition(bullet1pos);
            window3.draw(bullet1);
        }
        

        window3.display();


        Timer countdown(sf::seconds(3)); // 3 second countdown

        sf::Font font;
        if (!font.loadFromFile("Arial.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return -1;
        }

        if (!countdown.isFinished()) {
            // Update countdown text and draw it
            int remainingSeconds = static_cast<int>(countdown.getRemainingTime().asSeconds());
            countdownText.setString(std::to_string(remainingSeconds));
            window3.clear();
            window3.draw(countdownText);
        } else {
            // Game logic goes here
            // ...
            scoreboard.Player1Score++;
            scoreboard.Player2Score++;
            scoreboard.update();
            window3.clear();
            scoreboard.draw(window3);
        }
   
    }

    return 0;
}