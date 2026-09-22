#include "main.hpp"

int main(int argc, char *argv[])
{
    App app;
    int exitCode{};

    if (app.init())
    {
        exitCode = app.run();
    }

    return exitCode;
}