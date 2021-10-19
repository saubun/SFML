#define SFML_NO_DEPRECATED_WARNINGS
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <random.hpp>

#define PI 3.141592654

using Random = effolkronium::random_static;

unsigned int SCR_WIDTH = 1920;
unsigned int SCR_HEIGHT = 1080;

unsigned int FPS = 30;

/* ------------ Vector moditioncations ------------ */

float getMagnitude(sf::Vector2f vec)
{
    return sqrtf(pow(vec.x, 2) + pow(vec.y, 2));
}

sf::Vector2f getNormalized(sf::Vector2f vec)
{
    return vec / getMagnitude(vec);
}

sf::Vector2f getSetMagnitude(sf::Vector2f vec, float n)
{
    return getNormalized(vec) * n;
}

void setMagnitude(sf::Vector2f &vec, float n)
{
    vec = getNormalized(vec) * n;
}

/* ------------ Math ------------ */

float degreesToRadians(float degrees)
{
    return degrees * PI / 180.0f;
}

float radiansToDegrees(float radians)
{
    return radians * 180.0f / PI;
}

float getHeading(sf::Vector2f d)
{
    float h = atan2(d.y, d.x);
    return h;
}

/* ------------ Main Function ------------ */

int main()
{
    // Create loop
    sf::RenderWindow window(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "Rotation", sf::Style::Default);

    // Time
    sf::Clock clock;
    sf::Clock deltaClock;

    // FPS
    window.setFramerateLimit(FPS);

    // Rect
    sf::RectangleShape rect(sf::Vector2f(400, 50));
    rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2);
    rect.setPosition(SCR_WIDTH / 2, SCR_HEIGHT / 2);

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

        // Ok
        sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
        rect.setRotation(radiansToDegrees(getHeading(rect.getPosition() - mousePos)));

        // Draw
        window.draw(rect);

        // Swap buffers
        window.display();
    }

    return 0;
}
