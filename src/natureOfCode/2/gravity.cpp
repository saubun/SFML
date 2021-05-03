#define SFML_NO_DEPRECATED_WARNINGS
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <random.hpp>
#include <algorithm>

using Random = effolkronium::random_static;

unsigned int SCR_WIDTH = 1920;
unsigned int SCR_HEIGHT = 1080;

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

sf::Vector2f getSetMagnitude(sf::Vector2f vec, float n)
{
    return getNormalized(vec) * n;
}

void setMagnitude(sf::Vector2f &vec, float n)
{
    vec = getNormalized(vec) * n;
}

class Attractor
{
public:
    sf::CircleShape entity;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float mass;

    Attractor(float x, float y, float mass)
    {
        this->mass = mass;
        this->entity = sf::CircleShape(sqrtf(this->mass) * 20);
        this->entity.setFillColor(sf::Color::Green);
        this->entity.setPosition(x, y);
        this->velocity = sf::Vector2f(0, 0);
        this->entity.setOrigin(this->entity.getRadius(), this->entity.getRadius());
    }

    // A = F / M (Mass is 1)
    void applyForce(sf::Vector2f force)
    {
        this->acceleration += force / this->mass;
    }

    // Bounce on borders
    void bounce()
    {
        float r = this->entity.getRadius();
        if (this->entity.getPosition().y <= r)
        {
            this->entity.setPosition(this->entity.getPosition().x, r);
            this->velocity.y *= -1.0f;
        }
        if (this->entity.getPosition().y >= SCR_HEIGHT - r)
        {
            this->entity.setPosition(this->entity.getPosition().x, SCR_HEIGHT - r);
            this->velocity.y *= -1.0f;
        }
        if (this->entity.getPosition().x <= r)
        {
            this->entity.setPosition(r, this->entity.getPosition().y);
            this->velocity.x *= -1.0f;
        }
        if (this->entity.getPosition().x >= SCR_WIDTH - r)
        {
            this->entity.setPosition(SCR_WIDTH - r, this->entity.getPosition().y);
            this->velocity.x *= -1.0f;
        }
    }

    // Update position
    void update()
    {
        this->velocity += this->acceleration;
        this->entity.move(this->velocity);
        this->acceleration = sf::Vector2f(0, 0);
    }

    // Apply friction (F (force) = - 1 * Mu (friction coeff.) * N (normal force) * v̂ (direction))
    void friction(Attractor attractor)
    {
        sf::Vector2f displacement = this->entity.getPosition() - attractor.entity.getPosition();
        sf::Vector2f direction = getNormalized(displacement) * -1.0f;
        float mu = 0.1f;
        float normalForce = this->mass;
        sf::Vector2f fric = getSetMagnitude(direction, mu * normalForce);

        this->applyForce(fric);
    }

    // Apply fluid drag ( F (drag force) = -(1/2) * ρ (density of fluid) * ||v||^2 (mag of velocity/speed) * A (surface area) * C (coeff. of drag) * v̂ (direction) )
    void dragForce(Attractor attractor)
    {
        sf::Vector2f displacement = this->entity.getPosition() - attractor.entity.getPosition();
        sf::Vector2f drag = getNormalized(displacement) * -0.5f;
        float c = 0.001f;
        float speed = getMagnitude(this->velocity);
        float surfaceArea = 0.314f * this->entity.getRadius();
        setMagnitude(drag, c * powf(speed, 2.0f) * surfaceArea);

        this->applyForce(drag);
    }

    // Gravitationally attract to another attractor ( F = ((m1 * m2) / ||d||^2) * G )
    void attract(Attractor attractor)
    {
        sf::Vector2f displacement = this->entity.getPosition() - attractor.entity.getPosition();
        float distance = getMagnitude(displacement);
        distance = std::clamp(distance, this->entity.getRadius() * 4.0f, 1000.0f);
        float G = -100.0f;
        float forceMag = ((this->mass * attractor.mass) / powf(distance, 2.0f)) * G;
        sf::Vector2f gravity = getSetMagnitude(displacement, forceMag);
        this->applyForce(gravity);
    }

    // Detect collision with another attractor
    void collide(Attractor attractor)
    {
        sf::Vector2f displacement = this->entity.getPosition() - attractor.entity.getPosition();
        float distance = getMagnitude(displacement);

        if (distance <= this->entity.getRadius() + attractor.entity.getRadius())
        {
            this->velocity += getNormalized(displacement);
            this->friction(attractor);
            this->dragForce(attractor);
        }
    }
};

int main()
{
    // Create loop
    sf::RenderWindow window(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "Ball", sf::Style::Default);

    // Time
    sf::Clock clock;
    sf::Clock deltaClock;

    // FPS
    window.setFramerateLimit(FPS);

    // Attractor
    std::vector<Attractor> attractors;
    for (unsigned int x = 0; x < 3; x++)
    {
        attractors.push_back(
            Attractor((float)Random::get(0, (int)SCR_WIDTH), (float)Random::get(0, (int)SCR_HEIGHT), (float)Random::get(10, 20) / 10) // :3
        );
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

        // For every attractor
        for (int x = 0; x < attractors.size(); x++)
        {
            // Apply gravity
            for (int y = 0; y < attractors.size(); y++)
            {
                if (x != y)
                {
                    attractors.at(x).collide(attractors.at(y));
                    attractors.at(x).attract(attractors.at(y));
                }
            }

            // Draw attractor
            window.draw(attractors.at(x).entity);

            // Border check
            attractors.at(x).bounce();

            // Update forces
            attractors.at(x).update();
        }

        // Swap buffers
        window.display();
    }

    return 0;
}