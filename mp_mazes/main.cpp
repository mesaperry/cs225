#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    SquareMaze maze = SquareMaze();
	maze.makeMaze(150, 30);
	PNG* img = maze.drawCreativeMaze();
	img->writeToFile("creative.png");
	delete img;
    return 0;
}
