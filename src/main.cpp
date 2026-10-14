
#include "App.hpp"

int main ()
{
    App app {};
    int exitCode {};

    if (app.initialize()) {
        app.run();
        exitCode = app.shutdown();
    }
    
    return exitCode;
}