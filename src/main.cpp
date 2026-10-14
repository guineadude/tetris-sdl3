
#include "game/Game.hpp"

int main ()
{
    Game game {};
    int exitCode {0};
    
    if (game.initialize()) {
        game.run();
        exitCode = game.shutdown();
    }
    
    return exitCode;
}