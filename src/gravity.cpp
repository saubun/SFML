#define SFML_NO_DEPRECATED_WARNINGS
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <glm/glm.hpp>
#include <vector>
#include <stdlib.h>

unsigned int SCR_WIDTH = 1024;
unsigned int SCR_HEIGHT = 768;

unsigned int FPS = 60;

float CIRCLE_RADIUS = 10.0f;

int main()
{
    // Create loop
    sf::RenderWindow window(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "SFML", sf::Style::Default);

    // Vector of particles
    std::vector<sf::CircleShape> particles = {};

    // Time
    sf::Clock clock;
    sf::Clock deltaClock;

    // Vars
    glm::vec2 velocity(0, 0);
    glm::vec2 oldVelocity(0, 0);

    // Main Loop
    while (window.isOpen())
    {
        // Time
        float time = clock.getElapsedTime().asSeconds();

        // Calculate deltaTime
        float deltaTime = deltaClock.restart().asSeconds();

        // FPS
        window.setFramerateLimit(FPS);

        // Poll events on the main window
        sf::Event windowEvent;
        while (window.pollEvent(windowEvent))
        {
            switch (windowEvent.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                std::cout << "New Size: (" << windowEvent.size.width << ", " << windowEvent.size.height << ")\n";
                break;
            default:
                break;
            }
        }

        // Quit
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            window.close();

        // Reset display
        window.clear(sf::Color(129, 161, 193, 255));

        // Place new particles
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            sf::Vector2f pos(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
            sf::CircleShape circle(CIRCLE_RADIUS);
            circle.setPosition(pos);
            circle.setFillColor(sf::Color::Blue);
            particles.push_back(circle);
        }

        // Render all particles
        for (unsigned int x = 0; x < particles.size(); x++)
            window.draw(particles[x]);

        // Swap buffers
        window.display();
    }

    return 0;
}
