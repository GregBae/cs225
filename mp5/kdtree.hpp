/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

/**
 * Function returns true if a is smaller than b in the curDim dimension.
 * If the two points are the same, then will use the point < operator.
 */
template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
     if (first[curDim] < second[curDim]){
         return true;
     }
     else if (first[curDim] == second[curDim]){
         return first < second;
     }
     return false;
}

/**
 * Returns true if the potential is closer to the target than
 * the currentBest.
 */
template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     int target_d=0, curr_d=0;
     for (int i=0;i<Dim;i++){
         target_d += pow(target[i]-potential[i],2);
         curr_d += pow(currentBest[i]-target[i],2);
     }
     if (target_d < curr_d)
        return true;
     else if (target_d == curr_d){
         return potential < currentBest;
     }
     return false;
}
/**
* Builds a KD Tree and checks if the intial set of vector Points
* are empty. If it is, then initialize all the private variables
* accordingly. If it is a valid tree, then start constructing the
* tree.
*/
template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */

     points = newPoints;
     if (points.size() == 0){
         root = NULL;
         size = 0;
         return;
     }
     size = points.size();
     root = buildKDTree(0,size-1,0);
}

/**
* Helper function that will be called recrusively to construct
* each level of the KDtree that will be partitioned and selected
*/
template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::buildKDTree(int left, int right, int dim){
    KDTreeNode * curr_node = new KDTreeNode();
    int k = (left+right)/2;
    curr_node->point = quickSelect(left,right,dim,k);

    if (left!=k){
        curr_node->left = buildKDTree(left,k-1,(dim+1)%Dim);
    }
    if (right!=k){
        curr_node->right = buildKDTree(k+1,right,(dim+1)%Dim);
    }
    return curr_node;
}

/**
* Helper function that selects the median value while partitioning
* the given vector points in that current dimension. Input parameters
* are starting left index left, ending right index right, the current
* dimension dim, and the median value index k.
*/

template <int Dim>
Point<Dim> KDTree<Dim>::quickSelect(int left, int right, int dim, int k){
    if (left == right)
        return points[left];
    int pivotIndex = (left+right)/2;
    pivotIndex = partition(left,right,dim,pivotIndex);
    if (k == pivotIndex){
        return points[k];
    }
    else if (k < pivotIndex){
        return quickSelect(left,pivotIndex-1,dim,k);
    }
    else{
        return quickSelect(pivotIndex+1,right,dim,k);
    }
}

/**
* Partitions the following vector of points given a specific pivotindex
* and a dimension, along with its left starting index, and right starting
* index.
*/
template <int Dim>
int KDTree<Dim>::partition(int left, int right, int dim, int pivotIndex){
    Point<Dim> pivotVal = points[pivotIndex];
    swap(points[pivotIndex],points[right]); // move pivot to end
    int storeIndex = left;

    for (int i=left;i<right;i++){
        if (smallerDimVal(points[i],pivotVal,dim)){
            swap(points[storeIndex],points[i]);
            storeIndex++;
        }
    }
    swap(points[right],points[storeIndex]);
    return storeIndex;
}
/*
 * Copy constructor for the KDTree class.
 */
template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
   root = copy(other.root);
   size = other.size;
   points = other.points;
}

/*
 * Assigns a KDTree object as the rhs object passed in by the = operator.
 */
template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
   if (*this!= rhs){
       clear(root);
       root = copy(rhs.root);
       size = rhs.size;
       points = rhs.points;
   }
  return *this;
}
/*
 * Destructor for KDTree.
 */
template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   clear(root);
}

/**
* Helper function to destroy and delete memory on a tree recursively.
*/

template <int Dim>
void KDTree<Dim>::clear(KDTreeNode * subRoot){
    if (subRoot == NULL)
        return;
    clear(subRoot->left);
    clear(subRoot->right);
    delete subRoot;
}

/**
 * Helper function that will copy all the attributes of a tree to another tree.
 */
template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::copy(KDTreeNode * subRoot){
    if (subRoot == NULL)
        return NULL;

    KDTreeNode * newNode = new KDTreeNode(subRoot->point);
    newNode->left = copy(subRoot->left);
    newNode->right = copy(subRoot->right);
    return newNode;
}

/*
 * Function that returns the neareast possible point in a hyperrectangle. It will start
 * at the root and will call the helper function traverseKDTree and will traverse through
 * all the possible points to obtain the nearest neighbor.
 */
template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
     if (root == NULL)
        return Point<Dim>();
     Point <Dim> best_p;
     traverseKDTree(best_p,root,query,0);
     return best_p;
}

/*
 * Helper function that will determine whether the point is closer to the query point
 * based on its given dimension, and will backtrack to determine if the other subtree
 * has a closer neighbor than the current nearest neighbor
 */

template <int Dim>
void KDTree<Dim>::traverseKDTree(Point<Dim> &best_p, KDTreeNode * curr_node,
const Point<Dim>&query, int dim) const{
    if (curr_node->left == NULL && curr_node->right == NULL){
        if(shouldReplace(query,best_p,curr_node->point)){
            best_p = curr_node->point;
            return;
        }
        return;
    }
    Point<Dim>& curr_point = curr_node->point;

    if (smallerDimVal(query,curr_point,dim)){ // recurse through left subtree
        if (curr_node->left == NULL){ // if there is no left child, we dont do anything return back to parent
            return;
        }
        traverseKDTree(best_p,curr_node->left,query,(dim+1)%Dim);
        if (shouldReplace(query,best_p,curr_point)){
            best_p = curr_point;
        }
        int radius = find_radius(best_p,query);
        int split_p_dist = pow(curr_point[dim]-query[dim],2);

        if(split_p_dist<=radius && curr_node->right != NULL){
            traverseKDTree(best_p,curr_node->right,query,(dim+1)%Dim);
        }
    }
    else{ // recurse through right subtree
        if (curr_node->right == NULL){
            return;
        }
        traverseKDTree(best_p,curr_node->right,query,(dim+1)%Dim);
        if (shouldReplace(query,best_p,curr_point)){
            best_p = curr_point;
        }
        int radius = find_radius(best_p,query);
        int split_p_dist = pow(curr_point[dim]-query[dim],2);

        if (split_p_dist<=radius && curr_node->left != NULL){
            traverseKDTree(best_p,curr_node->left,query,(dim+1)%Dim);
        }
    }
}
/*
 * Calculates the radius of two points.
 */
template <int Dim>
int KDTree<Dim>::find_radius(const Point<Dim>& point1, const Point<Dim>& point2)const{
    double radius=0;
    for (int i=0;i<Dim;i++){
        radius += pow(point1[i]-point2[i],2);
    }
    return radius;
}
