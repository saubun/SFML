#define SFML_NO_DEPRECATED_WARNINGS
#include <iostream>
#include <SFML/Graphics.hpp>
#include <random.hpp>

using Random = effolkronium::random_static;

unsigned int SCR_WIDTH = 1024;
unsigned int SCR_HEIGHT = 768;

unsigned int FPS = 60;

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
private:
    sf::CircleShape entity;
    sf::Vector2f position;
    sf::Vector2f mousePos;
    sf::Vector2f velocity;

public:
    Walker(float x, float y)
    {
        this->entity = sf::CircleShape(10);
        this->entity.setPosition(x, y);
        this->mousePos = sf::Vector2f(0, 0);
        this->velocity = sf::Vector2f(0, 0);
    }

    void update()
    {
        // Update var
        this->position = this->entity.getPosition();

        // Calculate velocity
        sf::Vector2f displacement = this->mousePos - this->position;
        sf::Vector2f direction = getNormalized(displacement);
        sf::Vector2f acceleration = getNormalized(displacement) * 0.1f;
        this->velocity += acceleration;

        // Update position
        this->entity.move(this->velocity);
    }

    sf::CircleShape getEntity()
    {
        return this->entity;
    }

    void setMousePos(sf::Vector2f mousePos)
    {
        this->mousePos = mousePos;
    }
};

int main()
{
    // Create loop
    sf::RenderWindow window(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "Chaser Walker", sf::Style::Default);

    // Time
    sf::Clock clock;
    sf::Clock deltaClock;

    // FPS
    window.setFramerateLimit(FPS);

    // Walker
    Walker walker(SCR_WIDTH / 2, SCR_HEIGHT / 2);
    window.setMouseCursorVisible(false);

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

        // Draw walker
        walker.setMousePos(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
        walker.update();
        window.draw(walker.getEntity());

        // Draw cursor
        sf::CircleShape cursor(10);
        cursor.setPosition(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
        window.draw(cursor);

        // Swap buffers
        window.display();
    }

    return 0;
}
