#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <memory>
#include <regex>
#include <stdexcept>
#include <string>
#include <vector>

namespace fs = std::filesystem;

// Glob function for retrieving files matching a regex
std::vector<std::string> glob(const std::string& folderPath, const std::string& pattern) {
    std::vector<std::string> matchedFiles;

    try {
        if (!fs::exists(folderPath) || !fs::is_directory(folderPath)) {
            throw std::runtime_error("Invalid folder path");
        }

        std::regex regexPattern(pattern);

        for (const auto& entry : fs::directory_iterator(folderPath)) {
            if (entry.is_regular_file()) {
                std::string fileName = entry.path().filename().string();
                if (std::regex_match(fileName, regexPattern)) {
                    matchedFiles.push_back(entry.path().string());
                }
            }
        }

        std::sort(matchedFiles.begin(), matchedFiles.end());
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return matchedFiles;
}

// Class definition for an animated dice
class AnimatedDice : public sf::Drawable, public sf::Transformable {
private:
    std::vector<std::shared_ptr<sf::Texture>> textures;
    sf::Sprite Thedice;
    std::size_t currentFrame;
    sf::Clock animationClock;
    float frameDuration;
    bool clicked;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        states.transform *= getTransform();
        target.draw(Thedice, states);
    }

public:
    AnimatedDice(float frameDuration = 0.1f)
        : currentFrame(0), frameDuration(frameDuration), clicked(false) {}

    AnimatedDice(const std::vector<std::string>& frames, float frameDuration = 0.1f)
        : currentFrame(0), frameDuration(frameDuration), clicked(false) {
        for (const auto& frame : frames) {
            addFrame(frame);
        }
        if (!textures.empty()) {
            Thedice.setTexture(*textures[0]);
        }
    }

    void addFrame(const std::string& textureFile) {
        auto texture = std::make_shared<sf::Texture>();
        if (!texture->loadFromFile(textureFile)) {
            throw std::runtime_error("Failed to load texture: " + textureFile);
        }
        textures.push_back(texture);
    }

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (Thedice.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                clicked = true;
            }
        }
    }

    bool isClicked() const { return clicked; }

    void update() {
        if (textures.empty())
            return;

        if (animationClock.getElapsedTime().asSeconds() > frameDuration) {
            currentFrame = (currentFrame + 1) % textures.size();
            Thedice.setTexture(*textures[currentFrame]);
            animationClock.restart();
        }
    }

    void setPosition(float x, float y) { Thedice.setPosition(x, y); }
    void setScale(float scaleX, float scaleY) { Thedice.setScale(scaleX, scaleY); }
};

// Main function
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dice Background with Animated Dice");

    std::string diceFolder = "./media/animations/dice_roll";
    std::string pattern = R"(dice_\d+\.png)";  // Example pattern for dice images

    std::vector<std::string> diceFiles = glob(diceFolder, pattern);
    if (diceFiles.empty()) {
        std::cerr << "No dice images found in the folder: " << diceFolder << std::endl;
        return -1;
    }

    // Load textures into shared pointers
    std::vector<std::shared_ptr<sf::Texture>> diceTextures;
    for (const auto& file : diceFiles) {
        auto texture = std::make_shared<sf::Texture>();
        if (!texture->loadFromFile(file)) {
            std::cerr << "Failed to load texture: " << file << std::endl;
            return -1;
        }
        diceTextures.push_back(texture);
    }

    // Create grid for dice background
    std::vector<sf::Sprite> diceGrid;
    int diceSize = 100;  // Assume dice size is 100x100
    int rows = window.getSize().y / diceSize + 1;
    int cols = window.getSize().x / diceSize + 1;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            sf::Sprite Thedice(*diceTextures[(i * cols + j) % diceTextures.size()]);
            Thedice.setPosition(j * diceSize, i * diceSize);
            diceGrid.push_back(Thedice);
        }
    }

    // Create animated dice
    AnimatedDice diceRoll(diceFiles, 0.2f);
    diceRoll.setPosition(400, 300);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            diceRoll.handleEvent(event, window);
        }

        if (diceRoll.isClicked()) {
            diceRoll.update();
        }

        window.clear(sf::Color::Black);

        for (const auto& Thedice : diceGrid) {
            window.draw(Thedice);
        }

        window.draw(diceRoll);

        window.display();
    }

    return 0;
}
