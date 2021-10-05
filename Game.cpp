//
// Created by niko1 on 02.10.2021.
//

#include "Game.h"

Game::Game(){
 finiteState[4][4] = true;
}

Field Game::getInitialField() {
    Field res {};
    for(int i = 0; i < 9; i++){
        int j = 0, k = 9;
        if(i > 2 && i < 6){
            j = 3;
            k = 6;
        }
        for (; j < k; ++j) {
            res[i][j] = true;
        }
    }
    return res;
}

void Game::solve() {
    Field f = getInitialField();
    printField(f);
}

void Game::printField(std::array<std::array<bool, 9>, 9> f) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            std::cout << (f[i][j] ? "●" : "○") << "";
        }
        std::cout<<std::endl;
    }
}
