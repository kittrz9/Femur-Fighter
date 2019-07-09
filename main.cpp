#include <SFML/Graphics.hpp>
#include "playerC.h"
#include <sstream>
#define SCREENW 1600
#define SCREENH 900

float grav = 1;
bool debugShown = false;

int main() {
    // Femur Breaker background
    sf::Texture background;
    if(!background.loadFromFile("femur.png")){
        printf("failed to load femur breaker\n");
    }

    sf::RectangleShape backgroundR(sf::Vector2f(SCREENW, SCREENH));
    backgroundR.setTexture(&background);
    backgroundR.setPosition(0,0);

    // Player textures
    sf::Texture sansGriffin;
    if(!sansGriffin.loadFromFile("sGriff.png")){
        printf("failed to load Sans Griffin");
    }

    sf::Texture skeleman;
    if(!skeleman.loadFromFile("skeleman.png")){
        printf("failed to load skeleman");
    }

    // Text stuff
    sf::Font font;
    // Replace the string here with whatever font you want, idk if I can include it into the repository because it might be copyrighted or something
    if(!font.loadFromFile("ariblk.ttf")) {
        printf("font could not load");
    }

    sf::Text debugText;
    debugText.setFont(font);
    debugText.setCharacterSize(20);
    debugText.setFillColor(sf::Color::White);

    sf::Text playerMarker;
    playerMarker.setFillColor(sf::Color::White);
    playerMarker.setFont(font);
    playerMarker.setCharacterSize(40);

    // Timers and stuff
    sf::Clock hitTimer1;
    sf::Clock hitTimer2;
    sf::Clock hitboxTimer;
    sf::Clock hitboxTimer2;

    // SFML window
    sf::RenderWindow window(sf::VideoMode(SCREENW, SCREENH), "platforming game test i dont know smh my head");
    window.setFramerateLimit(60);

    // Players
    playerC player(2*(SCREENW/3), SCREENH/2);
    playerC player2(SCREENW/3, SCREENH/2);

    // Rectangle for the floor
    sf::RectangleShape floor(sf::Vector2f(SCREENW, SCREENH/8));
    floor.setFillColor(sf::Color::Yellow);
    floor.setPosition(0, SCREENH-(SCREENH/8));

    // Rectangle for player one
    sf::RectangleShape playerRect(sf::Vector2f(SCREENW/15, SCREENH/5));
    playerRect.setPosition(player.xPos, player.yPos);
    playerRect.setTexture(&sansGriffin);
    //playerRect.setFillColor(sf::Color::Green);

    // Rectangle for player two
    sf::RectangleShape player2Rect(sf::Vector2f(SCREENW/15, SCREENH/5));
    player2Rect.setTexture(&skeleman);
    //player2Rect.setFillColor(sf::Color::Blue);

    // Rectangle for players hitboxes
    sf::RectangleShape playerHitbox(sf::Vector2f(SCREENW/20, SCREENW/20));
    playerHitbox.setPosition(-100, -100);
    playerHitbox.setFillColor(sf::Color::Red);

    sf::RectangleShape playerHitbox2(sf::Vector2f(SCREENW/20, SCREENW/20));
    playerHitbox2.setPosition(-100, -100);
    playerHitbox2.setFillColor(sf::Color::Red);

    while (window.isOpen()){
        // SFML event handling
        sf::Event event;
        while (window.pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    switch(event.key.code){
                        // Player 1 input
                        // Dash left
                        case sf::Keyboard::Q:
                            if(!player.dashing){
                                player.xVel = -20;
                                player.yVel = 5;
                                player.dashing = true;
                            }
                            break;
                        // Dash right
                        case sf::Keyboard::E:
                            if(!player.dashing){
                                player.xVel = 20;
                                player.yVel = 5;
                                player.dashing = true;
                            }
                            break;
                        // Show debug screen
                        case sf::Keyboard::F3:
                            debugShown = !debugShown;
                            break;

                        case sf::Keyboard::F1:
                            player.invulnerable = !player.invulnerable;
                            break;

                        case sf::Keyboard::F2:
                            player2.invulnerable = !player2.invulnerable;
                            break;

                        // Left punch
                        case sf::Keyboard::Left:{
                            float hitboxXPos = player.xPos - SCREENW/20;
                            float hitboxYPos = player.yPos - SCREENH/7;
                            playerHitbox.setPosition(hitboxXPos, hitboxYPos);
                            if(((abs(player2.xPos - hitboxXPos) * 2 < (SCREENW/15 + SCREENW/20)) &&
                                (abs((player2.yPos - SCREENH/5) - hitboxYPos) * 2 < (SCREENH/5 + SCREENW/20))) &&
                                 !player2.hit){
                                player.punch(LEFT, &player2);
                                player2.hit = true;
                                hitTimer2.restart();
                            }
                            hitboxTimer.restart();
                            break;
                            }
                        // Right punch
                        case sf::Keyboard::Right:{
                            float hitboxXPos = player.xPos + SCREENW/20;
                            float hitboxYPos = player.yPos - SCREENH/7;
                            playerHitbox.setPosition(hitboxXPos, hitboxYPos);
                            if(((abs(player2.xPos - hitboxXPos) * 2 < (SCREENW/15 + SCREENW/20)) &&
                                (abs((player2.yPos - SCREENH/5) - hitboxYPos) * 2 < (SCREENH/5 + SCREENW/20))) &&
                                 !player2.hit){
                                player.punch(RIGHT, &player2);
                                player2.hit = true;
                                hitTimer2.restart();
                            }
                            hitboxTimer.restart();
                            break;
                            }
                        // Up punch
                        case sf::Keyboard::Up:{
                            float hitboxXPos = player.xPos;
                            float hitboxYPos = player.yPos - SCREENH/5 - SCREENW/40;
                            playerHitbox.setPosition(hitboxXPos, hitboxYPos);
                            if(((abs(player2.xPos - hitboxXPos) * 2 < (SCREENW/15 + SCREENW/20)) &&
                                (abs((player2.yPos - SCREENH/5) - hitboxYPos) * 2 < (SCREENH/5 + SCREENW/20))) &&
                                 !player2.hit){
                                player.punch(UP, &player2);
                                player2.hit = true;
                                hitTimer2.restart();
                            }
                            hitboxTimer.restart();
                            break;
                            }


                        case sf::Keyboard::Numpad4:{
                            float hitboxXPos = player2.xPos - SCREENW/20;
                            float hitboxYPos = player2.yPos - SCREENH/7;
                            playerHitbox2.setPosition(hitboxXPos, hitboxYPos);
                            if(((abs(player.xPos - hitboxXPos) * 2 < (SCREENW/15 + SCREENW/20)) &&
                                (abs((player.yPos - SCREENH/5) - hitboxYPos) * 2 < (SCREENH/5 + SCREENW/20))) &&
                                 !player.hit){
                                player2.punch(LEFT, &player);
                                player.hit = true;
                                hitTimer1.restart();
                            }
                            hitboxTimer2.restart();
                            break;
                        }

                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }

        // player stuff
        player.updateStuff();
        player2.updateStuff();
        playerRect.setPosition(player.xPos, player.yPos - SCREENH/5);
        player2Rect.setPosition(player2.xPos, player2.yPos - SCREENH/5);
        if(player2.hit && hitTimer2.getElapsedTime() > sf::seconds(0.2))
            player2.hit = false;
        if(player.hit && hitTimer1.getElapsedTime() > sf::seconds(0.2))
            player.hit = false;

        if(player2.health <= 0 || player.health <= 0){
            player.health = 100;
            player2.health = 100;
            player.reset(2*(SCREENW/3) , SCREENH/2);
            player2.reset(SCREENW/3 , SCREENH/2);
        }


        // Movement
        if(window.hasFocus()){
            // Player 1
            // Left and right movement
            if(!player.hit){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                    player.xVel -= 10;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                    player.xVel += 10;

                // Jumping
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                    player.jump();

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                    player.gravMult = 4;
                else
                    player.gravMult = 1;
            }

            // Player 2
            // Mainly here just for testing, idk if I'll ever even make this fully multiplayer
            if(!player2.hit){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
                    player2.xVel -= 10;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown))
                    player2.xVel += 10;
            }
        }

        // Draw everything to screen
        window.clear();
        window.draw(backgroundR);
        window.draw(floor);
        window.draw(playerRect);
        window.draw(player2Rect);
        if(hitboxTimer.getElapsedTime() < sf::seconds(0.2))
            window.draw(playerHitbox);
        if(hitboxTimer2.getElapsedTime() < sf::seconds(0.2))
            window.draw(playerHitbox2);

        playerMarker.setFillColor(sf::Color::White);
        playerMarker.setString("P1");
        playerMarker.setPosition(player.xPos + SCREENW/60, player.yPos - SCREENH/4);

        window.draw(playerMarker);
        playerMarker.setString("P2");

        playerMarker.setPosition(player2.xPos + SCREENW/60, player2.yPos - SCREENH/4);
        window.draw(playerMarker);

        // Using player marker for the health because I don't want to make another text thing
        std::stringstream health;
        health << player.health << "%";
        playerMarker.setString(health.str());
        playerMarker.setPosition(SCREENW/20, SCREENH - SCREENH/10);
        playerMarker.setFillColor(sf::Color::Black);
        window.draw(playerMarker);

        health.str(std::string());
        health << player2.health << "%";
        playerMarker.setString(health.str());
        playerMarker.setPosition(4*(SCREENW/20), SCREENH - SCREENH/10);
        window.draw(playerMarker);

        // Debug screen thing
        if(debugShown){
            std::stringstream debugString;
            debugString << "Pos: " << player.xPos << ", " << player.yPos <<
                           "\nVel1: " << player.xVel << ", " << player.yVel <<
                           "\nVel2: " << player2.xVel << ", " << player2.yVel <<
                           "\nJumping: " << (player.jumping ? "true" : "false") <<
                           "\nDashing: " << (player.dashing ? "true" : "false") <<
                           "\nGravity Multiplier: " << player.gravMult <<
                           "\nP1Hit: " << (player.hit ? "true" : "false") <<
                           " | P2Hit: " << (player2.hit ? "true" : "false") <<
                           "\nHit timer 1: " << hitTimer1.getElapsedTime().asSeconds() <<
                           "\nHit timer 2: " << hitTimer2.getElapsedTime().asSeconds() <<
                           "\nHitbox timer thing: " << hitboxTimer.getElapsedTime().asSeconds();

            debugText.setString(debugString.str());
            window.draw(debugText);
        }

        window.display();
    }

    return 0;
}
