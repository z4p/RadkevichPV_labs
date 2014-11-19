#ifndef LISTITERATOR_H
#define	LISTITERATOR_H

#include "List.h"

template<typename T, typename V>
class ListIterator {
private:
    ListNode<T, V> *currentNode;
public:
    ListIterator(): currentNode(nullptr) {}
    
    ListIterator(ListNode<T, V> *currentNode): currentNode(currentNode) {}
    
    ListIterator(const ListIterator& rv) {
        currentNode = rv.currentNode;
    }
    
    ListIterator<T, V>& operator=(const ListIterator<T, V>& rv) {
        currentNode = rv.currentNode;
    }
    
    ~ListIterator() {}
    
    void operator++() {
        if (currentNode->next) {
            currentNode = currentNode->next;
        }   
    }
    
    void operator--() {
        if (currentNode->prev) {
            currentNode = currentNode->prev;
        }
    }
    
    bool operator!=(const ListIterator<T, V>& rv) {
        return currentNode != rv.currentNode;
    }
    
    V operator*() {
        return currentNode->value;
    }
};

#endif	/* LISTITERATOR_H */
