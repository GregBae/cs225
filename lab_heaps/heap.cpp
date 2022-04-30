
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
using namespace std;

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    return 2*currentIdx;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return 2*currentIdx+1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    int parent = currentIdx/2;
    return (size_t)parent;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    if (leftChild(currentIdx)>=_elems.size())
        return false;
    return true;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    if (hasAChild(currentIdx)){
        size_t left = leftChild(currentIdx);
        size_t right = rightChild(currentIdx);
        if (right>=_elems.size()){ // only a left child exists
            return left;
        }
        else{ // both child exists
            if (higherPriority(_elems[left],_elems[right]))
                return left;
            else
                return right;
        }
    }
    return 0; // when no child exists
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
    if (!hasAChild(currentIdx)){
        return;
    }
    size_t priority = currentIdx;
    size_t left = leftChild(currentIdx);
    size_t right = rightChild(currentIdx);

    if (left < _elems.size() && higherPriority(_elems[left],_elems[priority]))
        priority = left;
    if (right < _elems.size() && higherPriority(_elems[right],_elems[priority]))
        priority = right;

    if (priority != currentIdx){
        swap(_elems[currentIdx],_elems[priority]);
        heapifyDown(priority);
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
    T min = numeric_limits<T>::min();
    _elems.push_back(min);
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    // @TODO Construct a heap using the buildHeap algorithm
    _elems = elems;
    T min = numeric_limits<T>::min();
    _elems.insert(_elems.begin(),min);
    for (size_t idx = parent(_elems.size()-1);idx>0;idx--){
        heapifyDown(idx);
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    if (empty()){
        return numeric_limits<T>::min();
    }
    T min = _elems[1];
    swap(_elems[1],_elems[_elems.size()-1]);
    _elems.pop_back();
    heapifyDown(1);
    return min;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    if (empty()){
        return numeric_limits<T>::min();
    }
    return _elems[1];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size()-1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    _elems[idx+1] = elem;

    if (higherPriority(_elems[idx+1],_elems[parent(idx+1)])){
        heapifyUp(idx+1);
    }
    else if (higherPriority(_elems[maxPriorityChild(idx+1)],_elems[idx+1])){
        heapifyDown(idx+1);
    }
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    if (_elems.size()<2)
        return true;
    return false;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
