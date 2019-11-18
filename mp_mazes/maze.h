/* Your code here! */


#include "cs225/PNG.h"

using std::vector;
using namespace cs225;

class SquareMaze {
	public:
		SquareMaze();
        void makeMaze(int width, int height);
        bool canTravel (int x, int y, int dir) const;
        void setWall(int x, int y, int dir, bool exists);
        vector<int> solveMaze();
        PNG* drawMaze() const;
        PNG* drawMazeWithSolution();
        PNG* drawCreativeMaze();

    private:
        struct cell {
            bool right;
            bool down;
            int distance;
            int parent;
		    cell()
		        : right(false), down(false), distance(0), parent(4)
		    {
		    }
		    cell(bool right_, bool down_, int distance_, int parent_)
		        : right(right_), down(down_), distance(distance_), parent(parent_)
		    {
		    }
        };
        vector<vector<struct cell>> maze;
        int width_;
        int height_;
};
