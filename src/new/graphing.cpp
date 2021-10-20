#define SFML_NO_DEPRECATED_WARNINGS
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <random.hpp>

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

sf::Vector2i vec2fToVec2i(sf::Vector2f vecf)
{
    return sf::Vector2i(vecf.x, vecf.y);
}

sf::Vector2f vec2iToVec2f(sf::Vector2i veci)
{
    return sf::Vector2f(veci.x, veci.y);
}

/* ------------ Drawable Point ------------ */

struct Point
{
    sf::CircleShape shape;

    Point(sf::Vector2f pos, unsigned int size)
    {
        this->shape = sf::CircleShape(size);
        this->shape.setOrigin(sf::Vector2f(size, size));
        this->shape.setPosition(pos);
    };
};

/* ------------ Main Function ------------ */

int main()
{
    // Create loop
    sf::RenderWindow window(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "Basic Graphing", sf::Style::Default);

    // Time
    sf::Clock clock;
    sf::Clock deltaClock;

    // FPS
    window.setFramerateLimit(FPS);

    // List of points
    std::vector<Point> points = {};

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

                // At mouse position sf::Mouse::getPosition(window)
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
                {
                    // Instatiate a new point
                    points.push_back(Point(vec2iToVec2f(sf::Mouse::getPosition(window)), 50));
                }

                break;
            case sf::Event::MouseButtonPressed:
                break;
            default:
                break;
            }
        }

        // Reset display
        window.clear(sf::Color::Black);

        for (auto x : points)
        {
            window.draw(x.shape);
        }

        // Swap buffers
        window.display();
    }

    return 0;
}
