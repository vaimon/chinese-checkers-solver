//
// Created by niko1 on 02.10.2021.
//

#include <algorithm>
#include "Game.h"


Field Game::finiteState{};
const std::vector<std::vector<int>> Game::possibleMoves{
        {2,  8},
        {9},
        {0,  10},
        {5,  15},
        {16},
        {3,  17},
        {8,  20},
        {9,  21},
        {0,  6,  10, 22},
        {1,  7,  11, 23},
        {2,  8,  12, 24},
        {9,  25},
        {10, 26},
        {15},
        {16},
        {3,  13, 17, 27},
        {4,  14, 18, 28},
        {5,  15, 19, 29},
        {16},
        {17},
        {6,  22},
        {7,  23},
        {8,  20, 24, 30},
        {9,  21, 25, 31},
        {10, 22, 26, 32},
        {11, 23},
        {12, 24},
        {15, 29},
        {16},
        {17, 27},
        {22, 32},
        {23},
        {24, 30}
};

std::vector<std::pair<int, int>> Game::fieldMap = enumerateField();
std::vector<std::vector<int>> Game::pagodaCoeffs = {{-10, -10, -1, 0, -1, -10, -10},
                                                    {-10, -10, 1,  2, 1,  -10, -10},
                                                    {-1,  1,   0,  0, 0,  1,   -1},
                                                    {0,   2,   0,  2, 0,  2,   0},
                                                    {-1,  1,   0,  0, 0,  1,   -1},
                                                    {-10, -10, 1,  2, 1,  -10, -10},
                                                    {-10, -10, -1, 0, -1, -10, -10}};

int Game::finitePagoda = 0;

Game::Game() {
    finiteState[3][3] = true;
};

Field Game::getInitialField() {
    Field res{};
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            if (!(i > 1 && i < 5) && (j < 2 || j > 4)) {
                continue;
            }
            res[i][j] = true;
        }
    }
    res[3][3] = false;
    return res;
}

void Game::solve() {
    Field f = getInitialField();
    finitePagoda = computePagoda(finiteState);
    moveHistory.push_back({f, {0, 0, 'e'}});
    //printField(f);
    if (!backtracking(1)) {
        std::cout << "Something went wrong" << std::endl;
        return;
    }
    moveHistory.pop_front();
    printNumeratedField();
    for (auto state: moveHistory) {
        std::cout << std::get<0>(state.second) << " => " << std::get<1>(state.second) << std::endl;
    }
}

void Game::printField(Field f) {
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            if (!(i > 1 && i < 5) && (j < 2 || j > 4)) {
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

void Game::printNumeratedField() {
    int x = 0;
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            if (!(i > 1 && i < 5) && (j < 2 || j > 4)) {
                printf("    ");
                continue;
            }
            printf(" %2d ", x++);
        }
        std::cout << std::endl;
    }
}

