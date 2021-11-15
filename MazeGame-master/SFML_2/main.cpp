/*
* An SFML application using a vector list to store point data - Darryl Charles
* SFML Documentation https://www.sfml-dev.org/documentation/2.5.1/
* Set up your own VS2019 project https://www.youtube.com/watch?v=lFzpkvrscs4
*/

#include <iostream>  
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp> 
#include <cmath>
#include "cells.h"
// define render window size constants
#define winWidth 800
#define winHeight 800
const float  PI_F = 3.14159265358979f;


class maze_class {
public:
    void Create_maze();
    sf::RectangleShape displayRects[15 * 15];
    sf::Vector2i player1 = sf::Vector2i(13, 13);
    sf::RectangleShape player = sf::RectangleShape(sf::Vector2f(40.f, 40.f));
    sf::Vector2i player2 = sf::Vector2i(4, 4);
    sf::RectangleShape enemy = sf::RectangleShape(sf::Vector2f(40.f, 40.f));
    int gameMap[15 * 15];

};
    void maze_class::Create_maze()
    {
        int gameMap[15 * 15];
        sf::RectangleShape displayRects[15 * 15];

        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 15; j++) {
                displayRects[i + j * 15].setPosition(i * 40.0f, j * 40.0f);
                displayRects[i + j * 15].setSize(sf::Vector2f(40.f, 40.f));
                displayRects[i + j * 15].setOutlineThickness(1.f);
                displayRects[i + j * 15].setOutlineColor(sf::Color(0, 0, 0));



                //Sets box obstacles
                if (!(i == player1.x && j == player1.y) && !(i == player2.x && j == player2.y)) {
                    if (std::rand() / (float)RAND_MAX < 0.22f || i == 0 || j == 0 || i == 14 || j == 14) {
                        gameMap[i + j * 15] = 1;
                        displayRects[i + j * 15].setFillColor(sf::Color(90, 0, 0));
                    }
                }
            }
        }
    }




int main()
{
    maze_class MazeCreate;
#pragma region ~ Initialise render window ~
    sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "Assignment 2");                            
    // pixel.setOrigin(pixel.getSize().x/2, pixel.getSize().y/2);
#pragma endregion

#pragma region ~ Create a square pixel (SFML graphics object), size it, and give it a color ~
    //sf::RectangleShape pixel(sf::Vector2f(16.0f, 16.0f));
    //pixel.setFillColor(sf::Color::Green);
    //int num_xCells = int(winWidth / pixel.getSize().x);                         // Get pixel width and height of the 2d grid (based on pixel size)
    //int num_yCells = int(winHeight / pixel.getSize().y);
#pragma endregion

#pragma region ~ Create 2d vector array for holding pixel values (integers) ~
    std::vector<std::vector<int>> cellsGrid2D;                                  // Vector list of map tiles  

#pragma endregion

    sf::Texture texture;
    if (!texture.loadFromFile("assets/player.png")) {
        std::cout << "Could not load enemy texture" << std::endl;
        return 0;
    }
    /*
    sf::Sprite playerSprite;
    playerSprite.setTexture(texture);
    playerSprite.setPosition(sf::Vector2f(winWidth / 2, winHeight / 2));
    playerSprite.setOrigin(playerSprite.getLocalBounds().width / 2, playerSprite.getLocalBounds().height / 2);
    playerSprite.setScale(4, 4);
    playerSprite.setRotation(0);
    float playerSpeed = 0.1f;
    */

    //creates players in game
    sf::Vector2i player1 = sf::Vector2i(13, 13);
    sf::RectangleShape player = sf::RectangleShape(sf::Vector2f(40.f, 40.f));
    sf::Vector2i player2 = sf::Vector2i(4, 4);
    sf::RectangleShape enemy = sf::RectangleShape(sf::Vector2f(40.f, 40.f));
    //player.setTexture(texture);
    player.setPosition(player1.x * 40.f, player1.y * 40.f);
    enemy.setPosition(player2.x * 40.f, player2.y * 40.f);
    //player.setOrigin(player.getLocalBounds().width / 2, player.getLocalBounds().height / 2); Causes player to be out of boxes
    player.setFillColor(sf::Color::Green);
    enemy.setFillColor(sf::Color::Red);
    
    //Size of map
    int gameMap[15 * 15];
    sf::RectangleShape displayRects[15 * 15];


    //Sets each boxes properties
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            displayRects[i + j * 15].setPosition(i * 40.0f, j * 40.0f);
            displayRects[i + j * 15].setSize(sf::Vector2f(40.f, 40.f));
            displayRects[i + j * 15].setOutlineThickness(1.f);
            displayRects[i + j * 15].setOutlineColor(sf::Color(0,0,0));



            //Sets box obstacles
            if (!(i == player1.x && j == player1.y) && !( i == player2.x && j == player2.y)) {
                if (std::rand() / (float)RAND_MAX < 0.22f || i == 0 || j == 0 || i == 14 || j == 14) {
                    gameMap[i + j * 15] = 1;
                    displayRects[i + j * 15].setFillColor(sf::Color(90, 0, 0));
                }
            }
        }
    }

