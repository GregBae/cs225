#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    SquareMaze illini;
    illini.makeMaze(40,60);
    PNG * png = illini.drawCreativeMaze();
    png->writeToFile("creative.png");
    return 0;
}
