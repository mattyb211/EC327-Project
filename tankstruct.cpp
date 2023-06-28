#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

int main() {
    sf::RenderWindow window1(sf::VideoMode(1000, 1000), "Player 1 Tanks");
    sf::RenderWindow window2(sf::VideoMode(1000, 1000), "Player 2 Tanks");

    float tanksize = 100.f; // Adjust this value as needed

    // Increase the point count to create rounded corners
    sf::ConvexShape square;
    square.setPointCount(8); // Increase the point count to achieve smoother corners

    // Set the positions of the points to create a rounded square
    float cornerRadius = tanksize * 0.1f; // Adjust the corner radius as desired
    float tankWidth = tanksize * 2.f; // Adjust the tank width as desired
    float tankHeight = tanksize * 1.5f; // Adjust the tank height as desired

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
    tankPositions[0] = sf::Vector2f(200.f, 100.f);
    tankPositions[1] = sf::Vector2f(400.f, 100.f);
    tankPositions[2] = sf::Vector2f(600.f, 100.f);
    tankPositions[3] = sf::Vector2f(800.f, 100.f);
    tankPositions[4] = sf::Vector2f(200.f, 400.f);
    tankPositions[5] = sf::Vector2f(400.f, 400.f);
    tankPositions[6] = sf::Vector2f(600.f, 400.f);
    tankPositions[7] = sf::Vector2f(800.f, 400.f);

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

    float tankRotation = 90.f; // Rotate tanks vertically
    float rotationSpeed = 2.f; // Adjust the rotation speed as desired

    std::vector<int> selectedTanksPlayer1;
    std::vector<int> selectedTanksPlayer2;

    sf::Color selectedTankColorPlayer1;
    sf::Color selectedTankColorPlayer2;

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
                        selectedTankColorPlayer1 = tankColorsPlayer1[i];
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
                        selectedTankColorPlayer2 = tankColorsPlayer2[i];

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
            if (std::find(selectedTanksPlayer1.begin(), selectedTanksPlayer1.end(), i) != selectedTanksPlayer1.end()) {
                square.setFillColor(selectedTankColorPlayer1);
                circle.setFillColor(selectedTankColorPlayer1);
                gun.setFillColor(selectedTankColorPlayer1);
            } else {
                square.setFillColor(tankColorsPlayer1[i]);
                circle.setFillColor(tankColorsPlayer1[i]);
                gun.setFillColor(tankColorsPlayer1[i]);
            }

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
            if (std::find(selectedTanksPlayer2.begin(), selectedTanksPlayer2.end(), i) != selectedTanksPlayer2.end()) {
                square.setFillColor(selectedTankColorPlayer2);
                circle.setFillColor(selectedTankColorPlayer2);
                gun.setFillColor(selectedTankColorPlayer2);
            } else {
                square.setFillColor(tankColorsPlayer2[i]);
                circle.setFillColor(tankColorsPlayer2[i]);
                gun.setFillColor(tankColorsPlayer2[i]);
            }

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

    // Prompt Player 1 to choose a color
    std::cout << "Player 1, select a color (1-8): ";
    int player1Choice;
    std::cin >> player1Choice;
    sf::Color player1Color = tankColorsPlayer1[player1Choice - 1];

    // Prompt Player 2 to choose a color
    std::cout << "Player 2, select a color (1-8): ";
    int player2Choice;
    std::cin >> player2Choice;
    sf::Color player2Color = tankColorsPlayer2[player2Choice - 1];

    return 0;
}

