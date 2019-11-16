/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = nullptr;
    tail_ = nullptr;
    length_ = 0;
}

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
  return List<T>::ListIterator(nullptr);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @TODO Graded in MP3.1
  if (size() == 0) { return; }
  ListNode *cur_ptr = head_;
  while (cur_ptr->next != nullptr) {
    cur_ptr = cur_ptr->next;
    delete cur_ptr->prev;
  }
  delete cur_ptr;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @TODO Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode->next = head_;
  newNode->prev = NULL;
  
  if (head_ != NULL) {
    head_->prev = newNode;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
  }

  head_ = newNode;

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
  /// @TODO Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode->next = NULL;
  newNode->prev = tail_;
  
  if (tail_ != NULL) {
    tail_->next = newNode;
  }
  if (head_ == NULL) {
    head_ = newNode;
  }

  tail_ = newNode;

  length_++;

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
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @TODO Graded in MP3.1
  ListNode * curr = start;

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL) {
    if (curr->prev != NULL) { curr->prev->next = NULL; }
    curr->prev = NULL;
    return curr;
  }
  return NULL;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @TODO Graded in MP3.1
  if (this->size() <= 2) { return; }
  ListNode* curr = head_;
  while (curr->next != tail_ and curr->next != NULL) {
    // remove from list
    ListNode* removed = curr->next;
    curr->next->next->prev = curr;
    curr->next = curr->next->next;
    // add to end
    removed->next = NULL;
    removed->prev = tail_;
    tail_->next = removed;
    tail_ = removed;
    //next
    curr = curr->next;
  }
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
  /// @todo Graded in MP3.2
  ListNode* oldStart = startPoint;
  ListNode* oldEnd = endPoint;
  while (startPoint != endPoint && startPoint->prev != endPoint) {
    if (startPoint->prev != NULL) { startPoint->prev->next = endPoint; }
    if (endPoint->next != NULL) { endPoint->next->prev = startPoint; }
    startPoint->next->prev = endPoint;
    endPoint->prev->next = startPoint;
    ListNode* temp1 = startPoint->prev;
    ListNode* temp2 = startPoint->next;
    startPoint->prev = endPoint->prev;
    startPoint->next = endPoint->next; //
    endPoint->prev = temp1;
    endPoint->next = temp2; //

    ListNode* temp = startPoint;
    startPoint = endPoint;
    endPoint = temp;
    startPoint = startPoint->next;
    endPoint = endPoint->prev;
  }
  startPoint = oldEnd;
  endPoint = oldStart;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
//headadad
  ListNode* startNode = this->head_;
  ListNode* endNode = this->head_;
  while (endNode->next != NULL) {
    for (int i = 0; i < n-1; i++) {
      if (endNode->next == NULL) { break; }
      endNode = endNode->next;
    }
    reverse(startNode, endNode);
    endNode = endNode->next;
    startNode = endNode;
  }
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
  ListNode* curr_head;
  if (first->data < second->data) {
    curr_head = first;
    first->prev = NULL;
    first = first->next;
  }
  else {
    curr_head = second;
    second->prev = NULL;
    second = second->next;
  }
  ListNode* head = curr_head;
  while (first != NULL && second != NULL) {
    if (first->data < second->data) {
      curr_head->next = first;
      first->prev = curr_head;
      curr_head = curr_head->next;
      first = first->next;
    }
    else {
      curr_head->next = second;
      second->prev = curr_head;
      curr_head = curr_head->next;
      second = second->next;
    }
    if (first == NULL) {
      curr_head->next = second;
      second->prev = curr_head;
    }
    else if (second == NULL) {
      curr_head->next = first;
      first->prev = curr_head;
    }
  }
  return head;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (chainLength > 1) {
    int half = chainLength / 2;
    int remain = chainLength % 2;
    ListNode* first = start;
    ListNode* second = start;
    for (int i = 0; i < half+remain; i++) {
      second = second->next;
    }
    first = mergesort(first, half);
    second = mergesort(second, half+remain);

    return merge(first, second);
  }
  return this->head_;
}






