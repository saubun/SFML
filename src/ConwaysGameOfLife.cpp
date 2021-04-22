#define SFML_NO_DEPRECATED_WARNINGS
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

unsigned int SCR_WIDTH = 1024;
unsigned int SCR_HEIGHT = 768;

unsigned int FPS = 30;

unsigned int MARGIN = 1;
unsigned int SIZE = 20;

int main()
{
    // Create loop
    sf::RenderWindow window(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "Conway's Game Of Life", sf::Style::Default);

    // Initialize list of cells
    std::vector<std::vector<unsigned int>> grid = {};
    unsigned int rows = ceil(SCR_HEIGHT / (SIZE + MARGIN)) + 1;
    unsigned int cols = ceil(SCR_WIDTH / (SIZE + MARGIN)) + 1;
    bool gameStarted = false;

    // Fill list w/ dead cells
    for (unsigned int x = 0; x < cols; x++)
    {
        std::vector<unsigned int> temp = {};
        grid.push_back(temp);
        for (unsigned int y = 0; y < rows; y++)
        {
            grid[x].push_back(0);
        }
    }

    // Time
    sf::Clock clock;
    sf::Clock deltaClock;

    // FPS
    window.setFramerateLimit(FPS);

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

                // Toggle pause
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
                {
                    gameStarted = !gameStarted;
                    gameStarted ? printf("game started\n") : printf("game paused\n");
                }
                break;
            case sf::Event::MouseButtonPressed:
                // Draw new cells
                if (!gameStarted)
                {
                    sf::Vector2f pos(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

                    unsigned int row = ceil(pos.x / (SIZE + MARGIN)) - 1;
                    unsigned int col = ceil(pos.y / (SIZE + MARGIN)) - 1;

                    if (grid[row][col] == 0)
                        grid[row][col] = 1;
                    else if (grid[row][col] == 1)
                        grid[row][col] = 0;
                }
                break;
            default:
                break;
            }
        }

        // Reset display
        window.clear(sf::Color::Black);

        // Draw cells
        for (unsigned int x = 0; x < cols; x++)
        {
            for (unsigned int y = 0; y < rows; y++)
            {
                sf::Color color;
                if (grid[x][y] == 0)
                    color = sf::Color::White;
                if (grid[x][y] == 1)
                    color = sf::Color::Black;
                sf::RectangleShape cell(sf::Vector2f(SIZE, SIZE));
                cell.setPosition(
                    (MARGIN + SIZE) * x + MARGIN,
                    (MARGIN + SIZE) * y + MARGIN);
                cell.setFillColor(color);
                window.draw(cell);
            }
        }

        // Game logic

        if (gameStarted)
        {
            // Create empty new list to modify
            std::vector<std::vector<unsigned int>> newGrid;
            for (unsigned int x = 0; x < cols; x++)
            {
                std::vector<unsigned int> temp;
                newGrid.push_back(temp);
                for (unsigned int y = 0; y < rows; y++)
                {
                    newGrid[x].push_back(0);
                }
            }

            // For every cell
            for (unsigned int x = 0; x < cols; x++)
            {
                for (unsigned int y = 0; y < rows; y++)
                {

                    // Count neighbors
                    int sum = 0;
                    for (int i = -1; i < 2; i++)
                        for (int j = -1; j < 2; j++)
                            if (grid[x + i][y + j])
                                sum++;

                    // Remove self as a neighbor
                    sum -= grid[x][y];

                    // Simple rules
                    if (grid[x][y] == 0 && sum == 3)
                        newGrid[x][y] = 1;
                    else if (grid[x][y] == 1 && (sum < 2 || sum > 3))
                        newGrid[x][y] = 0;
                    else
                        newGrid[x][y] = grid[x][y];
                }
            }

            // Set grid
            grid.clear();
            grid = newGrid;
        }

        // Swap buffers
        window.display();
    }

    return 0;
}
