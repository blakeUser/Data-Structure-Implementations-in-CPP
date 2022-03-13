/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
#include <utility>
#include <algorithm>
#include <iostream>
#include <math.h>       
using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first, const Point<Dim>& second, int curDim) const
{
     if (first[curDim] > second[curDim]) {
       return false;
     } else if (first[curDim] < second[curDim]) {
       return true;
     } else {
       return (first < second);
     }
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target, const Point<Dim>& currentBest, const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     double currentToTarget = 0.0;
     double potentialToTarget = 0.0;
     for (int i = 0; i < Dim; i++) {
       currentToTarget = currentToTarget + (target[i] - currentBest[i]) * (target[i] - currentBest[i]);
       potentialToTarget = potentialToTarget + (target[i] - potential[i]) * (target[i] - potential[i]);
     }
    currentToTarget = sqrt(currentToTarget);
    potentialToTarget = sqrt(potentialToTarget);
     if (potentialToTarget < currentToTarget) {
       return true;
     } else if (potentialToTarget > currentToTarget) {
       return false;
     } else {
       return (potential < currentBest);
     }
}

template <typename T>
void swap1(T& t1, T& t2) {
  T tmp = t1;
  t1 = t2;
  t2 = tmp;
}

template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& newPoints, int left, int right, int pivotIndex, int dimension) {
    Point<Dim> pivotValue = newPoints[pivotIndex];
    swap(newPoints[pivotIndex], newPoints[right]);
    // Point<Dim> tmp = newPoints.at(pivotIndex);
    // newPoints.at(pivotIndex) = newPoints.at(right);
    // newPoints.at(right) = tmp;
    size_t storeIndex = left;
    for (int i = left; i < right; i++) { //right or right-1
    if (smallerDimVal(newPoints[i], pivotValue, dimension)) { //newPoints[i][j] < pivotValue[j] ???
      swap (newPoints[storeIndex], newPoints[i]);
      storeIndex++;
      }
    }
    swap (newPoints[right], newPoints[storeIndex]);
    return storeIndex;
}

template <int Dim>
Point<Dim> KDTree<Dim>::select(vector<Point<Dim>>& newPoints, int left, int right, int medianIndex, int dimension) {
    if (left == right) {
      return newPoints[left];
    } 
    int pivotIndex = (left + right) / 2; //size_t pivotIndex = (left + right) / 2;   
    pivotIndex = partition(newPoints, left, right, pivotIndex, dimension);
    if (medianIndex == pivotIndex) {
      return newPoints[medianIndex];
    } else if (medianIndex < pivotIndex) {
       return select(newPoints, left, pivotIndex - 1, medianIndex, dimension); 
    } else {
       return select(newPoints, pivotIndex + 1, right, medianIndex, dimension);
    }
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>:: helpToConstruct(vector<Point<Dim>>& newPoints, int dimension, int start, int end) {
  //how to create that subroot?
  int asdf = newPoints.size();
  if (start > end) {
    return NULL;
  }
  unsigned median = (start + end) / 2;
  Point<Dim> point = select(newPoints, start, end, median, dimension);
  KDTreeNode * newNode = new KDTreeNode(point); // vector gets already sorted
  //dimension = dimension + 1;
  size++;
  newNode->left = helpToConstruct(newPoints, (dimension + 1) % Dim, start, median - 1); //what are these two for? they are the subtree of the big tree
  newNode->right = helpToConstruct(newPoints, (dimension + 1) % Dim, median + 1, end);
  return newNode;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     * @todo No Points in the vector
     * @todo The median of the vector
     * @todo If there are ties (two points have equal value along a dimension), they must be decided using Point::operator<().
     */
     if(newPoints.empty()){
       root = NULL;
       size = 0;
     } else {
      size = 0;
      int dimension = 0;
      int start = 0;
      int end = newPoints.size() - 1;
      vector<Point<Dim>> newPoint = newPoints;
      root = helpToConstruct(newPoint, dimension, start, end);
     }
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
     copy(other);
     size = other.size;
}

template <int Dim>
void KDTree<Dim>::copy(const KDTree<Dim>& other) {
  KDTreeNode * subroot = other.root;
  if (subroot== NULL) {
     return;
   } else {
     this->root = new KDTreeNode(subroot->point);
     size = other.size;
   } if (subroot->left != NULL) {
     copy(subroot->left);
   } if (subroot->right != NULL) {
     copy(subroot->right);
   }
}



template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
   if (this != rhs) {
        clear(root);
    }
    copy(rhs);
    size = rhs.size;
    return *this;
}

