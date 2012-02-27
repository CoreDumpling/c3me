#include "MPApp.h"

int main(int argc, char **argv)
{
    MPApp app(argc, argv);

    /* bitmask for which players are human-controlled */
    uint32_t mask = 0;
    /* flag for whether or not multiplayer is enabled */
    char flag = 1;

    return app.exec();
}
