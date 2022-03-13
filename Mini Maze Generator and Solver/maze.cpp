/* Your code here! */
#include <iostream>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <vector>
#include "maze.h"
#include <math.h>  
#include <random>
#include <map>
#include <queue>
#include "dsets.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <iostream>

using cs225::HSLAPixel;
using cs225::PNG;

using namespace std;

SquareMaze::~SquareMaze() {
	if (babySet != NULL) {
        delete babySet;
        babySet = NULL;
    }
    if (maze != NULL) { //what is this?
        delete maze;
        maze = NULL;
    }
}

void SquareMaze::makeMaze(int width, int height) {
    //Initialize, Does it take o(n)? 
    /* first == right, second == down */
    /* first == 0,· second == 1 */

    width_ = width;
    height_ = height;
    bool exists = true;
    maze = new vector<  vector<  pair<bool, bool>  >  > (height, vector<pair<bool, bool>>(width, pair<bool, bool>(true, true)));
    babySet = new DisjointSets();
    babySet->addelements(width * height);  

    while (babySet->getMaxSize() * (-1) !=  (width * height)  ) {
       // cout << "creating.. " << endl;
        int randomWidth = rand() % width_;
        int randomHeight = rand() % height_;
        int upOrLeftYouMakeTheChoice = rand() % 2;

        int firstIndex = randomHeight;
        int secondIndex = randomWidth;
        int disJointIndex = firstIndex * (width_) + (secondIndex);


        if (firstIndex == height_ - 1 || secondIndex == width_ - 1) {      //perimeter prevention
            if (firstIndex == height_ - 1 && upOrLeftYouMakeTheChoice == 1) { //if is at down
                continue;
            } else if (secondIndex == width_ - 1 && upOrLeftYouMakeTheChoice == 0) { //if is right
                continue;
            }
        }


        if (upOrLeftYouMakeTheChoice == 0) { //if right
            int firstIndexToWorkWith2 = firstIndex;
            int secondIndexToWorkWith2 = secondIndex + 1;
            int disJointIndexToWorkWith2 = firstIndexToWorkWith2 * (width_) + (secondIndexToWorkWith2);


            if (babySet->find(disJointIndex) == babySet->find(disJointIndexToWorkWith2)) { //如果有cycle
                 continue;
            } else if  (babySet->find(disJointIndex) != babySet->find(disJointIndexToWorkWith2)) {                                     
                exists = false;                                                             //没有cycle
                babySet->setunion(disJointIndex, disJointIndexToWorkWith2);
                setWall( randomWidth, randomHeight, 0, exists);
            }



        } else if (upOrLeftYouMakeTheChoice == 1) { //if down
      
            int firstIndexToWorkWith = firstIndex + 1;
            int secondIndexToWorkWith = secondIndex;
            int disJointIndexToWorkWith = firstIndexToWorkWith * (width_) + (secondIndexToWorkWith);

            if (babySet->find(disJointIndex) == babySet->find(disJointIndexToWorkWith)) { //have cycle
                // exists = true;
                // setWall( randomWidth,  randomHeight, 1, exists);
                continue;
            } else if (babySet->find(disJointIndex) != babySet->find(disJointIndexToWorkWith)) {  //NO cycle
                babySet->setunion(disJointIndex, disJointIndexToWorkWith);
                exists = false;
                setWall( randomWidth,  randomHeight, 1, exists);
            }
        }
    }
}

/** bool SquareMaze::canTravel	(	int 	x,
    int 	y,
    int 	dir 
    )		const
    This uses your representation of the maze to determine whether it is possible to travel in the given direction from the square at coordinates (x,y).
    For example, after makeMaze(2,2), the possible input coordinates will be (0,0), (0,1), (1,0), and (1,1).
    dir = 0 represents a rightward step (+1 to the x coordinate)
    dir = 1 represents a downward step (+1 to the y coordinate)
    dir = 2 represents a leftward step (-1 to the x coordinate)
    dir = 3 represents an upward step (-1 to the y coordinate)
    You can not step off of the maze or through a wall.
    This function will be very helpful in solving the maze. It will also be used by the grading program to verify that your maze is a tree that occupies the whole grid, and to verify your maze solution. So make sure that this function works!
    Parameters
    x	The x coordinate of the current cell
    y	The y coordinate of the current cell
    dir	The desired direction to move from the current cell
    Returns
    whether you can travel in the specified direction 
**/

