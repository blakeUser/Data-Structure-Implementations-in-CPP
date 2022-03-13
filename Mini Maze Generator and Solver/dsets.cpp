#include <iostream>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <vector>
#include "dsets.h"
using namespace std;


void DisjointSets::addelements(int num) {
    for (int i = 0; i < num; i++) {
        theMainVector.push_back(-1);
    }
}

int DisjointSets::find(int elem) {
    if (theMainVector[elem] < 0) {
        return elem;
    } else {
        int root = find(theMainVector[elem]);
        theMainVector[elem] = root;
        return root;
    }
}

int DisjointSets::getMaxSize() {
    return maxSize;
}
/**
* @ To Do
Your setunion function SHOULD find the roots of its arguments before combining the trees. 
If the two sets are the same size, make the tree containing the second argument point to the tree containing the first. 
(Note that normally we could break this tie arbitrarily, but in this case we want to control things for grading.)
*/

void DisjointSets::setunion(int a, int b) {

    int indexOfA = find(a);

    int indexOfB = find(b); 

    int newSize = (theMainVector[indexOfA] + theMainVector[indexOfB]);

    if (newSize < maxSize) {
        maxSize = newSize;
    }



    if (indexOfA == indexOfB) { //if we go to the same postion, no need to calculate other things
        return;
    }

    if (theMainVector[indexOfA] == theMainVector[indexOfB]) { //if the size is the same, was considering -1, but I think it is included
        theMainVector[indexOfB] = indexOfA; //make the tree containing the second argument point to the tree containing the first. 
        theMainVector[indexOfA] = newSize;
        return;
    }

    if (theMainVector[indexOfA] < theMainVector[indexOfB]) { //a size greater than b
        theMainVector[indexOfA] = newSize;
        theMainVector[indexOfB] = indexOfA;
    }

    if (theMainVector[indexOfA] > theMainVector[indexOfB]) {
        theMainVector[indexOfB] = newSize;
        theMainVector[indexOfA] = indexOfB;
    }

    return;

}

int DisjointSets::size(int elem) {
    return -1 * theMainVector[find(elem)];
}
