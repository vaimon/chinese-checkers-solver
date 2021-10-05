//
// Created by niko1 on 02.10.2021.
//

#include "Game.h"


Field Game::finiteState {};
const std::vector<std::vector<int>> Game::possibleMoves{{2,6},{7},{0,8},{5,12},{13},
                                                        {3,14},{0,8,21},{1,22},{2,6,23},{11,27},
                                                        {12,28},{9,13,29},{3,10,14,30},{4,11,15,31},{5,12,16,32},
                                                        {13,17,33},{14,34},{15,35},{20},{21},
                                                        {18,22},{6,19,23,36},{7,20,24,37},{8,21,25,38},{22,26},
                                                        {23},{24},{9,29},{10,30},{27,11,31},
                                                        {12,28,32,39},{13,29,33,40},{14,30,34,41},{15,31,35},{16,32},
                                                        {17,33},{21,38,42},{22,43},{23,36,44},{30,41},
                                                        {31},{32,39},{36,44}, {37}, {38,42}};

std::vector<std::pair<int,int>> Game::fieldMap = enumerateField();

Game::Game(){
    finiteState[4][4] = true;
};

Field Game::getInitialField() {
    Field res{};
    for (int i = 0; i < 9; i++) {
        int j = 0, k = 9;
        if (!(i > 2 && i < 6)) {
            j = 3;
            k = 6;
        }
        for (; j < k; ++j) {
            res[i][j] = true;
        }
    }
    res[4][4] = false;
    return res;
}

void Game::solve() {
    Field f = getInitialField();
    printField(f);
}

void Game::printField(Field f) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if(!(i > 2 && i < 6) && (j < 3 || j > 5)){
                printf("   ");
                continue;
            }
            if (f[i][j]) {
                printf(" o ");
            } else {
                printf(" x ");
            }

        }
        std::cout << std::endl;
    }
}

std::vector<std::pair<int, int>> Game::getAvailableMoves(Field f) {
    for (auto pair: getBlankPositions(f)){
        
    }
    return {};
}

std::vector<std::pair<int, int>> Game::getBlankPositions(Field f) {
    std::vector<std::pair<int, int>> res {};
    for (int i = 0; i < 9; i++) {
        int j = 0, k = 9;
        if (!(i > 2 && i < 6)) {
            j = 3;
            k = 6;
        }
        for (; j < k; ++j) {
            if(!f[i][j]){
                res.emplace_back(i,j);
            }
        }
    }
    return res;
}

std::vector<std::pair<int, int>> Game::enumerateField() {
    std::vector<std::pair<int,int>> res {};
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if(!(i > 2 && i < 6) && (j < 3 || j > 5)){
                continue;
            }
            res.emplace_back(i,j);
        }
    }
    return res;
}