template <int Dim>
void KDTree<Dim>::clear(KDTreeNode *& subRoot) {
  if (subRoot == NULL)
        return;
    clear(subRoot->left);
    clear(subRoot->right);
    delete subRoot;
    subRoot = NULL;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   clear(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
     Point<Dim> query2;
     for (int i = 0; i < Dim; i++) {
       query2[i] = 987654321.1;
     }
     findHelper(0, query2, query, root);
     return query2;
}


template <int Dim>
void KDTree<Dim>::findHelper(int dimension, Point<Dim> & toReturn, Point<Dim> query, KDTreeNode * subRoot) const {
  //We get the 小弟leaf node
  bool left = false;

  if (subRoot->right == NULL && subRoot->left == NULL) {  //Eric 情况怎么办？
    toReturn = subRoot->point;
    return;
  }

  if (!smallerDimVal(subRoot->point, query, dimension) && subRoot->left != NULL) {
    left = true;
    findHelper( (dimension + 1) % Dim, toReturn, query, subRoot->left);

  } else if (smallerDimVal(subRoot->point, query, dimension) && subRoot->right != NULL) {
    findHelper( (dimension + 1) % Dim, toReturn, query, subRoot->right);
  }

  //consider the tie situation !!!!!!!!!!!!!! still not considered?
  //若被更改了，那气功墙也要有变化，气功墙的范围变化根据toReturn的变化而变化
  //若没过判定，气功墙没有任何变化。直接和splitDistance做判定

  if (shouldReplace(query, toReturn, subRoot->point)) { 
    toReturn = subRoot->point;
  } 

  //当前star的radius参考值，永远是有效状态
  double radius = 0.0;
  for (int i = 0; i < Dim; i++) {
    radius += (toReturn[i] - query[i]) * (toReturn[i] - query[i]);
  }

  //在决定是不是在气功范围内的subROOT的参考值
  double splitDistance = (subRoot->point[dimension] - query[dimension]) * (subRoot->point[dimension] - query[dimension]);

  //若挺好的并且在范围内
  if (radius >= splitDistance) {
    Point<Dim> tmp;
    for (int i = 0; i < Dim; i++) {
       tmp[i] = 987654321.1;
     }
     
    if (!smallerDimVal(subRoot->point, query, dimension) && subRoot->right != NULL) { //left is visited，如何确定左右是否被visit过尚不明确
    //if (left == true && subRoot->right != NULL) {
      findHelper( (dimension + 1) % Dim, tmp, query, subRoot->right);
    }
    if (smallerDimVal(subRoot->point, query, dimension) && subRoot->left != NULL) { //right is visited
    //if (left == false && subRoot->left != NULL) {
      findHelper( (dimension + 1) % Dim, tmp, query, subRoot->left);
    } 
    if (shouldReplace(query, toReturn, tmp) == true) {
       toReturn = tmp;
       return;
    }
    //why not when both are visited?
    
    return;
  }
  //./mosaics header.png[/class/cs225/mp5_uiuc-ig/][mymosaic.png]
  //  ./mosaics header.png [uiuc-ig/] [100] [50] [mymosaic.png]
 // ./mosaics 333.png /class/cs225/mp5_uiuc-ig/ 100 50 mymosaic.png
} 
