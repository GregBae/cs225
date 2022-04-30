/* Your code here! */
#pragma once
#include <vector>

using std::vector;

class DisjointSets{
    private:
        /*
        * vector of the disjoint set
        */
        vector<int>dset;
    public:
        /*
        * add num amount of unconnected root nodes to the vector dset
        */
        void addelements(int num);
        /*
        * find the rootnode of the node that has the value num
        */
        int find(int elem);
        /*
        * union two elements together, a and b are implied to be root nodes
        */
        void setunion(int a, int b);
        /*
        * return the number of nodes in the up-tree containing the element
        */
        int size(int elem);
};
