//
// Created by niko1 on 02.10.2021.
//

#ifndef CHINESE_CHECKERS_GAME_H
#define CHINESE_CHECKERS_GAME_H

#define Field std::array<std::array<bool,9>,9>
#include <array>
#include <iostream>
#include <vector>

class Game {
    static Field finiteState;
    const static std::vector<std::vector<int>> possibleMoves;
    static std::vector<std::pair<int,int>> fieldMap;
public:
    Game();

    static Field getInitialField();

    void solve();

    static std::vector<std::pair<int,int>> enumerateField();

    static void printField(Field f);

    static std::vector<std::pair<int, int>> getAvailableMoves(Field f);

    static std::vector<std::pair<int, int>> getBlankPositions(Field f);

};


#endif //CHINESE_CHECKERS_GAME_H
