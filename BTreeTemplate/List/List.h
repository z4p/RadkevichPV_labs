#ifndef LIST_H
#define LIST_H

#include <iostream>
#include "ListExceptions.h"

/*
 * List - двусвязный список для B+деревьев
 * Вставка происходит в отсортированный список (список отсортирован всегда)
 */

template <typename T, typename V> class List;

template<typename T, typename V>
class ListIterator {
private:
    List *currentNode;
    
public:
    ListIterator(): currentNode(nullptr) {}
    
    ListIterator(List<T, V>::ListNode *currentNode): currentNode(currentNode) {}
    
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


template <typename T, typename V>
class List {
private:
    friend Iterator;
    
    struct ListNode {
        ListNode *prev, *next;
        T index;
        V value;
        //BTreeNode *child;
        ListNode() {
            this->index = 0;
            this->value = 0;
            this->next = nullptr;
            this->prev = nullptr;
            //this->child = nullptr;
        }

        ListNode(T key, V val/*, BTreeNode* child*/) {
            this->index = key;
            this->value = val;
            this->next = nullptr;
            this->prev = nullptr;
        //     this->child = child;
        }
    };
    
    typedef ListNode Node;
    
    Node *_begin, *_end;
    int _length;
    
public:
    typedef ListIterator<T, V> Iterator;
    
    List() {
        this->_begin = nullptr;
        this->_end = nullptr;
        this->_length = 0;
    };
    
    List(const List<T,V>& orig) {
        this->_begin = nullptr;
        this->_end = nullptr;
        this->_length = 0;
        Node *lp = orig._begin;
        while (lp) {
            this->insert(lp->index/*, lp->child*/);
            lp = lp->next;
        }
    }
    
    List<T,V>& operator=(List<T,V> &rv) {
        if (&rv != this) {
            this->clear();
            this->_begin = nullptr;
            this->_end = nullptr;
            this->_length = 0;
            Node *lp = rv._begin;
            while (lp) {
                this->insert(lp->index/*, lp->child*/);
                lp = lp->next;
            }
        }
        return *this;
    }
    
    List<T,V>& operator=(List<T,V> &&rv) {
        if (&rv != this) {
            this->clear();
            std::swap(this->_begin, rv._begin);
            std::swap(this->_end, rv._end);
            this->_length = rv._length;
        }
        return *this;
    }
    
    ~List() {
        clear();
    }
    
    void clear() {
        Node *i = _begin;
        Node *p;
        while (i) {
            p = i;
            i = i->next;
            delete p;
        }
        _begin = _end = nullptr;
        _length = 0;    
    }
    
    void insert(T key, V val/*, BTreeNode* child = nullptr*/) {
        Node *lp = new Node(key, val/*, child*/);
        if (!_begin) {
            _begin = lp;
            _end = lp;
        } else {
            Node *i = _begin;
            while (i->index < key && i->next) {
                i = i->next;
            }
            if (i->index == key) {
                throw DuplicateKeyException();
            }

            if (!i->next && i->index < key) {
                // inserting at the end
                i->next = lp;
                lp->prev = i;
                lp->next = nullptr;
                _end = lp;
            } else {
                lp->next = i;
                lp->prev = i->prev;
                i->prev = i;
                if (lp->prev) {
                    lp->prev->next = lp;
                } else {
                    _begin = lp;
                }
            }
        }
        _length++;
    }

    void remove(T key) {
        if (!_begin) {
            return;
        }

        Node *i = _begin;
        while (i && i->index < key) {
            i = i->next;
            if (!i->next) break;
        }
        if (!i || i->index > key) {
            throw NotFoundException();
        }

        // if not first ListNode
        if (i->prev) {
            i->prev->next = i->next;
        } else {
            _begin = i->next;
        }

        // if not last ListNode
        if (i->next) {
            i->next->prev = i->prev;
        } else {
            _end = i->prev;
        }

        delete i;
        _length--;
    }
    
    Node* find(T key) {
        Node *i = _begin;
        while (i && i->index < key) {
            i = i->next;
            if (!i->next) break;
        }
        if (!i) throw NotFoundException();
        if (i->index == key) {
            return i;
        } else {
            throw NotFoundException();
        }
    }

    int getLength() const {
        return _length;
    }
    
    void setLength(int len) {
        _length = len;
    }

    Iterator begin() const {
        return Iterator(_begin);
    }
    
    Iterator end() {
        return Iterator(_end);
    }
    
    void setBegin(Node* b) {
        _begin = b;
    }
    
    void setEnd(Node* e) {
        _end = e;
    }
};


#endif /* LIST_H */
