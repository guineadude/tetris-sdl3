#include <iostream>
#include "game.hpp"

int main() {
    std::cout << "Starting Tetris with SDL3..." << std::endl;
    return game::run();
}
