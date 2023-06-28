#include <SFML/Graphics.hpp>
#include <iostream>

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
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tank Game");

    Scoreboard scoreboard; 

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // For demonstration, incrementing scores every frame
        scoreboard.Player1Score++;
        scoreboard.Player2Score++;

        scoreboard.update();
        window.clear();
        scoreboard.draw(window);
        window.display();
    }

    return 0;
}