#pragma region ~ Load map from file ~
    std::ifstream dataStream;
    std::string line;

    dataStream.open(".\\map.csv");
    if (dataStream.is_open())
    {
        while (std::getline(dataStream, line))
        {
            std::stringstream lineStream(line);
            std::string character;
            std::vector<int> parsedRow;
            while (std::getline(lineStream, character, ','))
            {
                parsedRow.push_back(std::stoi(character));
                std::cout << std::stoi(character);
            }
            std::cout << std::endl;
            cellsGrid2D.push_back(parsedRow);
        }
    }
#pragma endregion  

    sf::Vector2f NormalisedVectorToMouse;

    while (window.isOpen())                                                    
    {
#pragma region ~ Check for a close window event ~
        sf::Event event;                                                // Windows is event driven - this code closes the Window properly
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {

                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                case sf::Keyboard::Up:
                    if (gameMap[player1.x + (player1.y - 1) * 15] != 1) player1.y -= 1;
                    break;
                case sf::Keyboard::Down:
                    if (gameMap[player1.x + (player1.y + 1) * 15] != 1) player1.y += 1;
                    break;
                case sf::Keyboard::Right:
                    if (gameMap[(player1.x + 1) + player1.y * 15] != 1) player1.x += 1;
                    break;
                case sf::Keyboard::Left:
                    if (gameMap[(player1.x - 1) + player1.y * 15] != 1) player1.x -= 1;
                    break;
                }
            }
            player.setPosition(player1.x * 40.f, player1.y * 40.f);
        }
#pragma endregion

        /* get the current mouse position in the window
        sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
        // convert it to world coordinates
        sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mousePixelPos);

        sf::Vector2f vectorToMouse = mouseWorldPos - playerSprite.getPosition();
        float distance = sqrt((vectorToMouse.x * vectorToMouse.x) + (vectorToMouse.y * vectorToMouse.y));

        NormalisedVectorToMouse = sf::Vector2f(vectorToMouse.x / distance, vectorToMouse.y / distance);

        float playerRot = playerSprite.getRotation();
        float angleToMouse = atan2(NormalisedVectorToMouse.y, NormalisedVectorToMouse.x) * 180 / PI_F;

        if (distance > 4) playerSprite.setRotation(90 + angleToMouse);
        if (distance > 16) playerSprite.move(NormalisedVectorToMouse.x * playerSpeed, NormalisedVectorToMouse.y * playerSpeed);

        // std::cout << vectorToMouse.x << ", " << vectorToMouse.y << ", " << NormalisedVectorToMouse.x << ", " << NormalisedVectorToMouse.y << std::endl; */

        window.clear(sf::Color::White);                                                 

        //drawCells(num_xCells, num_yCells, cellsGrid2D, pixel, window);  
        
        for (int i = 0; i < 15 * 15; i++) {
            window.draw(displayRects[i]);
        }
        
        window.draw(player);
        window.draw(enemy);
        window.display();                                               

        if (player1 == player2) {
            window.clear();
            MazeCreate.Create_maze();

            window.display();
        }
        
    }

    return 0;
}
