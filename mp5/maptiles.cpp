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
     MosaicCanvas * obj = new MosaicCanvas(theSource.getRows(),theSource.getColumns());
     map <Point<3>,int> mymap;
     vector<Point<3>> tree;
     for (unsigned i=0;i<theTiles.size();i++){
         Point<3> pt = convertToXYZ(theTiles[i].getAverageColor());
         pair<Point<3>,int> elem(pt,i);
         mymap.insert(elem);
         tree.push_back(pt);
     }

     KDTree<3> kdtree(tree);

     for (int i=0;i<theSource.getRows();i++){
         for (int j=0;j<theSource.getColumns();j++){
             LUVAPixel color = theSource.getRegionColor(i,j);
             Point<3>query = convertToXYZ(color);
             Point<3>nearestPoint = kdtree.findNearestNeighbor(query);
             map<Point<3>,int>::iterator it = mymap.find(nearestPoint);
             if (it == mymap.end()){
                 cout << "DID NOT FIND POINT" << endl;
             }
             obj->setTile(i,j,&theTiles[mymap[nearestPoint]]);
         }
     }

     return obj;
}
