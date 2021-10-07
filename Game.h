//
// Created by niko1 on 02.10.2021.
//

#ifndef CHINESE_CHECKERS_GAME_H
#define CHINESE_CHECKERS_GAME_H

#define Field std::array<std::array<bool,9>,9>
#include <array>
#include <iostream>
#include <vector>
#include <tuple>
#include <deque>
#include <set>
#include <map>

class Game {
    static Field finiteState;
    const static std::vector<std::vector<int>> possibleMoves;
    static std::vector<std::pair<int,int>> fieldMap;
    std::deque<std::pair<Field,std::tuple<int, int, char>>> moveHistory {};
    std::map<long long,int> failedStates{};
public:
    Game();

    /// Начально состояние поля перед игрой
    static Field getInitialField();

    void solve();

    /// Ставит в соответствие кажой координате номер ячейки
    static std::vector<std::pair<int,int>> enumerateField();

    static void printField(Field f);

    /// Все доступные на данный момент ходы ( <позиция откуда бьём> => <куда приходим> )
    static std::vector<std::tuple<int, int, char>> getAvailableMoves(Field f);

    /// Все позиции, в которых нет шарика
    static std::vector<int> getBlankPositions(Field f);

    /// Получает номер позиции по её координатам
    static int getPositionNumber(std::pair<int, int> coordinates);

    bool backtracking(int counter);

    static Field getStateAfterMove(Field state, std::tuple<int, int, char> move);

    static bool isFinish(Field f);

    static long long hashField(Field f);

    static int h(Field f);

    int ida_star(int bound);
};


#endif //CHINESE_CHECKERS_GAME_H
