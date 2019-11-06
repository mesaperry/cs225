/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] < second[curDim]) { return true; }
    else if (first[curDim] > second[curDim]) { return false; }
    else { return first < second; }
}


template <int Dim>
double KDTree<Dim>::distance(const Point<Dim>& point1,
                             const Point<Dim>& point2) const
{
    double total = 0;
    for (int i = 0; i < Dim; i++) {
        double dist = point1[i] - point2[i];
        total += dist * dist;
    }
    return total;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    if (distance(potential, target) < distance(currentBest, target)) { return true; }
    else if (distance(potential, target) > distance(currentBest, target)) { return false; }
    else { return potential < currentBest; }
}

template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& Points, int l, int r, int curDim) {
    Point<Dim> pivot = Points[r];
    int i = l-1;
    for (int j = l; j <= r-1; j++) {
        if (smallerDimVal(Points[j], pivot, curDim)) {
            i++;
            swap(Points[i], Points[j]);
        }
    }
    swap(Points[i+1], Points[r]);
    return i+1;
}

template <int Dim>
void KDTree<Dim>::placeMedian(vector<Point<Dim>>& Points, int l, int r, int median, int curDim) {
    int i = partition(Points, l, r, curDim);
    if (i > median) { placeMedian(Points, l, i-1, median, curDim); }
    else if (i < median) { placeMedian(Points, i+1, r, median, curDim); }
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::buildTree(vector<Point<Dim>>& Points, int left, int right, int curDim) {
    if (left > right) { return NULL; }
    int median = (left + right) / 2;
    placeMedian(Points, left, right, median, curDim);
    KDTreeNode* node = new KDTreeNode(Points[median]);
    node->left = buildTree(Points, left, median-1, (curDim+1)%Dim);
    node->right = buildTree(Points, median+1, right, (curDim+1)%Dim);
    return node;
}


template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints) {
    /**
     * @todo Implement this function!
     */
    if (newPoints.empty()) {
        root = NULL;
        return;
    }
    vector<Point<Dim>> Points(newPoints);
    root = buildTree(Points, 0, Points.size()-1, 0);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::buildCopy(const KDTreeNode* node) {
    if (!node) { return NULL; }
    KDTreeNode* thisNode = new KDTreeNode(node->point);
    thisNode->left = buildCopy(node->left);
    thisNode->right = buildCopy(node->right);
    return thisNode;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
    size = other.size;
    root = buildCopy(other.root);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
    if (this == &rhs) { return; }
    remove(root);
    this = new KDTree(rhs);
    return *this;
}

template <int Dim>
void KDTree<Dim>::remove(KDTreeNode* node) {
    if (!node) { return; }
    remove(node->left);
    remove(node->right);
    delete node;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
    remove(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::narrowNearest(const Point<Dim>& query, KDTreeNode* current, int curDim) const {
    if (!current) { return Point<Dim>(); }
    if (current->point == query) { return current->point; }
    
    Point<Dim> best = Point<Dim>();
    if (current->left!=NULL && smallerDimVal(query, current->point, curDim)) {
		if (current->left != NULL) {
        	best = narrowNearest(query, current->left, (curDim+1)%Dim);
		} else {
        	best = narrowNearest(query, current->right, (curDim+1)%Dim);
		}
    }
    else {
		if (current->right != NULL) {
        	best = narrowNearest(query, current->right, (curDim+1)%Dim);
		} else {
        	best = narrowNearest(query, current->left, (curDim+1)%Dim);
		}
    }

    if (shouldReplace(query, best, current->point)) { best = current->point; }
    

    double split_plane_dist = (query[curDim]-current->point[curDim])*(query[curDim]-current->point[curDim]);
    double best_dist = distance(best, query);
    if (split_plane_dist <= best_dist) {
        Point<Dim> maybe = Point<Dim>();
        if (smallerDimVal(query, current->point, curDim)) {
            maybe = narrowNearest(query, current->right, (curDim+1)%Dim);
            if (shouldReplace(query, best, maybe)) { best = maybe; }
        }
        else {
            maybe = narrowNearest(query, current->left, (curDim+1)%Dim);
            if (shouldReplace(query, best, maybe)) { best = maybe; }
        }
    }
    return best;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    return narrowNearest(query, root, 0);
}

