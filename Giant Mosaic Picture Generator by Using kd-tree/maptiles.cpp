/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );

}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    MosaicCanvas * toReturn = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    vector<Point<3>> vectorForThisFunction;
    for (unsigned long i = 0; i < theTiles.size(); i++) {
      vectorForThisFunction.push_back(convertToXYZ(theTiles[i].getAverageColor()));
    }
    
    KDTree<3> * treePointer = new KDTree<3>(vectorForThisFunction);
    for (int row = 0; row < toReturn->getRows(); row++) { // <=
      for (int column = 0; column < toReturn->getColumns(); column++) {

        LUVAPixel averageColor = theSource.getRegionColor(row, column);
        Point<3> searchPointToTheTree = convertToXYZ(averageColor);
        Point<3> nearestNeighbor = treePointer->findNearestNeighbor(searchPointToTheTree);
        
        //now I have a point, how to find the image by this?
        LUVAPixel loveIsGreat = LUVAPixel(nearestNeighbor[0], nearestNeighbor[1], nearestNeighbor[2]);
        for (size_t i = 0; i < theTiles.size(); i++) {
          if (loveIsGreat == theTiles[i].getAverageColor()) {
            toReturn->setTile(row, column, &theTiles[i]);
            break;
          }
        }
      }
    }
    delete treePointer;
    return toReturn;
}