/* Your code here! */
#pragma once
#include <vector>
#include "cs225/PNG.h"
#include "dsets.h"
#include <queue>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <cstdlib>

using namespace std;
using namespace cs225;

class SquareMaze{
    public:
        SquareMaze();
        void makeMaze(int width, int height);
        bool canTravel(int x, int y, int dir) const;
        void setWall(int x, int y, int dir, bool exists);
        vector <int> solveMaze();
        PNG * drawMaze() const;
        PNG * drawMazeWithSolution();
        PNG * drawCreativeMaze();
    private:
        int height;
        int width;
        int size;
        vector<pair<pair<int,int>,int>>walls;
        vector<bool>r_wall;
        vector<bool>d_wall;
};
