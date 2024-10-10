#include <iostream>
#include "../include/Game.h"
#include "../include/GameRender.h"
#include "../include/InputHandler.h"

int main(){
    Game game;

    // Display welcome message
    TerminalRender::displayWelcomeMessage();

    // Wait for the start game command
    InputType command;
    while (true) {
        command = InputHandler::handleInput();
        if (command == InputType::START_GAME) {
            break;
        } else {
            std::cout << "Invalid input. Press 'E' to start the game.\n";
        }
    }

    game.initGame();
    TerminalRender::render((game.getGameBoard(), 
                            game.getScore(), game.getMoveCount());

    // Game loop
    while (true) {
        InputType input = InputHandler::handleInput();
        if(input == InputType::UNDO) {
            gmae.undoLastMove();
        }
        else if(input == InputType::QUIT_GAME) {
            break;
        }
        else{
            Direction direction;
            switch (input) {
                case InputType::UP:
                    direction = Direction::UP;
                    break;
                case InputType::DOWN:
                    direction = Direction::DOWN;
                    break;
                case InputType::LEFT:
                    direction = Direction::LEFT;
                    break;
                case InputType::RIGHT:
                    direction = Direction::RIGHT;
                    break;
                default:
                    std::cout << "Invalid input. Use arrow keys to move, U to undo, or Q to quit.\n";
                    continue;
            }
            game.move(direction);
        }
        TerminalRender::render((game.getGameBoard(), 
                                game.getScore(), game.getMoveCount());

        if(game.hasWon()) {
            TerminalRender::displayWinMessage();
            break;
        }
        else if(game.hasLost()) {
            TerminalRender::displayLoseMessage();
            break;
        }
    }

    TerminalRender::displayElapsedTime(game.getElapsedTime);

    return 0;
}

