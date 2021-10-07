//
// Created by niko1 on 02.10.2021.
//

#include <algorithm>
#include "Game.h"


Field Game::finiteState{};
const std::vector<std::vector<int>> Game::possibleMoves{{2,  6},
                                                        {7},
                                                        {0,  8},
                                                        {5,  12},
                                                        {13},
                                                        {3,  14},
                                                        {0,  8,  21},
                                                        {1,  22},
                                                        {2,  6,  23},
                                                        {11, 27},
                                                        {12, 28},
                                                        {9,  13, 29},
                                                        {3,  10, 14, 30},
                                                        {4,  11, 15, 31},
                                                        {5,  12, 16, 32},
                                                        {13, 17, 33},
                                                        {14, 34},
                                                        {15, 35},
                                                        {20},
                                                        {21},
                                                        {18, 22},
                                                        {6,  19, 23, 36},
                                                        {7,  20, 24, 37},
                                                        {8,  21, 25, 38},
                                                        {22, 26},
                                                        {23},
                                                        {24},
                                                        {9,  29},
                                                        {10, 30},
                                                        {27, 11, 31},
                                                        {12, 28, 32, 39},
                                                        {13, 29, 33, 40},
                                                        {14, 30, 34, 41},
                                                        {15, 31, 35},
                                                        {16, 32},
                                                        {17, 33},
                                                        {21, 38, 42},
                                                        {22, 43},
                                                        {23, 36, 44},
                                                        {30, 41},
                                                        {31},
                                                        {32, 39},
                                                        {36, 44},
                                                        {37},
                                                        {38, 42}};

std::vector<std::pair<int, int>> Game::fieldMap = enumerateField();

Game::Game() {
    finiteState[4][4] = true;
};

Field Game::getInitialField() {
    Field res{};
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (!(i > 2 && i < 6) && (j < 3 || j > 5)) {
                continue;
            }
            res[i][j] = true;
        }
    }
    res[4][4] = false;
    return res;
}

void Game::solve() {
    Field f = getInitialField();
    moveHistory.push_back({f,{0,0,'e'}});
    f[4][3] = false;
    printField(f);
    if(!backtracking(1)){
        std::cout << "Something went wrong" << std::endl;
        return;
    }
    printField(f);
    for(auto state:moveHistory){
        std::cout << std::get<0>(state.second) << " => " << std::get<1>(state.second) << std::endl;
    }
}

void Game::printField(Field f) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (!(i > 2 && i < 6) && (j < 3 || j > 5)) {
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

std::vector<std::pair<Field,std::tuple<int, int, char>>> Game::getAvailableMoves(Field f) {
    //auto cmp = [](Field left, Field right) { return h(left) > h(right); };
    std::vector<std::pair<Field,std::tuple<int, int, char>>> res{};

    for (int blankPosition: getBlankPositions(f)) {
        int i = fieldMap[blankPosition].first, j = fieldMap[blankPosition].second;
        for (int movePosition: possibleMoves[blankPosition]) {
            int fi = fieldMap[movePosition].first, fj = fieldMap[movePosition].second;
            Field newState {};
            std::copy(f.begin(), f.end(), newState.begin());
            newState[fi][fj] = false;
            newState[i][j] = true;
            if (movePosition == blankPosition - 2) {
                if(f[i][j - 1] && f[i][j - 2]) {
                    newState[fi][fj + 1] = false;
                    res.push_back({newState,{movePosition, blankPosition, 'r'}});
                }
                continue;
            }
            if (movePosition == blankPosition + 2) {
                if(f[i][j + 1] && f[i][j + 2]) {
                    newState[fi][fj - 1] = false;
                    res.push_back({newState,{movePosition, blankPosition, 'l'}});
                }
                continue;
            }
            if (movePosition < blankPosition ) {
                if(f[i - 1][j] && f[i - 2][j]){
                    newState[fi + 1][fj] = false;
                    res.push_back({newState,{movePosition, blankPosition, 'd'}});
                }
                continue;
            }
            if (movePosition > blankPosition) {
                if(f[i + 1][j] && f[i + 2][j]){
                    newState[fi - 1][fj] = false;
                    res.push_back({newState,{movePosition, blankPosition, 'u'}});
                }
                continue;
            }
        }
    }
    return res;
}

std::vector<int> Game::getBlankPositions(Field f) {
    std::vector<int> res{};
    int pos = 0;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (!(i > 2 && i < 6) && (j < 3 || j > 5)) {
                continue;
            }
            if(!f[i][j]){
                res.push_back(pos);
            }
            pos++;
        }
    }
    return res;
}

