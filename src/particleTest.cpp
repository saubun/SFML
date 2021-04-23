#define SFML_NO_DEPRECATED_WARNINGS
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>

unsigned int SCR_WIDTH = 1024;
unsigned int SCR_HEIGHT = 768;

unsigned int FPS = 10;

int main()
{
    // Create loop
    sf::RenderWindow window(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "<name>", sf::Style::Default);

    // List of particles
    std::vector<sf::CircleShape> particles;

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
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                {
                    sf::Vector2f pos(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
                    sf::CircleShape particle(10);
                    particle.setFillColor(sf::Color::Blue);
                    particle.setPosition(pos);
                    particles.push_back(particle);
                }

                break;
            default:
                break;
            }
        }

        // Reset display
        window.clear(sf::Color::Black);

        // Render
        for (unsigned int x = 0; x < particles.size(); x++)
        {
            window.draw(particles.at(x));
        }

        // Swap buffers
        window.display();
    }

    return 0;
}
