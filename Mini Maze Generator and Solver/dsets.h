#pragma once
#include <iostream>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class DisjointSets
{
    public:
    void addelements(int num);
    int find(int elem);
    void setunion(int a,int b);
    int size(int elem);	
    int getMaxSize();
    vector<int> theMainVector;

    private:
    
    int maxSize = -1;
};