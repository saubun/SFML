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
    sf::RenderWindow window(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "Random Noise", sf::Style::Default);

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

        int size = 10;
        for (int i = 0; i < SCR_WIDTH; i += size)
        {
            for (int j = 0; j < SCR_HEIGHT; j += size)
            {
                sf::RectangleShape rect(sf::Vector2f(size, size));
                rect.setPosition(i, j);
                rect.setFillColor(sf::Color(255, 255, 255, 255 * Random::get(0, 1) / Random::get(1, 10)));
                window.draw(rect);
            }
        }

        // Swap buffers
        window.display();
    }

    return 0;
}
