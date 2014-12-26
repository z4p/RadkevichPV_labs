#ifndef LISTITERATOR_H
#define	LISTITERATOR_H

template<typename T, typename V, class TNode>
class ListIterator {
private:
    TNode *currentNode;
    
public:
    ListIterator(): currentNode(nullptr) {}
    
    ListIterator(TNode *currentNode): currentNode(currentNode) {}
    
    ListIterator(const ListIterator& rv) {
        currentNode = rv.currentNode;
    }
    
    ListIterator<T, V, TNode>& operator=(const ListIterator<T, V, TNode>& rv) {
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
    
    bool operator!=(const ListIterator<T, V, TNode>& rv) {
        return currentNode != rv.currentNode;
    }
    
    V operator*() {
        return currentNode->value;
    }
};


#endif	/* LISTITERATOR_H */
