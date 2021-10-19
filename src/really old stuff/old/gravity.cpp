#define SFML_NO_DEPRECATED_WARNINGS
#include <iostream>
#include <SFML/Graphics.hpp>
#include <random.hpp>

using Random = effolkronium::random_static;

unsigned int SCR_WIDTH = 1920;
unsigned int SCR_HEIGHT = 1080;

unsigned int FPS = 60;

unsigned int COUNT = 60;

float getMagnitude(sf::Vector2f vec)
{
    float mag = sqrtf(pow(vec.x, 2) + pow(vec.y, 2));
    return mag;
}

sf::Vector2f getNormalized(sf::Vector2f vec)
{
    return vec / getMagnitude(vec);
}

class Walker
{
public:
    sf::CircleShape entity;
    sf::Vector2f velocity;

    Walker(float x, float y)
    {
        this->entity = sf::CircleShape(10);
        this->entity.setPosition(x, y);
        this->velocity = sf::Vector2f(0, 0);
        this->entity.setFillColor(sf::Color::Green);
    }

    void update(Walker walker)
    {
        // Calculate velocity
        sf::Vector2f displacement = walker.entity.getPosition() - this->entity.getPosition();
        sf::Vector2f direction = getNormalized(displacement);
        sf::Vector2f acceleration = getNormalized(displacement) * 0.0001f;
        float distance = getMagnitude(displacement);
        this->velocity += acceleration;

        // Update position
        this->entity.move(this->velocity);
    }
};

int main()
{
    // Create loop
    sf::RenderWindow window(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "Simple Gravity", sf::Style::Default);

    // Time
    sf::Clock clock;
    sf::Clock deltaClock;

    // FPS
    window.setFramerateLimit(FPS);

    // Walker
    std::vector<Walker> walkers;
    for (unsigned int x = 0; x < COUNT; x++)
    {
        Walker walker(Random::get(0, (int)SCR_WIDTH), Random::get(0, (int)SCR_HEIGHT));
        walkers.push_back(walker);
    }

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

                // Reset walkers
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
                {
                    walkers.clear();
                    for (unsigned int x = 0; x < COUNT; x++)
                    {
                        Walker walker(Random::get(0, (int)SCR_WIDTH), Random::get(0, (int)SCR_HEIGHT));
                        walkers.push_back(walker);
                    }
                }

                break;
            case sf::Event::MouseButtonPressed:
                break;
            default:
                break;
            }
        }

        // Clear
        window.clear(sf::Color::White);

        // Draw walkers
        for (unsigned int i = 0; i < walkers.size(); i++)
        {
            for (unsigned int j = 0; j < walkers.size(); j++)
                if (j != i)
                    walkers.at(i).update(walkers.at(j));

            window.draw(walkers.at(i).entity);
        }

        // Swap buffers
        window.display();
    }

    return 0;
}
