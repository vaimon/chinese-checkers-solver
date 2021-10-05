//
// Created by niko1 on 02.10.2021.
//

#ifndef CHINESE_CHECKERS_GAME_H
#define CHINESE_CHECKERS_GAME_H

#define Field std::array<std::array<bool,9>,9>
#include <array>
#include <iostream>

class Game {
    Field finiteState {};
    std::array<std::array<bool*,9>,3> horizontal {};
    std::array<std::array<bool*,3>,9> vertical {};
public:
    Game();

    static Field getInitialField();

    void solve();

    void printField(Field f);
};


#endif //CHINESE_CHECKERS_GAME_H
