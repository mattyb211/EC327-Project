#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

bool showConfirmationDialog(const std::string& color) {
    std::string choice;
    std::cout << "Would you like to pick " << color << "? (Yes/No): ";
    std::cin >> choice;
    return (choice == "Yes" or choice == "yes" or choice == "Y" or choice == "y");
}

std::pair<std::string, std::string> selectColors() {
    // Create the SFML windows
    sf::RenderWindow window1(sf::VideoMode(400, 300), "Player 1 Color");
    sf::RenderWindow window2(sf::VideoMode(400, 300), "Player 2 Color");
    bool window2Visible = false;

    // Define the available colors
    std::map<std::string, sf::Color> colorOptions;
    colorOptions.insert(std::make_pair("Green", sf::Color::Green));
    colorOptions.insert(std::make_pair("Red", sf::Color::Red));
    colorOptions.insert(std::make_pair("Cyan", sf::Color::Cyan));
    colorOptions.insert(std::make_pair("Blue", sf::Color(0, 0, 139)));
    colorOptions.insert(std::make_pair("Pink", sf::Color(255, 105, 180)));
    colorOptions.insert(std::make_pair("Purple", sf::Color(148, 0, 211)));
    colorOptions.insert(std::make_pair("Orange", sf::Color(255, 165, 0)));
    colorOptions.insert(std::make_pair("Yellow", sf::Color(255, 247, 153)));

    //Color Grid
    const int gridR = 2;
    const int gridC = 4;
    const float rectdim = 80.0f;
    const float padding = 20.0f;

    // Calculate grid dimensions and initial position
    const float gridWidth = gridC * (rectdim + padding) - padding;
    const float gridHeight = gridR * (rectdim + padding) - padding;
    const sf::Vector2f initialPosition((window1.getSize().x - gridWidth) / 2, (window1.getSize().y - gridHeight) / 2);
    
    std::string selectedColor1, selectedColor2;

    while (window1.isOpen() or window2.isOpen()) {
     sf::Event event;
    while (window1.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
                window1.close();
                window2.close();
    } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        //Mouse Position
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window1);
        // Check if the mouse is inside any color rectangle
        for (const auto& colorOption : colorOptions) {
        sf::RectangleShape colorRect(sf::Vector2f(rectdim, rectdim));
        colorRect.setFillColor(colorOption.second);

        // Calculate the position of the color rectangle
         int index = std::distance(colorOptions.begin(), colorOptions.find(colorOption.first));
        int row = index / gridC;
        int column = index % gridC;
        sf::Vector2f rectPosition = initialPosition + sf::Vector2f(column * (rectdim + padding), row * (rectdim + padding));
        colorRect.setPosition(rectPosition);

        // If the mouse is inside the rectangle, set the color of tank for Player 1
        if (colorRect.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
        selectedColor1 = colorOption.first;
        bool confirmSelection = showConfirmationDialog(selectedColor1);
        if (confirmSelection) {
        window1.close();
        window2Visible = true;
        }
        }
        }
        }
        }

    while (window2.isOpen() and window2Visible) {
    sf::Event event;
    while (window2.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
        window1.close();
        window2.close();
        } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        // Mouse position
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window2);
        // Check if the mouse is inside any color rectangle
        for (const auto& colorOption : colorOptions) {
            sf::RectangleShape colorRect(sf::Vector2f(rectdim, rectdim));
            colorRect.setFillColor(colorOption.second);
            // Calculate the position of the color rectangle
            int index = std::distance(colorOptions.begin(), colorOptions.find(colorOption.first));
            int row = index / gridC;
            int column = index % gridC;
            sf::Vector2f rectPosition = initialPosition + sf::Vector2f(column * (rectdim + padding), row * (rectdim + padding));
            colorRect.setPosition(rectPosition);
            // If the mouse is inside the rectangle, set the color of tank for Player 2
            if (colorRect.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
                selectedColor2 = colorOption.first;
                bool confirmSelection = showConfirmationDialog(selectedColor2);
                   if (confirmSelection) {
                        window2.close();
                        }
                         }
                    }
                }
            }
            window2.clear(sf::Color::White);
            // Draw the color rectangles for Player 2
            for (const auto& colorOption : colorOptions) {
                sf::RectangleShape colorRect(sf::Vector2f(rectdim, rectdim));
                colorRect.setFillColor(colorOption.second);

                // Calculate the position of the color rectangle
                int index = std::distance(colorOptions.begin(), colorOptions.find(colorOption.first));
                int row = index / gridC;
                int column = index % gridC;
                sf::Vector2f rectPosition = initialPosition + sf::Vector2f(column * (rectdim + padding), row * (rectdim + padding));

                colorRect.setPosition(rectPosition);
                window2.draw(colorRect);
            }

            window2.display();
        }

        window1.clear(sf::Color::White);

        // Draw the color rectangles for Player 1
        for (const auto& colorOption : colorOptions) {
            sf::RectangleShape colorRect(sf::Vector2f(rectdim, rectdim));
            colorRect.setFillColor(colorOption.second);

            // Calculate the position of the color rectangle
            int index = std::distance(colorOptions.begin(), colorOptions.find(colorOption.first));
            int row = index / gridC;
            int column = index % gridC;
            sf::Vector2f rectPosition = initialPosition + sf::Vector2f(column * (rectdim + padding), row * (rectdim + padding));

            colorRect.setPosition(rectPosition);
            window1.draw(colorRect);
        }

        window1.display();
    }

    return std::make_pair(selectedColor1, selectedColor2);
}

int main() {
    std::pair<std::string, std::string> selectedColors = selectColors();

    std::cout << "Player 1 selected color: " << selectedColors.first << std::endl;
    std::cout << "Player 2 selected color: " << selectedColors.second << std::endl;

    return 0;
}
