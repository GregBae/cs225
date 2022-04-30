
#include <queue>
#include <algorithm>
#include <string>
#include <list>
#include <utility>
#include <limits>
#include <vector>

using std::unordered_map;
using std::string;
using std::pair;
using std::vector;
using std::queue;

/**
 * Returns an std::list of vertex keys that creates some shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 *
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
  std::list<std::string> path;
    vector<string> temp;
    queue<string> q;
    unordered_map<string,string> pred;
    unordered_map<string,bool> visit;
    //std::cout << 1 << std::endl;

    for (auto it = vertexMap.begin(); it != vertexMap.end(); it++){
        pair<string,string> p(it->first,"");
        pair<string,bool> v(it->first,false);
        pred.insert(p);
        visit.insert(v);
    }
    visit.at(start) = true;
    q.push(start);

    while (!q.empty()){
        //std::cout << __LINE__ << std::endl;
        string u = q.front();
        q.pop();
        auto ie = incidentEdges(u);
        for (auto it = ie.begin(); it != ie.end(); it++){
            if ((*it).get().source().key() != u && visit.at((*it).get().source().key()) == false){
                string next = (*it).get().source().key();
                q.push(next);
                pred.at(next) = u;
                visit.at(next) = true;
            }
            else if (visit.at((*it).get().dest().key()) == false){
                string next = (*it).get().dest().key();
                q.push(next);
                pred.at(next) = u;
                visit.at(next) = true;
            }
        }
    }

    string temp1 = end;
    temp.push_back(end);
    while (pred[temp1] != ""){
        //std::cout << pred[temp1] << std::endl;
        temp1 = pred[temp1];
        temp.push_back(temp1);
    }
    std::reverse(temp.begin(),temp.end());

    for (int i=0;i<(int)temp.size(); i++){
        path.push_back(temp[i]);
    }
    return path;
}
