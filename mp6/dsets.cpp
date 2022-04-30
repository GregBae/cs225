/* Your code here! */
#include "dsets.h"
void DisjointSets::addelements(int num){
    for (int i=0;i<num;i++){
        this->dset.push_back(-1);
    }
}

int DisjointSets::find(int elem){
    if (dset[elem]<0){
        return elem;
    }
    else{
        int root = find(dset[elem]);
        dset[elem] = root;
        return root;
    }
}

void DisjointSets::setunion(int a, int b){
    int root_a = find(a);
    int root_b = find(b);

    int newSize = dset[root_a] + dset[root_b];

    if (dset[root_a] <= dset[root_b]){
        dset[root_b] = root_a;
        dset[root_a] = newSize;
    }
    else{
        dset[root_a] = root_b;
        dset[root_b] = newSize;
    }
}

int DisjointSets::size(int elem){
    return -1 * dset[find(elem)];
}
