#include <SFML/Graphics.hpp>
#include <iostream>

// Define the Timer class before it's used
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

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    sf::CircleShape shape(100.f);
    sf::Vector2f circlePos(500,500);
    shape.setPosition(circlePos);
    shape.setFillColor(sf::Color::Green);

    Scoreboard scoreboard;
    Timer countdown(sf::seconds(3)); // 3 second countdown

    sf::Font font;
    if (!font.loadFromFile("Arial.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return -1;
    }

    sf::Text countdownText;
    countdownText.setFont(font);
    countdownText.setCharacterSize(32);
    countdownText.setFillColor(sf::Color::White);
    countdownText.setPosition(window.getSize().x / 2, window.getSize().y / 2);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (!countdown.isFinished()) {
            // Update countdown text and draw it
            int remainingSeconds = static_cast<int>(countdown.getRemainingTime().asSeconds());
            countdownText.setString(std::to_string(remainingSeconds));
            window.clear();
            window.draw(countdownText);
        } else {
            // Game logic goes here
            // ...
            scoreboard.Player1Score++;
            scoreboard.Player2Score++;
            scoreboard.update();
            window.clear();
            scoreboard.draw(window);
        }

        window.draw(shape);
        window.display();
    }

   return 0; 
}