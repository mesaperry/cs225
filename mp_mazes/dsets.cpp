/* Your code here! */

#include "dsets.h"

void DisjointSets::addelements(int num) {
    for (int i = 0; i < num; i++) {
        _elems.push_back(-1);
    }
}


int DisjointSets::find(int elem) {
    if (_elems[elem] < 0) {
        return elem;
    }
    else {
        int root = find(_elems[elem]);
        _elems[elem] = root;
        return root;
    }
}


void DisjointSets::setunion(int a, int b) {
    int a_r = find(a);
    int b_r = find(b);
    if (a_r == b_r) { return; }
    if (size(a) >= size(b)) {
        _elems[a_r] += _elems[b_r];
        _elems[b_r] = a_r;
    }
    else {
        _elems[b_r] += _elems[a_r];
        _elems[a_r] = b_r;
    }
}


int DisjointSets::size(int elem) {
    return _elems[find(elem)] * -1;
}
