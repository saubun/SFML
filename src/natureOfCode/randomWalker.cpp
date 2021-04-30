#define SFML_NO_DEPRECATED_WARNINGS
#include <iostream>
#include <SFML/Graphics.hpp>
#include <random.hpp>

using Random = effolkronium::random_static;

unsigned int SCR_WIDTH = 1024;
unsigned int SCR_HEIGHT = 768;

unsigned int FPS = 60;

class Walker
{
private:
    sf::RectangleShape entity;
    sf::Vector2f position;
    sf::Vector2f velocity;

public:
    Walker(float x, float y)
    {
        this->entity = sf::RectangleShape(sf::Vector2f(5, 5));
        this->entity.setPosition(x, y);
    }

    void update()
    {
        this->position = this->entity.getPosition();
        this->velocity = sf::Vector2f(Random::get(-1, 1), Random::get(-1, 1));
        this->entity.move(this->velocity);
    }

    sf::RectangleShape getEntity()
    {
        return this->entity;
    }
};

int main()
{
    // Create loop
    sf::RenderWindow window(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "Random Walk", sf::Style::Default);

    // Time
    sf::Clock clock;
    sf::Clock deltaClock;

    // FPS
    window.setFramerateLimit(FPS);

    // Walker
    Walker walker(SCR_WIDTH / 2, SCR_HEIGHT / 2);

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

        // Clear
        window.clear(sf::Color::Black);

        // Draw
        walker.update();
        window.draw(walker.getEntity());

        // Swap buffers
        window.display();
    }

    return 0;
}
