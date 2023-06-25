#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <string>

int main() {
    sf::RenderWindow window1(sf::VideoMode(800, 600), "Player 1");
    sf::RenderWindow window2(sf::VideoMode(800, 600), "Player 2");

    float cornerRadius = 20.f;
    float tankWidth = 200.f;
    float tankHeight = 200.f;
    float circleRadius = 50.f;

    // Increase the point count to create rounded corners
    sf::ConvexShape square1;
    square1.setPointCount(8);

    sf::ConvexShape square2;
    square2.setPointCount(8);

    // Set the positions of the points to create a rounded square for P1,P2
    square1.setPoint(0, sf::Vector2f(cornerRadius, 0.f));
    square1.setPoint(1, sf::Vector2f(tankWidth - cornerRadius, 0.f));
    square1.setPoint(2, sf::Vector2f(tankWidth, cornerRadius));
    square1.setPoint(3, sf::Vector2f(tankWidth, tankHeight - cornerRadius));
    square1.setPoint(4, sf::Vector2f(tankWidth - cornerRadius, tankHeight));
    square1.setPoint(5, sf::Vector2f(cornerRadius, tankHeight));
    square1.setPoint(6, sf::Vector2f(0.f, tankHeight - cornerRadius));
    square1.setPoint(7, sf::Vector2f(0.f, cornerRadius));
    ////////////////////////////////////////////////////////////////////////
    square2.setPoint(0, sf::Vector2f(cornerRadius, 0.f));
    square2.setPoint(1, sf::Vector2f(tankWidth - cornerRadius, 0.f));
    square2.setPoint(2, sf::Vector2f(tankWidth, cornerRadius));
    square2.setPoint(3, sf::Vector2f(tankWidth, tankHeight - cornerRadius));
    square2.setPoint(4, sf::Vector2f(tankWidth - cornerRadius, tankHeight));
    square2.setPoint(5, sf::Vector2f(cornerRadius, tankHeight));
    square2.setPoint(6, sf::Vector2f(0.f, tankHeight - cornerRadius));
    square2.setPoint(7, sf::Vector2f(0.f, cornerRadius));

    // Tank Color
    std::map<std::string, sf::Color> colorOptions;
    colorOptions.insert(std::make_pair("red", sf::Color::Red));
    colorOptions.insert(std::make_pair("blue", sf::Color::Blue));
    colorOptions.insert(std::make_pair("green", sf::Color::Green));
    colorOptions.insert(std::make_pair("purple", sf::Color(128, 0, 128)));
    colorOptions.insert(std::make_pair("pink", sf::Color(255, 105, 180)));
    colorOptions.insert(std::make_pair("yellow", sf::Color::Yellow));
    colorOptions.insert(std::make_pair("rainbow", sf::Color::Magenta));
    colorOptions.insert(std::make_pair("chrome", sf::Color(100, 149, 237)));

    std::string selectedColor1, selectedColor2;
    std::cout << "Available colors: red, blue, green, purple, pink, yellow, rainbow, chrome\n";

    std::cout << "Enter the color of tank for Player 1: ";
    std::cin >> selectedColor1;
    sf::Color squareColor1 = colorOptions[selectedColor1];
    sf::Color outlineColor1 = sf::Color::White;
    square1.setFillColor(squareColor1);
    square1.setOutlineThickness(5.f);
    square1.setOutlineColor(outlineColor1);

    std::cout << "Enter the color of tank for Player 2: ";
    std::cin >> selectedColor2;
    sf::Color squareColor2 = colorOptions[selectedColor2];
    sf::Color outlineColor2 = sf::Color::Black;
    square2.setFillColor(squareColor2);
    square2.setOutlineThickness(5.f);
    square2.setOutlineColor(outlineColor2);

    sf::CircleShape circle1(circleRadius);
    circle1.setFillColor(outlineColor1);
    circle1.setOutlineThickness(5.f);
    circle1.setOutlineColor(outlineColor1);
    circle1.setOrigin(circleRadius, circleRadius);

    sf::CircleShape circle2(circleRadius);
    circle2.setFillColor(outlineColor2);
    circle2.setOutlineThickness(5.f);
    circle2.setOutlineColor(outlineColor2);
    circle2.setOrigin(circleRadius, circleRadius);

    sf::RectangleShape gun1(sf::Vector2f(175.f, 30.f));
    gun1.setFillColor(squareColor1);
    gun1.setOutlineThickness(2.f);
    gun1.setOutlineColor(outlineColor1);
    gun1.setOrigin(0.f, 15.f);

    sf::RectangleShape gun2(sf::Vector2f(175.f, 30.f));
    gun2.setFillColor(squareColor2);
    gun2.setOutlineThickness(2.f);
    gun2.setOutlineColor(outlineColor2);
    gun2.setOrigin(0.f, 15.f);

//
    while (window1.isOpen() and window2.isOpen()) {
        sf::Event event;
        while (window1.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window1.close();
        }

        while (window2.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window2.close();
        }

        window1.clear();
        window2.clear();

        if (window1.isOpen()) {
            float P1X = window1.getSize().x / 4.f;
            float P1Y = window1.getSize().y / 2.f;
            circle1.setPosition(P1X, P1Y);
            square1.setPosition(P1X - tankWidth / 2.f, P1Y - tankHeight / 2.f);
            gun1.setPosition(P1X, P1Y);
            window1.draw(square1);
            window1.draw(circle1);
            window1.draw(gun1);
            window1.display();
        }

        if (window2.isOpen()) {
            float P2X = window2.getSize().x * 3.f / 4.f;
            float P2Y = window2.getSize().y / 2.f;
            circle2.setPosition(P2X, P2Y);
            square2.setPosition(P2X - tankWidth / 2.f, P2Y - tankHeight / 2.f);
            gun2.setPosition(P2X, P2Y);
            window2.draw(square2);
            window2.draw(circle2);
            window2.draw(gun2);
            window2.display();
        }
    }

    return 0;
}
