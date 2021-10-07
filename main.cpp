#include <iostream>
#include <chrono>
#include "Game.h"

int main() {
    setlocale(LC_ALL, "Russian");
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    Game g;
    std::cout << "Finding solution..." << std::endl;
    auto timerStart = high_resolution_clock::now();
    g.solve();
    auto timerEnd = high_resolution_clock::now();
    duration<double, std::milli> timeAmount = timerEnd - timerStart;
    std::cout << "Time taken: " << timeAmount.count() / 1000.0 << "s." << std::endl << std::endl;
    return 0;
}
