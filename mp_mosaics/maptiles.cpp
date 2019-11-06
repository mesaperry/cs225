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
    int rows = theSource.getRows();
    int cols = theSource.getColumns();
    MosaicCanvas* c = new MosaicCanvas(rows, cols);

    vector<Point<3>> points;
    map<Point<3>, TileImage> tileHash;
    for (TileImage tile : theTiles) {
        const LUVAPixel p = tile.getAverageColor();
        Point<3> pt = Point<3>(p.l, p.u, p.v);
        points.push_back(pt);
        tileHash[pt] = tile;
    }
    KDTree<3> tileTree = KDTree<3>(points);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            const LUVAPixel pix1 = theSource.getRegionColor(i, j);
            Point<3> pt = Point<3>(pix1.l, pix1.u, pix1.v);

            Point<3> closest = tileTree.findNearestNeighbor(pt);
            TileImage* copy = new TileImage(tileHash[closest]);
            c->setTile(i, j, copy);
        }
    }

    return c;
}

