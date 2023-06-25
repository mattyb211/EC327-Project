
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

        if (!countdown.isFinished()) {
        // Update countdown text and draw it
        int remainingSeconds = static_cast<int>(countdown.getRemainingTime().asSeconds());
        countdownText.setString(std::to_string(remainingSeconds));
        window.draw(countdownText);
    } else {
        // Game logic goes here
        // ...
        Scoreboard.Player1Score++;
        Scoreboard.Player2Score++;
        Scoreboard.update();
        Scoreboard.draw(window);
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


Timer countdown(sf::seconds(3)); // 3 second countdown
sf::Text countdownText;
countdownText.setFont(font); // Assuming you have a loaded sf::Font named font
countdownText.setCharacterSize(32);
countdownText.setFillColor(sf::Color::White);
countdownText.setPosition(window.getSize().x / 2, window.getSize().y / 2);

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