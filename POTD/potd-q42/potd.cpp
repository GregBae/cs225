#include <unordered_map>
#include <iostream>
using namespace std;

unordered_map<string, int> common_elems(unordered_map<string, int> &mapA,
                                        unordered_map<string, int> &mapB) {

    // your code here
    unordered_map<string,int> ret;
    for (auto it = mapA.begin(); it!= mapA.end(); ++it){
        if (mapB.find(it->first) != mapB.end()){
            ret[it->first] = it->second + mapB[it->first];
        }
    }

    for (auto it = ret.begin(); it!=ret.end();++it){
        mapA.erase(it->first);
        mapB.erase(it->first);
    }

    return ret;
}
