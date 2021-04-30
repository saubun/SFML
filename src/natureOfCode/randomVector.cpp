#define SFML_NO_DEPRECATED_WARNINGS
#include <iostream>
#include <SFML/Graphics.hpp>
#include <random.hpp>
#include <glm/glm.hpp>

using Random = effolkronium::random_static;

unsigned int SCR_WIDTH = 1024;
unsigned int SCR_HEIGHT = 768;

unsigned int FPS = 60;

int main()
{
    // Create loop
    sf::RenderWindow window(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "Random Vector", sf::Style::Default);

    // Time
    sf::Clock clock;
    sf::Clock deltaClock;

    // FPS
    window.setFramerateLimit(FPS);

    // Vector
    sf::Vertex vec[] = {sf::Vertex(sf::Vector2f(10, 10)), sf::Vertex(sf::Vector2f(0, 0))};

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

        // Center origin
        sf::Transform transform;
        transform.translate(SCR_WIDTH / 2, SCR_HEIGHT / 2);

        // Line end
        glm::vec2 pos = glm::normalize(glm::vec2(Random::get(-100, 100), Random::get(-100, 100)));
        pos *= 100;
        vec[0].position = sf::Vector2f(pos.x, pos.y);

        // Render
        window.draw(vec, 2, sf::Lines, transform);

        // Swap buffers
        window.display();
    }

    return 0;
}
