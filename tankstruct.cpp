#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

int main() {
    sf::RenderWindow window1(sf::VideoMode(1000, 1000), "Player 1 Tanks");
    sf::RenderWindow window2(sf::VideoMode(1000, 1000), "Player 2 Tanks");

    float tanksize = 100.f; 

    //edeges corner
    sf::ConvexShape square;
    square.setPointCount(8); 

    //Tank Structure
    float cornerRadius = tanksize * 0.1f; 
    float tankWidth = tanksize * 2.f; 
    float tankHeight = tanksize * 1.5f; 

    square.setPoint(0, sf::Vector2f(cornerRadius, 0.f));
    square.setPoint(1, sf::Vector2f(tankWidth - cornerRadius, 0.f));
    square.setPoint(2, sf::Vector2f(tankWidth, cornerRadius));
    square.setPoint(3, sf::Vector2f(tankWidth, tankHeight - cornerRadius));
    square.setPoint(4, sf::Vector2f(tankWidth - cornerRadius, tankHeight));
    square.setPoint(5, sf::Vector2f(cornerRadius, tankHeight));
    square.setPoint(6, sf::Vector2f(0.f, tankHeight - cornerRadius));
    square.setPoint(7, sf::Vector2f(0.f, cornerRadius));

    sf::Color tankOutlineColorPlayer1 = sf::Color::White;
    sf::Color tankOutlineColorPlayer2 = sf::Color::Black;
    square.setOutlineThickness(tanksize * 0.05f);
    square.setOrigin(tankWidth / 2.f, tankHeight / 2.f); // Set the origin to the center of the tank

    sf::CircleShape circle(tanksize * 0.35f);
    circle.setOutlineThickness(tanksize * 0.05f);
    circle.setOrigin(circle.getRadius(), circle.getRadius());

    sf::RectangleShape gun(sf::Vector2f(tanksize * 1.65f, tanksize * 0.30f));
    gun.setOutlineThickness(tanksize * 0.02f);
    gun.setOrigin(0.f, gun.getSize().y / 2.f); // Set the origin to the center of the gun

    std::vector<sf::Vector2f> tankPositions(8);
    tankPositions[0] = sf::Vector2f(200.f, 200.f);
    tankPositions[1] = sf::Vector2f(400.f, 200.f);
    tankPositions[2] = sf::Vector2f(600.f, 200.f);
    tankPositions[3] = sf::Vector2f(800.f, 200.f);
    tankPositions[4] = sf::Vector2f(200.f, 600.f);
    tankPositions[5] = sf::Vector2f(400.f, 600.f);
    tankPositions[6] = sf::Vector2f(600.f, 600.f);
    tankPositions[7] = sf::Vector2f(800.f, 600.f);
    //Each Tank Color
    std::vector<sf::Color> tankColorsPlayer1(8);
    tankColorsPlayer1[0] = sf::Color::Green;
    tankColorsPlayer1[1] = sf::Color::Red;
    tankColorsPlayer1[2] = sf::Color::Cyan;
    tankColorsPlayer1[3] = sf::Color(0, 0, 139);
    tankColorsPlayer1[4] = sf::Color(255, 105, 180);
    tankColorsPlayer1[5] = sf::Color(148, 0, 211);
    tankColorsPlayer1[6] = sf::Color(255, 165, 0);
    tankColorsPlayer1[7] = sf::Color(255, 247, 153);

    std::vector<sf::Color> tankColorsPlayer2(8);
    tankColorsPlayer2[0] = sf::Color::Red;
    tankColorsPlayer2[1] = sf::Color::Green;
    tankColorsPlayer2[2] = sf::Color::Cyan;
    tankColorsPlayer2[3] = sf::Color(0, 0, 139);
    tankColorsPlayer2[4] = sf::Color(255, 105, 180);
    tankColorsPlayer2[5] = sf::Color(148, 0, 211);
    tankColorsPlayer2[6] = sf::Color(255, 165, 0);
    tankColorsPlayer2[7] = sf::Color(255, 247, 153);

    // Rotate tanks vertically 
    float tankRotation = 90.f;

    std::vector<int> selectedTanksPlayer1;
    std::vector<int> selectedTanksPlayer2;

    while (window1.isOpen() || window2.isOpen()) {
        sf::Event event;
        while (window1.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window1.close();
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            // Check if any tank was clicked
            for (size_t i = 0; i < tankPositions.size(); ++i) {
            sf::FloatRect tankBounds = square.getGlobalBounds();
            if (tankBounds.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
             selectedTanksPlayer1.push_back(i);
            window1.close(); // Close the window after selecting a tank
            break; // No need to check other tanks if one is already selected
            }
            }
        }
        }

        while (window2.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window2.close();
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                // Check if any tank was clicked
            for (size_t i = 0; i < tankPositions.size(); ++i) {
            sf::FloatRect tankBounds = square.getGlobalBounds();
            if (tankBounds.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                selectedTanksPlayer2.push_back(i);
                window2.close(); // Close the window after selecting a tank
                break; // No need to check other tanks if one is already selected
                }
            }
         }
        }

        window1.clear();

        for (size_t i = 0; i < tankPositions.size(); ++i) {
            square.setPosition(tankPositions[i]);
            circle.setPosition(tankPositions[i]);
            gun.setPosition(tankPositions[i]);
             
            // Apply tank rotation
            square.setRotation(tankRotation);
            circle.setRotation(tankRotation);
            gun.setRotation(tankRotation);

            // Set tank color
            square.setFillColor(tankColorsPlayer1[i]);
            circle.setFillColor(tankColorsPlayer1[i]);
            gun.setFillColor(tankColorsPlayer1[i]);

            // Set tank outline color for Player 1 window
            square.setOutlineColor(tankOutlineColorPlayer1);
            circle.setOutlineColor(tankOutlineColorPlayer1);
            gun.setOutlineColor(tankOutlineColorPlayer1);

            window1.draw(square);
            window1.draw(circle);
            window1.draw(gun);
        }

        window1.display();

        window2.clear();

        for (size_t i = 0; i < tankPositions.size(); ++i) {
            square.setPosition(tankPositions[i]);
            circle.setPosition(tankPositions[i]);
            gun.setPosition(tankPositions[i]);

            // Apply tank rotation
            square.setRotation(tankRotation);
            circle.setRotation(tankRotation);
            gun.setRotation(tankRotation);

            // Set tank color
            square.setFillColor(tankColorsPlayer2[i]);
            circle.setFillColor(tankColorsPlayer2[i]);
            gun.setFillColor(tankColorsPlayer2[i]);

            // Set tank outline color for Player 2 window
            square.setOutlineColor(tankOutlineColorPlayer2);
            circle.setOutlineColor(tankOutlineColorPlayer2);
            gun.setOutlineColor(tankOutlineColorPlayer2);

            window2.draw(square);
            window2.draw(circle);
            window2.draw(gun);
        }

        window2.display();
    }

    std::cout << "Player 1 selected tanks: ";
    for (int tank : selectedTanksPlayer1) {
        std::cout << tank << " ";
    }
    std::cout << std::endl;

    std::cout << "Player 2 selected tanks: ";
    for (int tank : selectedTanksPlayer2) {
        std::cout << tank << " ";
    }
    std::cout << std::endl;

    return 0;
}