std::vector<std::pair<Field, std::tuple<int, int, char>>> Game::getAvailableMoves(Field f) {
    //auto cmp = [](Field left, Field right) { return h(left) > h(right); };
    std::vector<std::pair<Field, std::tuple<int, int, char>>> res{};

    for (int blankPosition: getBlankPositions(f)) {
        int i = fieldMap[blankPosition].first, j = fieldMap[blankPosition].second;
        for (int movePosition: possibleMoves[blankPosition]) {
            int fi = fieldMap[movePosition].first, fj = fieldMap[movePosition].second;
            Field newState{};
            std::copy(f.begin(), f.end(), newState.begin());
            newState[fi][fj] = false;
            newState[i][j] = true;
            if (movePosition == blankPosition - 2) {
                if (f[i][j - 1] && f[i][j - 2]) {
                    newState[fi][fj + 1] = false;
                    res.push_back({newState, {movePosition, blankPosition, 'r'}});
                }
                continue;
            }
            if (movePosition == blankPosition + 2) {
                if (f[i][j + 1] && f[i][j + 2]) {
                    newState[fi][fj - 1] = false;
                    res.push_back({newState, {movePosition, blankPosition, 'l'}});
                }
                continue;
            }
            if (movePosition < blankPosition) {
                if (f[i - 1][j] && f[i - 2][j]) {
                    newState[fi + 1][fj] = false;
                    res.push_back({newState, {movePosition, blankPosition, 'd'}});
                }
                continue;
            }
            if (movePosition > blankPosition) {
                if (f[i + 1][j] && f[i + 2][j]) {
                    newState[fi - 1][fj] = false;
                    res.push_back({newState, {movePosition, blankPosition, 'u'}});
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
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            if (!(i > 1 && i < 5) && (j < 2 || j > 4)) {
                continue;
            }
            if (!f[i][j]) {
                res.push_back(pos);
            }
            pos++;
        }
    }
    return res;
}

std::vector<std::pair<int, int>> Game::enumerateField() {
    std::vector<std::pair<int, int>> res{};
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            if (!(i > 1 && i < 5) && (j < 2 || j > 4)) {
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
    if (isFinish(state)) {
        return true;
    }
    auto moves = getAvailableMoves(state);
    std::sort(moves.begin(), moves.end(), less_than_key());
    // У нас нет ходов, или у нас конфликт с функцией пагоды, или у нас не осталось фишек класса центральной
    if (moves.empty() || computePagoda(state) < finitePagoda ||
        !(state[3][3] || state[1][3] || state[3][1] || state[3][5] || state[5][3])) {
        return false;
    }
    for (auto move: moves) {
        long long hash = hashField(move.first);
        if (failedStates.find(hash) != failedStates.end()) {
//            std::cout << "collision" << std::endl;
            return false;
        }
        moveHistory.emplace_back(move);
        if (!backtracking(counter + 1)) {
            failedStates.insert(hashField(moveHistory.back().first));
            moveHistory.pop_back();
        } else {
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
    Field newState{};
    std::copy(state.begin(), state.end(), newState.begin());
    newState[fromI][fromJ] = false;
    if (direction == 'l') {
        newState[fromI][fromJ - 1] = false;
    } else if (direction == 'r') {
        newState[fromI][fromJ + 1] = false;
    } else if (direction == 'u') {
        newState[fromI - 1][fromJ] = false;
    } else if (direction == 'd') {
        newState[fromI + 1][fromJ] = false;
    }
    newState[toI][toJ] = true;
    return newState;
}

bool Game::isFinish(Field f) {
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            if (f[i][j] != finiteState[i][j]) {
                return false;
            }
        }
    }
    return true;
}

int Game::getPositionNumber(std::pair<int, int> coordinates) {
    for (int i = 0; i < fieldMap.size(); i++) {
        if (fieldMap[i] == coordinates) {
            return i;
        }
    }
    return -1;
}

long long Game::hashField(Field f) {
    long long res = 0;
    int shift = 0;
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            if (!(i > 1 && i < 5) && (j < 2 || j > 4)) {
                continue;
            }
            res += (f[i][j] ? 1LL : 0LL) << shift;
            shift++;
        }
    }
    return res;
}

int Game::h(Field f) {
    int res = 0;
    // corners
    res += f[0][2] + f[0][4] + f[2][0] + f[4][0] + f[2][6] + f[4][6] + f[6][2] + f[6][4];
    // Merson regions
//    res += (f[1][3] && f[2][3]) + (f[3][1] && f[3][2]) + (f[5][1] && f[5][2]) + (f[6][3] && f[7][3]) +
//           (f[6][5] && f[7][5]) + (f[5][6] && f[5][7]) + (f[3][6] && f[3][7]) + (f[1][5] && f[2][5]) +
//           (f[3][3] && f[3][4] && f[4][3] && f[4][4]);

    return res;
}

int Game::computePagoda(Field f) {
    int res = 0;
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            if (!(i > 1 && i < 5) && (j < 2 || j > 4)) {
                continue;
            }
            res += (f[i][j] ? pagodaCoeffs[i][j] : 0);
        }
    }
    return res;
}
