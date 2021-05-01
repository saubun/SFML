#define SFML_NO_DEPRECATED_WARNINGS
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
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

sf::Vector2f getSetMagnitude(sf::Vector2f vec, float n)
{
    return getNormalized(vec) * n;
}

void setMagnitude(sf::Vector2f &vec, float n)
{
    vec = getNormalized(vec) * n;
}

class Walker
{
private:
    sf::CircleShape entity;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    sf::Vector2f displacement;
    float mass;

public:
    Walker(float x, float y, float mass)
    {
        this->mass = mass;
        this->entity = sf::CircleShape(sqrtf(this->mass) * 20);
        this->entity.setFillColor(sf::Color::Green);
        this->entity.setPosition(x, y);
        this->velocity = sf::Vector2f(0, 0);
    }

    // A = F / M (Mass is 1)
    void applyForce(sf::Vector2f force)
    {
        this->acceleration += force / this->mass;
    }

    // Apply friction (F (force) = - 1 * Mu (friction coeff.) * N (normal force) * v̂ (direction))
    void friction()
    {
        float distanceToGround = SCR_HEIGHT - (this->entity.getPosition().y + this->entity.getRadius() * 2);
        if (distanceToGround < 1)
        {
            sf::Vector2f direction = getNormalized(this->velocity) * -1.0f;
            float mu = 0.01f;
            float normalForce = this->mass;
            sf::Vector2f fric = getSetMagnitude(direction, mu * normalForce);

            this->applyForce(fric);
        }
    }

    // Apply fluid drag ( F (drag force) = -(1/2) * ρ (density of fluid) * ||v||^2 (mag of velocity/speed) * A (surface area) * C (coeff. of drag) * v̂ (direction) )
    void dragForce()
    {
        sf::Vector2f drag = getNormalized(this->velocity) * -0.5f;
        float c = 0.001f;
        float speed = getMagnitude(this->velocity);
        float surfaceArea = 0.314f * this->entity.getRadius();
        setMagnitude(drag, c * powf(speed, 2.0f) * surfaceArea);

        this->applyForce(drag);
    }

    // Bounce on borders
    void bounce()
    {
        float r = this->entity.getRadius();
        if (this->entity.getPosition().y <= 0)
        {
            this->entity.setPosition(this->entity.getPosition().x, 0);
            this->velocity.y *= -1.0f;
        }
        if (this->entity.getPosition().y >= SCR_HEIGHT - r * 2)
        {
            this->entity.setPosition(this->entity.getPosition().x, SCR_HEIGHT - r * 2);
            this->velocity.y *= -1.0f;
        }
        if (this->entity.getPosition().x <= 0)
        {
            this->entity.setPosition(0, this->entity.getPosition().y);
            this->velocity.x *= -1.0f;
        }
        if (this->entity.getPosition().x >= SCR_WIDTH - r * 2)
        {
            this->entity.setPosition(SCR_WIDTH - r * 2, this->entity.getPosition().y);
            this->velocity.x *= -1.0f;
        }
    }

    void update()
    {
        // Update position
        this->velocity += this->acceleration;
        this->entity.move(this->velocity);
        this->acceleration = sf::Vector2f(0, 0);
    }

    sf::CircleShape getEntity()
    {
        return this->entity;
    }

    float getMass()
    {
        return this->mass;
    }

    sf::Vector2f getVelocity()
    {
        return this->velocity;
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

    // Walker
    std::vector<Walker> walkers;
    for (unsigned int x = 0; x < 10; x++)
    {
        walkers.push_back(
            Walker((float)Random::get(0, (int)SCR_WIDTH), (float)SCR_HEIGHT / 2, (float)Random::get(1, 100) / 10) // :3
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

        // For every walker
        for (int x = 0; x < walkers.size(); x++)
        {

            // Apply gravity
            sf::Vector2f weight(sf::Vector2f(0.0f, 0.5f) * walkers.at(x).getMass());
            walkers.at(x).applyForce(weight);

            // Apply winds
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
                walkers.at(x).applyForce(sf::Vector2f(0, -5.0f));
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
                walkers.at(x).applyForce(sf::Vector2f(-5.0f, 0));
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
                walkers.at(x).applyForce(sf::Vector2f(0, 5.0f));
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
                walkers.at(x).applyForce(sf::Vector2f(5.0f, 0));

            // Update forces
            walkers.at(x).update();

            // Border check
            walkers.at(x).bounce();

            // Drag force & friction
            walkers.at(x).dragForce();
            walkers.at(x).friction();

            // Draw walker
            window.draw(walkers.at(x).getEntity());
        }

        // Swap buffers
        window.display();
    }

    return 0;
}