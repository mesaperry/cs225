/* Your code here! */

#include <stdlib.h>
#include <time.h>
#include "dsets.h"
#include "maze.h"

#include <iostream>
#include <random>
#include <stack>
#include <unordered_map>

using std::stack;
using std::pair;
using std::unordered_map;
using std::cout;
using std::endl;




bool randomBool() {
  return rand() % 2 == 1;
}



SquareMaze::SquareMaze() {

}



void SquareMaze::makeMaze(int width, int height) {
	// set seeds and initialize random functions
	std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(0, 4);

    width_ = width;
    height_ = height;

    if (!maze.empty()) {
        maze.clear();
    }
    for (int i = 0; i < height; i++) {
        vector<struct cell> row;
        for (int j = 0; j < width; j++) {
            row.emplace_back(true, true, 0, 4);
        }
        maze.push_back(row);
    }
    DisjointSets dset;
    dset.addelements(width * height);

    // delete random walls
    int idx = 0;
    while (dset.size(0) < width*height) {
        int y = idx / height;
        int x = idx % height;
		int dir = distr(eng);
        if (dir==0 and x!=width-1) { // right
			if (dset.find(idx) != dset.find(idx+1)) {
		        maze[y][x].right = false;
		        dset.setunion(idx, idx+1);
			}
        }
        else if (dir==1 and y!=height-1) { // down
			if (dset.find(idx) != dset.find(idx+width_)) {
		        maze[y][x].down = false;
		        dset.setunion(idx, idx+width_);
			}
        }
        else if (dir==2 and x!=0) { // left
			if (dset.find(idx) != dset.find(idx-1)) {
		        maze[y][x-1].right = false;
		        dset.setunion(idx, idx-1);
			}
        }
        else if (dir==3 and y!=0) { // up
			if (dset.find(idx) != dset.find(idx-width_)) {
		        maze[y-1][x].down = false;
		        dset.setunion(idx, idx-width_);
			}
        }
        idx += distr(eng);
        if (idx >= width*height) { idx -= width*height; }
    }
}



bool SquareMaze::canTravel(int x, int y, int dir) const {
    if (x==0 and dir==2) { return false; }
    if (y==0 and dir==3) { return false; }
    if (x==width_-1 and dir==0) { return false; }
    if (y==height_-1 and dir==1) { return false; }

    if (dir==0 and maze[y][x].right) { return false; }
    if (dir==1 and maze[y][x].down) { return false; }
    if (dir==2 and maze[y][x-1].right) { return false; }
    if (dir==3 and maze[y-1][x].down) { return false; }

    return true;
}



void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    if (dir == 0) {
        maze[y][x].right = exists;
    }
    else {
        maze[y][x].down = exists;
    }
}



vector<int> SquareMaze::solveMaze() {
    // set distances
    stack<pair<int,int>> visit;
    unordered_map<int, bool> visited;
    visit.emplace(0,0);
    while (!visit.empty()) {
        pair<int,int> pt = visit.top();
        visit.pop();
        visited[pt.second*width_ + pt.first] = true;
        if (canTravel(pt.first, pt.second, 0)) {
            if (!visited[pt.second*width_ + pt.first+1]) {
                visit.emplace(pt.first+1,pt.second);
                maze[pt.second][pt.first+1].distance = maze[pt.second][pt.first].distance + 1;
                maze[pt.second][pt.first+1].parent = 0;
            }
        }
        if (canTravel(pt.first, pt.second, 1)) {
            if (!visited[(pt.second+1)*width_ + pt.first]) {
                visit.emplace(pt.first,pt.second+1);
                maze[pt.second+1][pt.first].distance = maze[pt.second][pt.first].distance + 1;
                maze[pt.second+1][pt.first].parent = 1;
            }
        }
        if (canTravel(pt.first, pt.second, 2)) {
            if (!visited[pt.second*width_ + pt.first-1]) {
                visit.emplace(pt.first-1,pt.second);
                maze[pt.second][pt.first-1].distance = maze[pt.second][pt.first].distance + 1;
                maze[pt.second][pt.first-1].parent = 2;
            }
        }
        if (canTravel(pt.first, pt.second, 3)) {
            if (!visited[(pt.second-1)*width_ + pt.first]) {
                visit.emplace(pt.first,pt.second-1);
                maze[pt.second-1][pt.first].distance = maze[pt.second][pt.first].distance + 1;
                maze[pt.second-1][pt.first].parent = 3;
            }
        }
    }

    // find end cell
    cell max_cell;
	max_cell.distance = 0;
    int x = 0;
    int y = height_ - 1;
    for (int idx = 0; idx < width_; idx++) {
        struct cell curr = maze[height_-1][idx];
        if (curr.distance > max_cell.distance) {
            max_cell = curr;
            x = idx;
        }
    }
    
    // record path
    stack<int> reverse;
    while (maze[y][x].distance != 0) {
        int dir = maze[y][x].parent;
        reverse.push(dir);
        if (dir == 0) { x--; }
        else if (dir == 1) { y--; }
        if (dir == 2) { x++; }
        else if (dir == 3) { y++; }
    }

    // reverse path
    vector<int> path;
    while (!reverse.empty()) {
        path.push_back(reverse.top());
        reverse.pop();
    }
    return path;
}



PNG* SquareMaze::drawMaze() const {
    PNG* img = new PNG(width_*10+1, height_*10+1);
    for (int i = 10; i < width_*10+1; i++) {
        img->getPixel(i, 0) = HSLAPixel(0,0,0,1);
    }
    for (int i = 0; i < height_*10+1; i++) {
        img->getPixel(0, i) = HSLAPixel(0,0,0,1);
    }

    for (int j = 0; j < height_; j++) {
        for (int i = 0; i < width_; i++) {
            if (maze[j][i].right) {
                for (int k = 0; k < 10; k++) {
                    img->getPixel((i+1)*10, j*10+k) = HSLAPixel(0,0,0,1);
                }
            }
            if (maze[j][i].down) {
                for (int k = 0; k < 10; k++) {
                    img->getPixel(i*10+k, (j+1)*10) = HSLAPixel(0,0,0,1);
                }
            }
        }
    }
    return img;
}



PNG* SquareMaze::drawMazeWithSolution() {
    PNG* img = drawMaze();
    vector<int> path = solveMaze();
    int x = 5;
    int y = 5;
    img->getPixel(x, y) = HSLAPixel(0,1,0.5,1);
    for (int dir: path) {
        for (int i=0; i<10; i++) {
            if (dir==0) {
                x++;
                img->getPixel(x, y) = HSLAPixel(0,1,0.5,1);
            }
            if (dir==1) {
                y++;
                img->getPixel(x, y) = HSLAPixel(0,1,0.5,1);
            }
            if (dir==2) {
                x--;
                img->getPixel(x, y) = HSLAPixel(0,1,0.5,1);
            }
            if (dir==3) {
                y--;
                img->getPixel(x, y) = HSLAPixel(0,1,0.5,1);
            }
        }
    }
    for (int k=1; k<10; k++) {
        img->getPixel(x-5+k, y+5) = HSLAPixel(0,0,1,1);
    }
    return img;
}









