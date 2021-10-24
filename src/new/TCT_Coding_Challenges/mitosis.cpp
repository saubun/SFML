#define SFML_NO_DEPRECATED_WARNINGS
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <random.hpp>

using Random = effolkronium::random_static;

unsigned int SCR_WIDTH = 1920;
unsigned int SCR_HEIGHT = 1080;

unsigned int FPS = 60;

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
    unsigned int radius = 100;
    sf::CircleShape self;

    Cell(sf::Vector2f pos = {(float)SCR_WIDTH / 2, (float)SCR_HEIGHT / 2})
    {
        this->self = sf::CircleShape(this->radius);
        this->self.setPosition(pos);
        this->self.setOrigin(this->radius, this->radius);
    }

    void move()
    {
        sf::Vector2f vel = sf::Vector2f(Random::get(0, 1), Random::get(0, 1));
        this->self.move(vel);
    }

    void update()
    {
    }

    bool isClicked(sf::Vector2f mousePos)
    {
        if (distance(this->self.getPosition(), mousePos) <= this->radius)
            return true;
        else
            return false;
    }
};

int main()
{
    // Create loop
    sf::RenderWindow window(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "Mitosis", sf::Style::Default);

    // Time
    sf::Clock clock;
    sf::Clock deltaClock;

    // FPS
    window.setFramerateLimit(FPS);

    // List of Cells
    std::vector<Cell> cells = {};
    cells.push_back(Cell());

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
                break;
            case sf::Event::MouseButtonPressed:
                break;
            default:
                break;
            }
        }

        // Reset display
        window.clear(sf::Color::Black);

        // Draw cells
        for (Cell cell : cells)
        {
            cell.move();
            cell.update();

            window.draw(cell.self);
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            for (Cell cell : cells)
            {
                if (cell.isClicked(vec2iToVec2f(sf::Mouse::getPosition(window))))
                {
                    std::cout << "Clicked at " << time << "\n";
                }
            }
        }

        // Swap buffers
        window.display();
    }

    return 0;
}
