/*
 * File: visualizer.h
 * Author: Rick Hayes
 * License: MIT
 * Version: 1.3
 * Date: April 05, 2025
 */
#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <SFML/Graphics.hpp>
#include <string>

class Visualizer {
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text tempText;
public:
    Visualizer() : window(sf::VideoMode(400, 200), "ESDK Visualizer") {
        if (!font.loadFromFile("arial.ttf")) throw std::runtime_error("Failed to load font");
        tempText.setFont(font);
        tempText.setCharacterSize(24);
        tempText.setFillColor(sf::Color::White);
        tempText.setPosition(10, 10);
    }
    void update(float temperature) {
        if (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
            }
            tempText.setString("Temperature: " + std::to_string(temperature) + "°C");
            window.clear();
            window.draw(tempText);
            window.display();
        }
    }
    bool isOpen() const { return window.isOpen(); }
};

#endif // VISUALIZER_H
