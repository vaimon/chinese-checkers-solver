//
// Created by niko1 on 02.10.2021.
//

#ifndef CHINESE_CHECKERS_GAME_H
#define CHINESE_CHECKERS_GAME_H

#define GameField std::array<std::array<bool,9>,9>
#define VerticalField std::array<std::array<bool*,3>,9>
#define HorizontalField std::array<std::array<bool*,9>,3>

#include <array>
#include <iostream>
#include <cstdio>
#include <vector>

class Game {
    GameField finiteState {};
public:
    Game();

    static GameField getInitialField();

    void solve();

    static std::pair<std::array<std::array<bool*,9>,3>,std::array<std::array<bool*,3>,9>> getWalkingMatrices(GameField& f);

    static void printField(GameField f);

    static void printWalkingMatrices(std::array<std::array<bool*,9>,3> horizontal,std::array<std::array<bool*,3>,9> vertical);

    static std::vector<std::pair<int,int>> getAvailableMoves(GameField& f);

    static bool checkUp(GameField& f, int i, int j);

    static bool checkDown(GameField& f, int i, int j);

    static bool checkRight(GameField& f, int i, int j);

    static bool checkLeft(GameField& f, int i, int j);
};


#endif //CHINESE_CHECKERS_GAME_H
