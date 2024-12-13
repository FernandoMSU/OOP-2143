#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

enum class State { MainMenu, Gameplay, Paused, EndScreen };

int main() {
    sf::RenderWindow gameWindow(sf::VideoMode(800, 600), "Game States Example with Pause and Transitions");

    // Background setup
    sf::Texture bgTexture;
    sf::Sprite bgSprite;
    sf::Vector2u bgSize, screenSize;

    if (!bgTexture.loadFromFile("background_image.jpg")) {
        std::cerr << "Error: Failed to load background image\n";
        return -1;
    } else {
        // Scale background to fit the window
        bgSize = bgTexture.getSize();
        screenSize = gameWindow.getSize();
        float scaleX = static_cast<float>(screenSize.x) / bgSize.x;
        float scaleY = static_cast<float>(screenSize.y) / bgSize.y;
        bgSprite.setTexture(bgTexture);
        bgSprite.setScale(scaleX, scaleY);
    }

    // Current game state
    State gameState = State::MainMenu;

    // Font and text setup
    sf::Font textFont;
    if (!textFont.loadFromFile("Arial.ttf")) {
        std::cerr << "Error: Failed to load font\n";
        return -1;
    }

    sf::Text menuText("Press Enter to Start", textFont, 50);
    menuText.setFillColor(sf::Color::White);
    menuText.setPosition(200.f, 250.f);

    sf::Text gameOverText("Game Over! Press R to Restart", textFont, 50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(150.f, 250.f);

    sf::Text pauseText("Game Paused! Press R to Resume", textFont, 50);
    pauseText.setFillColor(sf::Color::Blue);
    pauseText.setPosition(150.f, 250.f);

    // Click counter setup
    int clickCount = 0;
    sf::Text clickCounter;
    clickCounter.setFont(textFont);
    clickCounter.setCharacterSize(30);
    clickCounter.setFillColor(sf::Color::White);
    clickCounter.setPosition(10.f, 10.f);
    clickCounter.setString("Clicks: 0");

    // Player setup
    sf::CircleShape playerAvatar(50.f);
    playerAvatar.setFillColor(sf::Color::Green);
    playerAvatar.setPosition(300.f, 300.f);

    float moveSpeed = 5.0f;

    // Clock for fade-in effect
    sf::Clock transitionTimer;
    sf::RectangleShape transitionOverlay(sf::Vector2f(800.f, 600.f));
    transitionOverlay.setFillColor(sf::Color(0, 0, 0, 0));

    // Main game loop
    while (gameWindow.isOpen()) {
        sf::Event inputEvent;
        while (gameWindow.pollEvent(inputEvent)) {
            if (inputEvent.type == sf::Event::Closed) {
                gameWindow.close();
            }

            // Handle input for different states
            if (gameState == State::MainMenu) {
                if (inputEvent.type == sf::Event::KeyPressed && inputEvent.key.code == sf::Keyboard::Enter) {
                    gameState = State::Gameplay;
                    transitionTimer.restart();
                }
            } else if (gameState == State::Gameplay) {
                if (inputEvent.type == sf::Event::KeyPressed && inputEvent.key.code == sf::Keyboard::Escape) {
                    gameState = State::EndScreen;
                } else if (inputEvent.type == sf::Event::KeyPressed && inputEvent.key.code == sf::Keyboard::P) {
                    gameState = State::Paused;
                }

                // Player movement
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) playerAvatar.move(0, -moveSpeed);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) playerAvatar.move(-moveSpeed, 0);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) playerAvatar.move(0, moveSpeed);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) playerAvatar.move(moveSpeed, 0);

                // Check for mouse clicks on the player
                if (inputEvent.type == sf::Event::MouseButtonPressed && inputEvent.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePosition(inputEvent.mouseButton.x, inputEvent.mouseButton.y);
                    if (playerAvatar.getGlobalBounds().contains(mousePosition)) {
                        clickCount++;
                        clickCounter.setString("Clicks: " + std::to_string(clickCount));
                    }
                }

            } else if (gameState == State::Paused) {
                if (inputEvent.type == sf::Event::KeyPressed && inputEvent.key.code == sf::Keyboard::R) {
                    gameState = State::Gameplay;
                }
            } else if (gameState == State::EndScreen) {
                if (inputEvent.type == sf::Event::KeyPressed && inputEvent.key.code == sf::Keyboard::R) {
                    gameState = State::MainMenu;
                    clickCount = 0;
                    clickCounter.setString("Clicks: 0");
                }
            }
        }

        // Clear the screen
        gameWindow.clear();

        // Draw the background
        gameWindow.draw(bgSprite);

        // Render according to the current game state
        if (gameState == State::MainMenu) {
            gameWindow.draw(menuText);
        } else if (gameState == State::Gameplay) {
            // Apply fade-in effect
            sf::Time elapsedTime = transitionTimer.getElapsedTime();
            if (elapsedTime.asSeconds() < 1.0f) {
                int alpha = static_cast<int>((1.0f - elapsedTime.asSeconds()) * 255);
                transitionOverlay.setFillColor(sf::Color(0, 0, 0, alpha));
                gameWindow.draw(transitionOverlay);
            }

            gameWindow.draw(playerAvatar);
            gameWindow.draw(clickCounter);
        } else if (gameState == State::Paused) {
            gameWindow.draw(playerAvatar);
            gameWindow.draw(pauseText);
            gameWindow.draw(clickCounter);
        } else if (gameState == State::EndScreen) {
            gameWindow.draw(gameOverText);
        }

        // Display everything on the screen
        gameWindow.display();
    }

    return 0;
}
