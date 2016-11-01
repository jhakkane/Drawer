#include <iostream>
#include "logic.h"
#include "interface.h"

using namespace std;

// SDL requires main to be of exactly this format:
int main(int argc, char *argv[])
{
    cout << "Welcome" << endl;

    Logic logic;
    Interface interface(logic);
    interface.start();

    cout << "Goodbye" << endl;
    return 0;
}