bool SquareMaze::canTravel(int x, int y, int dir) const{
    int firstIndex = y;
    int secondIndex = x;
    if (dir == 0) { //right
        if (secondIndex == width_ - 1) {
            return false;
        } else if ((*maze)[firstIndex][secondIndex].first == true) {
            return false;
        } else {
            return true;
        }
    } else if (dir == 1) { //down   
        if (firstIndex == height_ - 1) {
            return false;
        } else if ((*maze)[firstIndex][secondIndex].second == true) {
            return false;
        } else {
            return true;
        }
    }  else if (dir == 2) { //left
        if (secondIndex == 0) {
            return false;
        } else if ((*maze)[firstIndex][secondIndex - 1].first == true) {
            return false;
        } else {
            return true;
        }
    } else if (dir == 3) { //up
        if (firstIndex == 0) {
            return false;
        } else if ((*maze)[firstIndex - 1][secondIndex].second == true) {
            return false;
        } else {
            return true;
        }
    }
    return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    //check if boundary 

    int firstIndex = y;
    int secondIndex = x;
    if (dir == 0) {
        (*maze)[firstIndex][secondIndex].first = exists;
    } else if (dir == 1) {
        (*maze)[firstIndex][secondIndex].second = exists;
    }
    
}

 //RECONSTRUCT
// dir = 0 represents a rightward step (+1 to the x coordinate)
// dir = 1 represents a downward step (+1 to the y coordinate)
// dir = 2 represents a leftward step (-1 to the x coordinate)
// dir = 3 represents an upward step (-1 to the y coordinate)

vector<int> SquareMaze::reConstruct(map<pair<int, int>, pair<int, int>> & theMap, vector<int> bestDistance) {
    vector<int> toReturnFinal;
    //cout << bestDistance[0] << " is bestDistance[0]" << endl;
    pair<int, int> destination = pair<int, int>(bestDistance[0], bestDistance[1]);
         // while (destination.first != 0 || destination.second != 0) {   //(0.0)
            //auto dest = theMap.at(destination);
        int i = 0;
        //while (theMap[destination].first != 413) { 
        while (i != 413) { 
            toReturnFinal.push_back(theMap[destination].first);
            if (theMap[destination].first == 0) { //left
                destination.second = destination.second - 1;
            } else if(theMap[destination].first == 1) { //up
                destination.first = destination.first - 1;
            } else if(theMap[destination].first == 2) { //right
                destination.second = destination.second + 1;
            } else if(theMap[destination].first == 3) { //down
                destination.first = destination.first + 1;
            }

            i = theMap[destination].first;
        }

        std::reverse(toReturnFinal.begin(),toReturnFinal.end());
        bestDistance_[1] = bestDistance[1];
        bestDistance_[0] = bestDistance[0];
        return toReturnFinal;
}


