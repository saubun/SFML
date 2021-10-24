#define SFML_NO_DEPRECATED_WARNINGS
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <random.hpp>

unsigned int SCR_WIDTH = 1024;
unsigned int SCR_HEIGHT = 768;

using Random = effolkronium::random_static;

int main()
{
    // Create loop
    sf::RenderWindow window(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "Snow", sf::Style::Default);

    // Time
    window.setFramerateLimit(60);
    sf::Clock clock;

    // Circle
    std::vector<sf::RectangleShape *> snow;
    for (int i = 0; i < 200; i++)
    {
    }

    // Direction to move in
    int yVal = 1;

    // Main Loop
    while (window.isOpen())
    {
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

            default:
                break;
            }
        }

        // Reset display
        window.clear(sf::Color::Black);

        // New circle every frame
        sf::RectangleShape *rect = new sf::RectangleShape(sf::Vector2f(Random::get(1, 5), Random::get(1, 5)));
        rect->setPosition(Random::get((unsigned int)0, SCR_WIDTH), 0);
        snow.push_back(rect);

        // Render all snow and delete the ones out of bounds
        for (int i = 0; i < snow.size(); i++)
        {
            snow[i]->move(cos(clock.getElapsedTime().asMilliseconds()), Random::get(1, 3));
            if (snow.at(i)->getPosition().y > SCR_HEIGHT)
            {
                delete snow.at(i);
                snow.erase(snow.begin() + i);
            }
            window.draw(*snow.at(i));
        }

        // Swap buffers
        window.display();
    }
    return 0;
}
