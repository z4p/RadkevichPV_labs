#include "List.h"
#include <exception>

List::List() {
    this->_begin = nullptr;
    this->_end = nullptr;
    this->length = 0;
}

List::List(const List& orig) {
}

List::~List() {
    ListNode *i = _begin;
    ListNode *p;
    while (i) {
        p = i;
        i = i->next;
        delete p;
    }
    _begin = _end = nullptr;
}

void List::insert(DataType val, BTreeNode* child) {
    ListNode *lp = new ListNode(val, child);
    if (!_begin) {
        _begin = lp;
        _end = lp;
    } else {
        ListNode *i = _begin;
        while (i->index < val && i->next) {
            i = i->next;
        }
    if (i->index == val) {
        // index is a unique key. If the same index exists, an exception will be thrown
        throw std::exception();
    }
        
        if (!i->next) {
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
    length++;
}

void List::remove(DataType val) {
    if (!_begin) {
        // removing from empty list
        throw std::exception();
    }
    
    ListNode *i = _begin;
    while (i->index < val && i->next) {
        i = i->next;
    }
    if (i->index >= val) {
        // can't find the key <val> to remove
        throw std::exception();
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
    length--;
}

ListNode* List::find(DataType val) {
    ListNode *i = _begin;
    while (i->index < val && i->next) {
        i = i->next;
    }
    if (i->index == val) {
        return i;
    } else {
        // can't find the key <val>
        throw std::exception();
    }
}

int List::getLength() const {
    return length;
}

void List::setLength(int len) {
    length = len;
}

void List::setBegin(ListNode* b) {
    _begin = b;
}

void List::setEnd(ListNode* e) {
    _end = e;
}

// ListNode (struct) constructors

ListNode* List::begin() {
    return _begin;
}

ListNode* List::end() {
    return _end;
}

ListNode::ListNode() {
    this->index = 0;
    this->next = nullptr;
    this->prev = nullptr;
    this->child = nullptr;
}

ListNode::ListNode(DataType val, BTreeNode* child) {
    this->index = val;
    this->next = nullptr;
    this->prev = nullptr;
    this->child = child;
}
