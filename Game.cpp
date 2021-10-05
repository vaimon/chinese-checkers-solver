//
// Created by niko1 on 02.10.2021.
//

#include "Game.h"

Game::Game() {
    finiteState[4][4] = true;
}

GameField Game::getInitialField() {
    GameField res{};
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
    GameField f = getInitialField();
    getWalkingMatrices(f);
    printField(f);
}

void Game::printField(GameField f) {
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

std::pair<HorizontalField,VerticalField> Game::getWalkingMatrices(GameField &f) {
    HorizontalField horizontal {};
    VerticalField vertical {};

    for (int i = 0; i < 9; ++i) {
        for (int j = 3; j < 6; ++j) {
            vertical[i][j-3] = &f[i][j];
        }
    }
    for (int i = 3; i < 6; ++i) {
        for (int j = 0; j < 9; ++j) {
            horizontal[i-3][j] = &f[i][j];
        }
    }
    return {horizontal,vertical};
}

void Game::printWalkingMatrices(HorizontalField horizontal,VerticalField vertical) {
    std::cout << std::endl;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (*vertical[i][j]) {
                printf(" o ");
            } else {
                printf(" x ");
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (*horizontal[i][j]) {
                printf(" o ");
            } else {
                printf(" x ");
            }
        }
        std::cout << std::endl;
    }
}

std::vector<std::pair<int, int>> Game::getAvailableMoves(GameField& f) {
    auto [horizontal, vertical] = getWalkingMatrices(f);
    for (int i = 0; i < 9; ++i) {
        

    }
}

bool Game::checkUp(GameField &f, int i, int j) {
    return false;
}

bool Game::checkDown(GameField &f, int i, int j) {
    return false;
}

bool Game::checkRight(GameField &f, int i, int j) {
    return false;
}

bool Game::checkLeft(GameField &f, int i, int j) {
    return false;
}
