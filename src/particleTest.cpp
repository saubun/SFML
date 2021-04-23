#define SFML_NO_DEPRECATED_WARNINGS
#include <iostream>
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <vector>
#include <random.hpp>

unsigned int SCR_WIDTH = 1024;
unsigned int SCR_HEIGHT = 768;

unsigned int FPS_LIMIT = 60;

using Random = effolkronium::random_static;

sf::Vector2f glmToSf(glm::vec2 vector)
{
    return sf::Vector2f(vector.x, vector.y);
}

glm::vec2 sfToGlm(sf::Vector2f vector)
{
    return glm::vec2(vector.x, vector.y);
}

int main()
{
    // Create loop
    sf::RenderWindow window(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "Saubuny Particle Life", sf::Style::Default);

    // List of particles
    std::vector<sf::CircleShape> particles = {};

    // Current color of particle creation
    sf::Color particleColor = sf::Color::Red;

    // Time
    sf::Clock clock;
    sf::Clock deltaClock;
    sf::Clock fpsClock;

    // Init font
    sf::Font font;
    font.loadFromFile("res/larabiefont.ttf");

    // Init text
    sf::Text screenText;
    screenText.setFont(font);
    screenText.setCharacterSize(24);

    // FPS
    window.setFramerateLimit(FPS_LIMIT);

    // Vars
    glm::vec2 velocity(0, 0);
    glm::vec2 oldVelocity(0, 0);

    // Main Loop
    while (window.isOpen())
    {
        // Time
        float time = clock.getElapsedTime().asSeconds();

        // Calculate deltaTime
        float deltaTime = deltaClock.restart().asSeconds();

        // Calculate FPS
        int fps = round(1.0 / fpsClock.restart().asSeconds());

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

                // Change to slow particle
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
                    particleColor = sf::Color::Red;

                // Change to excited particle
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
                    particleColor = sf::Color::Blue;

                // Change to SPEED particle
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
                    particleColor = sf::Color::Green;

                break;
            case sf::Event::MouseButtonPressed:

                break;
            default:
                break;
            }
        }

        // Reset display
        window.clear(sf::Color::Black);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            unsigned int size = 2;
            sf::Vector2f pos(sf::Mouse::getPosition(window).x - size, sf::Mouse::getPosition(window).y - size);
            sf::CircleShape particle(size);
            particle.setFillColor(particleColor);
            particle.setPosition(pos);
            particles.push_back(particle);
        }

        // For every particle
        for (unsigned int x = 0; x < particles.size(); x++)
        {
            // Draw
            window.draw(particles.at(x));

            // Logic for particle behavior
            if (particles.at(x).getFillColor() == sf::Color::Blue)
            {
                // Choose random direction
                float num1 = Random::get(-100.0f, 100.0f);
                float num2 = Random::get(-100.0f, 100.0f);

                // Move
                particles.at(x).move(num1 * deltaTime, num2 * deltaTime);
            }
            else if (particles.at(x).getFillColor() == sf::Color::Red)
            {
                // Choose random direction
                float num1 = Random::get(-20.0f, 20.0f);
                float num2 = Random::get(-20.0f, 20.0f);

                // Move
                particles.at(x).move(num1 * deltaTime, num2 * deltaTime);
            }
            else if (particles.at(x).getFillColor() == sf::Color::Green)
            {
                // Choose random direction
                float num1 = Random::get(-500.0f, 500.0f);
                float num2 = Random::get(-500.0f, 500.0f);

                // Move
                particles.at(x).move(num1 * deltaTime, num2 * deltaTime);
            }

            // Particle attraction (stay away at a certain distance)
            for (unsigned int y = 0; y < particles.size(); y++)
            {
                // Calculate attraction
                oldVelocity = velocity;
                glm::vec2 displacement = sfToGlm(particles.at(x).getPosition()) - sfToGlm(particles.at(y).getPosition());
                glm::vec2 direction;
                try
                {
                    direction = glm::normalize(displacement);
                }
                catch (const std::exception &e)
                {
                    direction = glm::vec2(1.0f, 0.0f);
                }
                glm::vec2 velocity = direction * 5.0f * deltaTime;
                glm::vec2 acceleration = (velocity - oldVelocity) / deltaTime;

                // Circular collision
                float distance = sqrtf(
                    powf(particles.at(y).getPosition().x - particles.at(x).getPosition().x, 2) +
                    powf(particles.at(y).getPosition().y - particles.at(x).getPosition().y, 2));
            }

            // Delete particle if off screen
            if (particles.at(x).getPosition().x < 0 or particles.at(x).getPosition().x > SCR_WIDTH or particles.at(x).getPosition().y < 0 or particles.at(x).getPosition().y > SCR_HEIGHT)
            {
                particles.erase(particles.begin() + x);
            }
        }

        // Render text[s]
        char c[10];
        sprintf(c, "%d", fps);
        std::string string(c);
        screenText.setString(sf::String("FPS:" + string));
        screenText.setPosition(20, 10);
        window.draw(screenText);

        sprintf(c, "%d", (int)particles.size());
        string = c;
        screenText.setString(sf::String("Particles:" + string));
        screenText.setPosition(20, 40);
        window.draw(screenText);

        // Swap buffers
        window.display();
    }

    return 0;
}