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

class Game {
    static Field finiteState;
    const static std::vector<std::vector<int>> possibleMoves;
    static std::vector<std::pair<int,int>> fieldMap;
    std::deque<std::pair<Field,std::tuple<int, int, char>>> moveHistory {};
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
    static int getPositionNumber(std::pair<int, int> coordinates){
        for(int i = 0; i < fieldMap.size(); i ++){
            if(fieldMap[i] == coordinates){
                return i;
            }
        }
        return -1;
    }

    bool backtracking();

    static Field getStateAfterMove(Field state, std::tuple<int, int, char> move);

    static bool isFinish(Field f);
};


#endif //CHINESE_CHECKERS_GAME_H
