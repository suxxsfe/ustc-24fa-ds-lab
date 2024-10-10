#include "../include/GameBoard.h"
#include <algorithm>
#include <random>
#include <chrono>

GameBoard::GameBoard() {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator = std::mt19937(seed);
    reset();
}

const int GameBoardSize = 4, InitTilesNum = 2, GameGoal = 2048;

void GameBoard::generateNewTile(){
    int x, y;
    do{
        x = generator()%GameBoardSize;
        y = generator()%GameBoardSize;
    }while(board[x][y]);
    board[x][y] = (generator()%2+1)*2;
}

void GameBoard::reset() {    
    board.resize(GameBoardSize);
    for(int i = 0; i < GameBoardSize; i++){
        board[i].resize(GameBoardSize);
        for(int j = 0; j < GameBoardSize; j++){
            board[i][j] = 0;
        }
    }

    for(int k = 0; k < InitTilesNum ; k++){
        generateNewTile();
    }
}

int GameBoard::move(Direction direction) {
    slide(direction);
    int score = merge(direction);
    generateNewTile();
    return score;
}

void GameBoard::slide(Direction direction) {
    if(direction == Direction::UP){
        for(int i = 0; i < GameBoardSize; i++){
            for(int j = GameBoardSize-1, k = j; ~j; j--){
                if(board[i][j]){
                    board[i][k] = board[i][j];
                    k--;
                }
            }
        }
    }
    else if(direction == Direction::DOWN){
        for(int i = 0; i < GameBoardSize; i++){
            for(int j = 0, k = j; j < GameBoardSize; j++){
                if(board[i][j]){
                    board[i][k] = board[i][j];
                    k++;
                }
            }
        }
    }
    else if(direction == Direction::LEFT){
        for(int j = 0; j < GameBoardSize; j++){
            for(int i = 0, k = i; i < GameBoardSize; i++){
                if(board[i][j]){
                    board[k][j] = board[i][j];
                    k++;
                }
            }
        }
    }
    else if(direction == Direction::RIGHT){
        for(int j = 0; j < GameBoardSize; j++){
            for(int i = GameBoardSize-1 , k = i; ~i; i--){
                if(board[i][j]){
                    board[k][j] = board[i][j];
                    k--;
                }
            }
        }
    }
}

int GameBoard::merge(Direction direction) {
    int moveScore = 0;
    
    if(direction == Direction::UP){
        for(int i = 0; i < GameBoardSize; i++){
            for(int j = GameBoardSize-2, k = j+1; ~j; j--){
                if(!board[i][j]);
                else if(board[i][j] == board[i][k]){
                    board[i][k]<<=1;
                }
                else{
                    board[i][--k] = board[i][j];
                }
            }
        }
    }
    else if(direction == Direction::DOWN){
        for(int i = 0; i < GameBoardSize; i++){
            for(int j = 1, k = j-1; j < GameBoardSize; j++){
                if(!board[i][j]);
                else if(board[i][j] == board[i][k]){
                    board[i][k]<<=1;
                }
                else{
                    board[i][++k] = board[i][j];
                }
            }
        }
    }
    else if(direction == Direction::RIGHT){
        for(int j = 0; j < GameBoardSize; j++){
            for(int i = GameBoardSize-2, k = i+1; ~i; i--){
                if(!board[i][j]);
                else if(board[i][j] == board[k][j]){
                    board[k][j]<<=1;
                }
                else{
                    board[--k][j] = board[i][j];
                }
            }
        }
    }
    else if(direction == Direction::LEFT){
        for(int j = 0; j < GameBoardSize; j++){
            for(int i = 1, k = i-1; i < GameBoardSize; i++){
                if(!board[i][j]);
                else if(board[i][j] == board[k][j]){
                    board[k][j]<<=1;
                }
                else{
                    board[++k][j] = board[i][j];
                }
            }
        }
    }

    return moveScore;
}

bool GameBoard::isGameOver() const {
    for(int i = 0; i < GameBoardSize; i++){
        for(int j = 0; j < GameBoardSize; j++){
            if(!board[i][j]){
                return false;
            }
            if((i+1 < GameBoardSize && board[i][j] == board[i+1][j])
                    || (j+1 < GameBoardSize && board[i][j] == board[i][j+1])){
                return false;
            }
        }
    }
    return true;
}

bool GameBoard::hasWinningTile() const {
    for(int i = 0; i < GameBoardSize; i++){
        for(int j = 0; j < GameBoardSize; j++){
            if(board[i][j] == GameGoal){
                return true;
            }
        }
    }
    return false;
}

const Board &GameBoard::getBoard() const {
    return board;
}
