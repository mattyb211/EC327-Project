#include <SFML/Graphics.hpp>
#include <iostream>

struct Scoreboard {
    int redScore = 0;
    int blueScore = 0;

    sf::Font font;
    sf::Text redScoreText;
    sf::Text blueScoreText;

    Scoreboard() {
        if (!font.loadFromFile("Arial.ttf")) {  // Or any other font
            std::cout << "Could not load font" << std::endl;
            return;
        }

        redScoreText.setFont(font);
        redScoreText.setCharacterSize(24);
        redScoreText.setFillColor(sf::Color::Red);
        redScoreText.setPosition(10, 10);

        blueScoreText.setFont(font);
        blueScoreText.setCharacterSize(24);
        blueScoreText.setFillColor(sf::Color::Blue);
        blueScoreText.setPosition(10, 50);
    }

    void update() {
        redScoreText.setString("Red: " + std::to_string(redScore));
        blueScoreText.setString("Blue: " + std::to_string(blueScore));
    }

    void draw(sf::RenderWindow &window) {
        window.draw(redScoreText);
        window.draw(blueScoreText);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tank Game");

    Scoreboard scoreboard; // Creating an instance of Scoreboard

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        scoreboard.update();
        window.clear();
        scoreboard.draw(window);
        window.display();
    }

    return 0;
}