vector<int> SquareMaze::solveMaze() {
            vector<int> returnThis;
            vector< vector <bool> > visit (height_, vector< bool>(width_, true));
            queue<vector<int>> q;
            map<pair<int, int>, pair<int, int>> theMap;
            vector<int> bestDistance; 
            

            vector<int> tupleVector(4);
            tupleVector[0] = 0; //firstIndex
            tupleVector[1] = 0; //secondIndex
            tupleVector[2] = 413;  //direction
            tupleVector[3] = 0;//start here

            q.push(tupleVector);
            //cout << "Don't Stop Please" << endl;
            bestDistance.push_back(0);
            bestDistance.push_back(0);
            bestDistance.push_back(0);
            bestDistance.push_back(0);
            //cout << "bestDistance[3] at the begining is " << bestDistance[3] << endl;

                                   
            visit[0][0] = false;
           

            while (!q.empty()) { //why not &&
                //cout << "Round ++ " << endl;
                pair<int, int> keyInMap;
                keyInMap.first = q.front()[0]; keyInMap.second = q.front()[1]; 
                theMap[keyInMap] = pair<int, int>(q.front()[2], q.front()[3]);

                int firstIndex = q.front()[0]; int secondIndex = q.front()[1]; 
                int direction = q.front()[2]; int stepCount = q.front()[3];

                 //cout << stepCount << " is StepCount" << endl;
                 

                if (firstIndex == height_ - 1) { //determines the largest distance cell
                    if (stepCount == bestDistance[3]) {
                        if (secondIndex < bestDistance[1]) {
                        bestDistance[0] = firstIndex;
                        //cout << "bestDistance[0]" << bestDistance[0] << endl;
                        bestDistance[1] = secondIndex;
                        //cout << "bestDistance[1]" << bestDistance[1] << endl;
                        bestDistance[2] = direction;
                        //cout << "bestDistance[2]" << bestDistance[2] << endl;
                        bestDistance[3] = stepCount;
                        //cout << "bestDistance[3]" << bestDistance[3] << endl;
                        }
                        //cout << stepCount << " is StepCount" << endl;
                    }
                    if (stepCount > bestDistance[3]) {

                        // cout << "bestDistance[0]" << bestDistance[0] << endl;
                        // cout << "bestDistance[1]" << bestDistance[1] << endl;
                        // cout << "bestDistance[2]" << bestDistance[2] << endl;
                        // cout << "bestDistance[3]" << bestDistance[3] << endl;

                        bestDistance[0] = firstIndex;
                        bestDistance[1] = secondIndex;
                        bestDistance[2] = direction;
                        bestDistance[3] = stepCount;
                    }
                }

                //cout << " BestDistance[0]: " <<  bestDistance[0] << endl;
                //cout << " BestDistance[1]: " << bestDistance[1]  << endl;
                //cout << " BestDistance[2]: " << bestDistance[2] << endl;
                //cout << " BestDistance[3]: " << bestDistance[3] << endl;


                q.pop();
                //right
                if ( canTravel(secondIndex, firstIndex, 0)  == true) {
                    if (visit[firstIndex][secondIndex + 1] == true) { //never walked
                        vector<int> vect {firstIndex, secondIndex + 1, 0, stepCount + 1};
                        q.push(vect);
                        visit[firstIndex][secondIndex + 1] = false;
                    }
                }

                //1 down
                if ( canTravel(secondIndex, firstIndex, 1) == true ) {
                     if (visit[firstIndex + 1][secondIndex] == true) {
                         vector<int> vect{firstIndex + 1, secondIndex, 1,  stepCount + 1};
                         q.push( vect );
                         visit[firstIndex + 1][secondIndex] = false;
                     }
                }
                
                //2 left
                if ( canTravel(secondIndex, firstIndex, 2) == true) {
                    if (visit[firstIndex][secondIndex - 1] == true) {
                        vector<int> vect{firstIndex, secondIndex - 1, 2,  stepCount + 1};
                        q.push( vect );
                        visit[firstIndex][secondIndex - 1] = false;
                    }
                }

                //3 up
                if ( canTravel(secondIndex, firstIndex, 3) == true)  {
                    if (visit[firstIndex - 1][secondIndex] == true) {
                         vector<int> vect{firstIndex - 1, secondIndex, 3,  stepCount + 1};
                         q.push(vect);
                         visit[firstIndex - 1][secondIndex] = false;
                    }
                }

            }

            

            returnThis = reConstruct(theMap, bestDistance);
            cout << "else where" << endl;
            return returnThis;
}




