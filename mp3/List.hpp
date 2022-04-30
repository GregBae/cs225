/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1

  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return ++List<T>::ListIterator(tail_);
}

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <typename T>
List<T>::~List() {
    /// @todo Graded in MP3.1
    _destroy();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
      while (head_!=NULL){
          ListNode * temp = head_;
          head_ = head_->next;
          delete temp;
      }
      head_ = NULL;
      tail_ = NULL;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
    /// @todo Graded in MP3.1
    ListNode * temp = new ListNode(ndata);
    temp->prev = NULL;

    if (head_ == NULL && tail_ == NULL){
        head_ = temp;
        tail_ = temp;
        temp->next = NULL;
    }
    else{
        temp->next = head_;
        head_->prev = temp;
        head_ = temp;
    }

    length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
    /// @todo Graded in MP3.1
    ListNode * temp = new ListNode(ndata);
    temp->next = NULL;

    if (head_ == NULL && tail_ == NULL){
        head_ = temp;
        tail_ = temp;
        temp->prev = NULL;
    }
    else{
        temp->prev = tail_;
        tail_->next = temp;
        tail_ = temp;
    }

    length_++;
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}


/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
    /// @todo Graded in MP3.1
    ListNode * prev = startPoint->prev;
    ListNode * curr = startPoint;
    ListNode * next = startPoint->next;

    while (next != NULL){
        swap(curr->prev, curr->next);

        prev = curr;
        curr = next;
        next = curr->next;

    }

    swap(curr->prev, curr->next);
    swap(startPoint,endPoint);

    prev = NULL;
    curr = NULL;
    next = NULL;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
    /// @todo Graded in MP3.1
    if (n <= 1){
        return;
    }

    if (n>1 && n<length_){
        vector <ListNode*> heads;
        vector <ListNode*> tails;

        ListNode * curr_s = head_;

        bool flag = false;
        while (curr_s->next != NULL){
            ListNode * curr_e = curr_s;
            int count = 1;
            heads.push_back(curr_s);
            while (count < n){
                curr_e = curr_e->next;
                count++;
                if (curr_e->next == NULL) {
                    flag = true;
                    break;
                }
            }

            tails.push_back(curr_e);

            if(flag)
                break;

            curr_s = curr_e->next;
        }

        for (unsigned long i=0;i<heads.size();i++){
            heads[i]->prev = NULL;
            tails[i]->next = NULL;
            reverse(heads[i],tails[i]);
        }

        head_ = heads[0];
        tail_ = tails[tails.size()-1];

        for (unsigned long i=0;i<heads.size()-1;i++){
            tails[i]->next = heads[i+1];
            heads[i+1]->prev = tails[i];
        }

    }
    else{
        reverse();
    }

}


/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail_. This continues
 * until the next thing to be removed is either the tail_ (**not necessarily
 * the original tail_!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail_ should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
    /// @todo Graded in MP3.1

    if (length_ < 3) return;

    ListNode * curr = head_;
    ListNode * rem_ = curr->next;

    //check if list is 0 or 1

    while (rem_ != tail_){
        ListNode * temp = rem_->next;
        rem_->prev = tail_;
        rem_->next = tail_->next;
        curr->next = temp;
        temp->prev = curr;
        tail_->next = rem_;

        tail_ = rem_;
        curr = curr->next;
        rem_ = curr->next;
    }

}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <typename T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondhead_ = split(head_, splitPoint);

    int oldLength = length_;
    if (secondhead_ == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondhead_;
    ret.tail_ = secondhead_;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
    /// @todo Graded in MP3.2
    if (length_ == splitPoint){
        return NULL;
    }

    ListNode * newHead;
    ListNode * curr = start;

    for (int i=1;i<splitPoint;i++){
        curr = curr->next;
    }

    newHead = curr->next;
    curr->next = NULL;

    return newHead;

}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
    /// @todo Graded in MP3.2
    ListNode * sec_ptr = second;
    ListNode * fir_ptr = first;
    ListNode * ret_node = first;
    if (first == NULL && second == NULL ) return NULL;
    if (first != NULL && second == NULL ) return first;
    if (first == NULL && second != NULL ) return second;

    while (fir_ptr != NULL && sec_ptr!=NULL){
        ListNode * temp;
        if (sec_ptr->data < fir_ptr->data){ //When second one smaller than first
            if (fir_ptr == first){
                ret_node = second;
            }
            temp = sec_ptr->next;
            sec_ptr->prev = fir_ptr->prev;
            if (fir_ptr->prev != NULL)
                fir_ptr->prev->next = sec_ptr;
            fir_ptr->prev = sec_ptr;
            sec_ptr->next = fir_ptr;
            sec_ptr = temp;
            if (sec_ptr != NULL)
                sec_ptr->prev = NULL;
        }
        else if (fir_ptr->next == NULL && (fir_ptr->data < sec_ptr->data
            || fir_ptr->data == sec_ptr->data)){
            fir_ptr->next = sec_ptr;
            sec_ptr->prev = fir_ptr;
            temp = sec_ptr->next;
            sec_ptr->next = NULL;
            sec_ptr = temp;
            if (sec_ptr != NULL)
                sec_ptr->prev = NULL;
            fir_ptr = fir_ptr->next;
        }
        else{
            fir_ptr = fir_ptr->next;
        }
    }


    return ret_node;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <typename T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
    /// @todo Graded in MP3.2
    if (chainLength == 1){
        return start;
    }

    ListNode * l1 = start;
    ListNode * l2 = l1;
    for (int i=0; i<chainLength/2;i++){
        l2 = l2->next;
    }
    l2->prev->next = NULL;
    l2->prev = NULL;
    l1 = mergesort(l1,chainLength/2);
    l2 = mergesort(l2,chainLength-chainLength/2);

    return merge(l1,l2);
}
