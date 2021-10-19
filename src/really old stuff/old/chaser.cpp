#define SFML_NO_DEPRECATED_WARNINGS
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <random.hpp>

using Random = effolkronium::random_static;

unsigned int SCR_WIDTH = 1024;
unsigned int SCR_HEIGHT = 768;

unsigned int FPS = 60;

int main()
{
    // Create loop
    sf::RenderWindow window(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "<name>", sf::Style::Default);

    // Chasers
    std::vector<sf::CircleShape> chasers;

    // Colors
    std::vector<sf::Color> colors = {sf::Color::Red, sf::Color::Blue, sf::Color::Green, sf::Color::Cyan, sf::Color::Magenta};

    // Time
    sf::Clock clock;
    sf::Clock deltaClock;

    // FPS
    window.setFramerateLimit(FPS);

    // Main Loop
    while (window.isOpen())
    {
        // Time
        float time = clock.getElapsedTime().asSeconds();

        // Calculate deltaTime
        float deltaTime = deltaClock.restart().asSeconds();

        // Poll events on the main window
        sf::Event windowEvent;
        while (window.pollEvent(windowEvent))
        {
            switch (windowEvent.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                // End game
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                    window.close();

                break;
            case sf::Event::MouseButtonPressed:
                break;

            default:
                break;
            }
        }

        // Reset display
        window.clear(sf::Color::Black);

        // Create new chasers (with limit)
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            sf::CircleShape circle(2);
            sf::Vector2f mousePos(
                sf::Mouse::getPosition(window).x + Random::get(-20, 20),
                sf::Mouse::getPosition(window).y + Random::get(-20, 20));
            sf::Color color = colors.at(Random::get(0, (int)colors.size() - 1));
            circle.setFillColor(color);
            circle.setPosition(mousePos);

            if (chasers.size() < 500)
                chasers.push_back(circle);
        }

        // Render circles
        for (unsigned int i = 0; i < chasers.size(); i++)
        {
            // Chaser wacky
            sf::Vector2f randomMove(Random::get(-2, 2), Random::get(-2, 2));
            chasers.at(i).move(randomMove);

            // Collision detection between chasers
            for (unsigned int j = 0; j < chasers.size(); j++)
            {
                float distance = sqrtf(powf(chasers.at(j).getPosition().x - chasers.at(i).getPosition().x, 2) + powf(chasers.at(j).getPosition().y - chasers.at(i).getPosition().y, 2));
                sf::Vector2f displacement = chasers.at(i).getPosition() - chasers.at(j).getPosition();
                if (distance < chasers.at(i).getRadius() + chasers.at(j).getRadius())
                {
                    chasers.at(i).move(displacement);
                }
            }

            // Move towards cursor and circle if near
            sf::Vector2f mousePos(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
            sf::Vector2f displacement = mousePos - chasers.at(i).getPosition();
            float distance = sqrtf(powf(mousePos.y - chasers.at(i).getPosition().x, 2) + powf(mousePos.y - chasers.at(i).getPosition().y, 2));
            chasers.at(i).move(displacement * deltaTime);
            chasers.at(i).move(sin(time) * 2, cos(time) * 2);

            // Draw
            window.draw(chasers.at(i));
        }

        // Swap buffers
        window.display();
    }

    return 0;
}