std::vector<std::pair<int, int>> Game::enumerateField() {
    std::vector<std::pair<int, int>> res{};
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (!(i > 2 && i < 6) && (j < 3 || j > 5)) {
                continue;
            }
            res.emplace_back(i, j);
        }
    }
    return res;
}

bool Game::backtracking(int counter) {
    //std::cout << counter << std::endl;
    Field state = moveHistory.back().first;
    if(isFinish(state)){
        return true;
    }
    auto moves = getAvailableMoves(state);
    if(moves.empty()){
        return false;
    }
    for(auto move: moves){
        long long hash = hashField(move.first);
        if(failedStates.find(hash) != failedStates.end()){
//            std::cout << "collision" << std::endl;
            return false;
        }
        moveHistory.emplace_back(move);
        if(!backtracking(counter + 1)){
            failedStates.insert(hashField(moveHistory.back().first));
            moveHistory.pop_back();
        }else{
            return true;
        }
    }
    return false;
}

Field Game::getStateAfterMove(Field state, std::tuple<int, int, char> move) {

    int from, to, fromI, fromJ, toI, toJ;
    char direction;
    std::tie(from, to, direction) = move;
    std::tie(fromI, fromJ) = fieldMap[from];
    std::tie(toI, toJ) = fieldMap[to];
    Field newState {};
    std::copy(state.begin(), state.end(), newState.begin());
    newState[fromI][fromJ] = false;
    if(direction == 'l'){
        newState[fromI][fromJ - 1] = false;
    } else if(direction == 'r'){
        newState[fromI][fromJ + 1] = false;
    } else if(direction == 'u'){
        newState[fromI - 1][fromJ] = false;
    } else if(direction == 'd'){
        newState[fromI + 1][fromJ] = false;
    }
    newState[toI][toJ] = true;
    return newState;
}

bool Game::isFinish(std::array<std::array<bool, 9>, 9> f) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if(f[i][j] != finiteState[i][j]){
                return false;
            }
        }
    }
    return true;
}

int Game::getPositionNumber(std::pair<int, int> coordinates) {
    for(int i = 0; i < fieldMap.size(); i ++){
        if(fieldMap[i] == coordinates){
            return i;
        }
    }
    return -1;
}

long long Game::hashField(std::array<std::array<bool, 9>, 9> f) {
    long long res = 0;
    int shift = 0;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (!(i > 2 && i < 6) && (j < 3 || j > 5)) {
                continue;
            }
            res += (f[i][j]?1LL:0LL) << shift;
            shift++;
        }
    }
    return res;
}

int Game::h(Field f) {
    int res = 0;
    // corners
    res += f[0][3] + f[0][5] + f[3][0] + f[5][0] + f[3][8] + f[5][8] + f[8][3]  + f[8][5];
    // Merson regions
    res += (f[1][3] && f[2][3]) + (f[3][1] && f[3][2]) + (f[5][1] && f[5][2]) + (f[6][3] && f[7][3]) + (f[6][5] && f[7][5]) + (f[5][6] && f[5][7]) + (f[3][6] && f[3][7]) + (f[1][5] && f[2][5]) + (f[3][3] && f[3][4] && f[4][3] && f[4][4]);
    return res;
}
