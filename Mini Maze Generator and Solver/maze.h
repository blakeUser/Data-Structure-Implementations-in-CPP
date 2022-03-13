#include <iostream>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include "cs225/PNG.h"
#include "dsets.h"
#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;
using cs225::PNG;
using namespace std;

class SquareMaze {



    public:
    void makeMaze (int width, int height);
    bool canTravel (int x, int y, int dir) const;
    void setWall (int x, int y, int dir, bool exists);
    vector<int> solveMaze();
    PNG * drawMaze() const;
    PNG * drawMazeWithSolution();
    ~SquareMaze();
    vector<int> reConstruct(map< pair<int, int>, pair<int, int> > & theMap, vector<int> bestDistance);
    vector< vector< pair<bool, bool> > > *  maze;
    int width_;
    int height_;
    
    private:
    
    vector<int> toReturn;
    DisjointSets * babySet;
    int bestDistance_[2];
    
    
    
};