PNG * SquareMaze::drawMaze() const {
    PNG * png = new PNG(width_ * 10 + 1, height_ * 10 + 1);
    
    for (int i = 0; i < height_; i++) {
        for (int j = 0; j < width_; j++) {

            if (i == 0 && j != 0) { //celling situation
                for (int draw = 0; draw < 10; draw++) {
                    png->getPixel( (j) * 10 + draw, i).l = 0;
                }
            }
             if ( j == 0) { //leftmost situation
                for (int draw1 = 0; draw1 <= 10; draw1++) {
                    png->getPixel( j , i * 10 + draw1).l = 0;
                }
            }
            
            if ((*maze)[i][j].first == true) { //if have right
                for (int draw = 0; draw <= 10; draw++) {
                //png->getPixel( j * 10 + draw , ( (i + 1) * 10) ).l = 0;
                png->getPixel( (j + 1) * 10, (i * 10) + draw).l = 0;
                }
            }
            if ((*maze)[i][j].second == true) { //if have down
                for (int draw1 = 0; draw1 <= 10; draw1++) {
                    png->getPixel( j * 10 + draw1 , ( (i + 1) * 10) ).l = 0;
                    //png->getPixel( (j + 1) * 10, (i * 10) + draw1).l = 0;
                }
            }

           
            
        }
    }
    return png;
}


// This function calls drawMaze, then solveMaze; 
// it modifies the PNG from drawMaze to show the solution vector and the exit.

// Start at pixel (5,5). 
// Each direction in the solution vector corresponds to a trail of 11 red pixels in the given direction. 
// If the first step is downward, color pixels (5,5) through (5,15) red. 
// (Red is 0,1,0.5,1 in HSLA). 
// Then if the second step is right, color pixels (5,15) through (15,15) red. 
// Then if the third step is up, color pixels (15,15) through (15,5) red. 
// Continue in this manner until you get to the end of the solution vector, 
// so that your output looks analogous the above picture.

// Make the exit by undoing the bottom wall of the destination square: 
// call the destination maze coordinates (x,y), 
// and whiten the pixels with coordinates (x*10+k, (y+1)*10) for k from 1 to 9.
// dir = 0 represents a rightward step (+1 to the x coordinate)
// dir = 1 represents a downward step (+1 to the y coordinate)
// dir = 2 represents a leftward step (-1 to the x coordinate)
// dir = 3 represents an upward step (-1 to the y coordinate)

PNG * SquareMaze::drawMazeWithSolution() {
    PNG * png = this->drawMaze();

    vector<int> path = solveMaze();
    
    int indexOne = 5;
    int indexTwo = 5;

    for (unsigned long i = 0; i < path.size(); i++) {
        int route = path[i];
        //width, height -> getPixel
        if (route == 1) { //down, (5,5) through (5,15) red. 
            for (int i = indexOne; i <= indexOne + 10; i++) {
                 png->getPixel(indexTwo, i) = HSLAPixel(0, 1, 0.5, 1);
            }
            indexOne += 10;

        } else if (route == 0) {  //right, (5,15) through (15,15)
            for (int i = indexTwo; i <= indexTwo + 10; i++) {
                png->getPixel(i, indexOne) = HSLAPixel(0, 1, 0.5, 1);
            }
            indexTwo += 10;
            
        } else if (route == 3) { //up, (15,15) through (15,5)
            for (int i = indexOne; i >= indexOne - 10; i--) {
                png->getPixel(indexTwo, i) = HSLAPixel(0, 1, 0.5, 1);
            }
            indexOne -= 10;

        } else if (route == 2) { //left (15,15) through (5,15)
            for (int i = indexTwo; i >= indexTwo - 10; i--) {
                    png->getPixel(i, indexOne) = HSLAPixel(0, 1, 0.5, 1);
                }
            indexTwo -= 10;
        }

    }

    for (int draw1 = 1; draw1 <= 9; draw1++) {
        png->getPixel( bestDistance_[1] * 10 + draw1, ( (bestDistance_[0] + 1) * 10) ).l = 1;
    }
    return png;
}
