
#include "App.hpp"

int main ()
{
    App app {};
    int exitCode {0};

    if (app.initialize()) {
        app.run();
        exitCode = app.shutdown();
    }
    
    return exitCode;
}