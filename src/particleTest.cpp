#define SFML_NO_DEPRECATED_WARNINGS
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <random.hpp>

unsigned int SCR_WIDTH = 1024;
unsigned int SCR_HEIGHT = 768;

unsigned int FPS = 60;

using Random = effolkronium::random_static;

int main()
{
    // Create loop
    sf::RenderWindow window(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "<name>", sf::Style::Default);

    // List of particles
    std::vector<sf::CircleShape> particles = {};

    // Current color of particle creation
    sf::Color particleColor = sf::Color::Red;

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

                // Change to slow particle
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
                    particleColor = sf::Color::Red;

                // Change to excited particle
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
                    particleColor = sf::Color::Blue;

                // Change to SPEED particle
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
                    particleColor = sf::Color::Green;

                break;
            case sf::Event::MouseButtonPressed:

                break;
            default:
                break;
            }
        }

        // Reset display
        window.clear(sf::Color::Black);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            unsigned int size = 2;
            sf::Vector2f pos(sf::Mouse::getPosition(window).x - size, sf::Mouse::getPosition(window).y - size);
            sf::CircleShape particle(size);
            particle.setFillColor(particleColor);
            particle.setPosition(pos);
            particles.push_back(particle);
        }

        // For every particle
        for (unsigned int x = 0; x < particles.size(); x++)
        {
            // Draw
            window.draw(particles.at(x));

            // Determine particle behavior type
            enum BEHAVIOR_TYPES
            {
                EXCITED,
                SLOW,
                SPEED
            };
            int behavior;
            sf::Color color = particles.at(x).getFillColor();
            if (color == sf::Color::Blue)
                behavior = EXCITED;
            else if (color == sf::Color::Red)
                behavior = SLOW;
            else if (color == sf::Color::Green)
                behavior = SPEED;

            // Logic for particle behavior
            if (behavior == EXCITED)
            {
                // Choose random direction
                float num1 = Random::get(-100.0f, 100.0f);
                float num2 = Random::get(-100.0f, 100.0f);

                // Move
                particles.at(x).move(num1 * deltaTime, num2 * deltaTime);
            }
            else if (behavior == SLOW)
            {
                // Choose random direction
                float num1 = Random::get(-10.0f, 10.0f);
                float num2 = Random::get(-10.0f, 10.0f);

                // Move
                particles.at(x).move(num1 * deltaTime, num2 * deltaTime);
            }
            else if (behavior == SPEED)
            {
                // Choose random direction
                float num1 = Random::get(-1000.0f, 1000.0f);
                float num2 = Random::get(-1000.0f, 1000.0f);

                // Move
                particles.at(x).move(num1 * deltaTime, num2 * deltaTime);
            }

            // Particle attraction (stay away at a certain distance)
            for (unsigned int y = 0; y < particles.size(); y++)
            {
                // Calculate attraction
                sf::Vector2f displacement = particles.at(x).getPosition() - particles.at(y).getPosition();

                // Circular collision
            }
        }

        // Swap buffers
        window.display();
    }

    return 0;
}