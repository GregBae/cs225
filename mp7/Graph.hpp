#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>

using std::list;
using std::string;
using std::unordered_map;
using std::pair;

/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::size() const {
    // TODO: Part 2
    return (this->vertexMap).size();
}


/**
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
    // TODO: Part 2
    if (adjList.find(v.key()) != adjList.end())
        return adjList[v.key()].size();
    return 0;
}


/**
* Inserts a Vertex into the Graph by adding it to the Vertex map and adjacency list
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
    // TODO: Part 2
    V & v = *(new V(key));
    pair<std::string,V &> node(key,v);
    vertexMap.insert(node);
    list<edgeListIter> newList;
    adjList[key] = newList;
    return v;
}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
    // TODO: Part 2
    if (vertexMap.find(key) != vertexMap.end()){
        vertexMap.erase(key);
    }
}


/**
* Inserts an Edge into the adjacency list
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
    // TODO: Part 2
    E & e = *(new E(v1, v2));
    edgeList.push_front(e);
    typename std::list<E_byRef>::iterator v1_it = edgeList.begin();
    typename std::list<E_byRef>::iterator v2_it = edgeList.begin();
    adjList[v1.key()].push_front(v1_it);
    adjList[v2.key()].push_front(v2_it);
    return e;
}


/**
* Removes an Edge from the Graph
* @param key1 The key of the ource Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2) {
    // TODO: Part 2
    if (vertexMap.find(key1) != vertexMap.end() && vertexMap.find(key2) != vertexMap.end()){
        typename std::list<edgeListIter>::iterator v1_list;
        typename std::list<edgeListIter>::iterator v2_list;
        typename std::list<E_byRef>::iterator temp_list;
        for (v1_list = adjList[key1].begin(); v1_list != adjList[key1].end();v1_list++){
            for (v2_list = adjList[key2].begin(); v2_list != adjList[key2].end();v2_list++){
                if (*v1_list == *v2_list){
                    temp_list = *v1_list;
                    adjList[key1].erase(v1_list);
                    adjList[key2].erase(v2_list);
                    break;
                }
            }
        }
        edgeList.erase(temp_list);
    }
}


/**
* Removes an Edge from the adjacency list at the location of the given iterator
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
    // TODO: Part 2
    removeEdge(*it.source().key(),*it.dest().key());
}


/**
* @param key The key of an arbitrary Vertex "v"
* @return The list edges (by reference) that are adjacent to "v"
*/
template <class V, class E>
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {
    // TODO: Part 2
    std::list<std::reference_wrapper<E>> edges;
    for (auto it = adjList.at(key).begin();it!=adjList.at(key).end();it++){
        edges.push_front(**it);
    }
    return edges;
}


/**
* Return whether the two vertices are adjacent to one another
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const {
    // TODO: Part 2
    int size_1 = adjList.at(key1).size();
    int size_2 = adjList.at(key2).size();
    int min = std::min(size_1,size_2);
    if (min == size_1){
        for (auto li = adjList.at(key1).begin(); li != adjList.at(key1).end(); li++){
            if ((**li).get().dest().key() == key2){
                return true;
            }
        }
    }
    else{
        for (auto li = adjList.at(key2).begin(); li != adjList.at(key2).end(); li++){
            if ((**li).get().source().key() == key1){
                return true;
            }
        }
    }
    return false;
}
