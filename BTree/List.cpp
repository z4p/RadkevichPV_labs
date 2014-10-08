#include "List.h"
#include <exception>

List::List() {
    this->_begin = nullptr;
    this->_end = nullptr;
    this->length = 0;
}

List::List(const List& orig) {
    this->_begin = nullptr;
    this->_end = nullptr;
    this->length = 0;
    ListNode *lp = orig._begin;
    while (lp) {
        this->insert(lp->index, lp->child);
        lp = lp->next;
    }
}

List& List::operator=(List& rv) {
    if (&rv != this) {
        this->clear();
        this->_begin = nullptr;
        this->_end = nullptr;
        this->length = 0;
        ListNode *lp = rv._begin;
        while (lp) {
            this->insert(lp->index, lp->child);
            lp = lp->next;
        }
    }
    return *this;
}

List& List::operator=(List&& rv) {
    if (&rv != this) {
        this->clear();
        this->_begin = nullptr;
        this->_end = nullptr;
        this->length = 0;
        ListNode *lp = rv._begin;
        ListNode *ilp = _begin;
        while (lp) {
            std::swap(ilp, lp);
            this->insert(lp->index, lp->child);
            lp = lp->next;
        }
    }
    return *this;
}

List::~List() {
    clear();
}

void List::clear() {
    ListNode *i = _begin;
    ListNode *p;
    while (i) {
        p = i;
        i = i->next;
        delete p;
    }
    _begin = _end = nullptr;
    length = 0;    
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
        
        if (!i->next && i->index < val) {
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
    while (i && i->index < val) {
        i = i->next;
    }
    if (!i || i->index > val) {
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
    while (i && i->index < val) {
        i = i->next;
    }
    if (i->index == val) {
        return i;
    } else {
        // can't find the key <val>
        return nullptr;
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
