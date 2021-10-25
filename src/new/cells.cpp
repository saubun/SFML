#define SFML_NO_DEPRECATED_WARNINGS
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <random.hpp>

using Random = effolkronium::random_static;

unsigned int SCR_WIDTH = 1920;
unsigned int SCR_HEIGHT = 1080;

unsigned int FPS = 60;

unsigned int initialSize = 50;

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

float distance(sf::Vector2f vec1, sf::Vector2f vec2)
{
    return sqrtf(pow(vec2.x - vec1.x, 2) + pow(vec2.y - vec1.y, 2));
}

// Cell Object
struct Cell
{
    unsigned int radius;
    sf::CircleShape self;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float mass;

    Cell(unsigned int radius, sf::Vector2f pos)
    {
        this->radius = radius;
        this->mass = this->radius * 2;
        this->self = sf::CircleShape(this->radius);
        this->self.setPosition(pos);
        this->self.setOrigin(this->radius, this->radius);
        this->velocity = sf::Vector2f(0, 0);
    }

    // Update any values every frame
    void update()
    {
        // Update position
        this->velocity += this->acceleration;    // Add aceleration to velocity
        this->self.move(this->velocity);         // Move by current velocity
        this->acceleration = sf::Vector2f(0, 0); // Reset acceleration

        // Move randomly
        sf::Vector2f vel = sf::Vector2f(Random::get(-5, 5), Random::get(-5, 5));
        this->applyForce(vel);

        // Make sure velocity doesnt go crazy (figure out how to do this)
        // if (getMagnitude(this->velocity) > 10)
        //     this->applyForce(this->velocity * -0.8f);
    }

    // Apply any force to be added to the current acceleration
    void applyForce(sf::Vector2f force)
    {
        this->acceleration += force / this->mass;
    }

    // Checks if mouse position is inside of cell
    bool isClicked(sf::Vector2f mousePos)
    {
        if (distance(this->self.getPosition(), mousePos) <= this->radius)
            return true;
        else
            return false;
    }

    // Bounce on borders
    void bounce()
    {
        float r = this->self.getRadius();
        if (this->self.getPosition().y <= r)
        {
            this->self.setPosition(this->self.getPosition().x, r);
            this->velocity.y *= -1.0f;
        }
        if (this->self.getPosition().y >= SCR_HEIGHT - r)
        {
            this->self.setPosition(this->self.getPosition().x, SCR_HEIGHT - r);
            this->velocity.y *= -1.0f;
        }
        if (this->self.getPosition().x <= r)
        {
            this->self.setPosition(r, this->self.getPosition().y);
            this->velocity.x *= -1.0f;
        }
        if (this->self.getPosition().x >= SCR_WIDTH - r)
        {
            this->self.setPosition(SCR_WIDTH - r, this->self.getPosition().y);
            this->velocity.x *= -1.0f;
        }
    }

    void collideWithOtherCell(Cell cell)
    {
        // Displacement between cells
        sf::Vector2f displacement = this->self.getPosition() - cell.self.getPosition();

        // Apply force if colliding
        if (getMagnitude(displacement) <= this->radius * 2 && getMagnitude(displacement) <= cell.radius * 2)
        {
            if (getMagnitude(displacement) == 0)
            {
                displacement = {(float)Random::get(-1, 1), (float)Random::get(-1, 1)};
            }
            else
            {
                // Repel
                this->applyForce(getSetMagnitude(displacement, getMagnitude(this->velocity) * 10.0f));
            }
        }
        else
        {
            // This can make them attract
            this->applyForce(getSetMagnitude(-displacement, getMagnitude(this->velocity) * 2.0f));
        }

        // ...
    }
};

int main()
{
    // Create loop
    sf::RenderWindow window(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "<name>", sf::Style::Default);

    // Time
    sf::Clock clock;
    sf::Clock deltaClock;
    unsigned int splittingTimer = 0;

    // FPS
    window.setFramerateLimit(FPS);

    // List of Cells
    std::vector<Cell> cells = {};
    cells.push_back(Cell(initialSize, {(float)SCR_WIDTH / 2, (float)SCR_HEIGHT / 2}));

    // Main Loop
    while (window.isOpen())
    {
        // Time
        float time = clock.getElapsedTime().asSeconds();

        // Calculate deltaTime
        float deltaTime = deltaClock.restart().asSeconds();

        // Update split timer
        splittingTimer++;

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
                break;
            case sf::Event::MouseButtonPressed:
                break;
            default:
                break;
            }
        }

        // Reset display
        window.clear(sf::Color::Black);

        // For every cell
        for (unsigned int x = 0; x < cells.size(); x++)
        {
            // Every other cell
            for (unsigned int y = 0; y < cells.size(); y++)
            {
                if (x != y)
                {
                    cells.at(x).collideWithOtherCell(cells.at(y));
                }
            }

            // If cell is clicked (can only check once per second)
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                if (cells.at(x).isClicked(vec2iToVec2f(sf::Mouse::getPosition(window))) && splittingTimer > FPS / 3)
                {
                    // Split cell
                    cells.push_back(Cell(cells.at(x).radius * 0.8, cells.at(x).self.getPosition()));
                    cells.push_back(Cell(cells.at(x).radius * 0.8, cells.at(x).self.getPosition()));
                    cells.erase(cells.begin() + x);

                    // Reset splitting Timer
                    splittingTimer = 0;

                    // std::cout << "Clicked at " << time << "\n";
                }
            }

            // Bounce on borders
            cells.at(x).bounce();

            // Update forces
            cells.at(x).update();

            // Draw cells
            window.draw(cells.at(x).self);
        }

        // Swap buffers
        window.display();
    }

    return 0;
}
