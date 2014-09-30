#include "List.h"
#include <exception>

List::List() {
    this->begin = nullptr;
    this->end = nullptr;
    this->length = 0;
}

List::List(const List& orig) {
}

List::~List() {
}

void List::insert(DataType val, BTreeNode* child) {
    ListNode *lp = new ListNode(val, child);
    if (!begin) {
        begin = lp;
        end = lp;
    } else {
        ListNode *i = begin;
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
            end = lp;
        } else {
            lp->next = i;
            lp->prev = i->prev;
            i->prev = i;
            if (lp->prev) {
                lp->prev->next = lp;
            } else {
                begin = lp;
            }
        }
    }
    length++;
}

void List::remove(DataType val) {
    if (!begin) {
        // removing from empty list
        throw std::exception();
    }
    
    ListNode *i = begin;
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
        begin = i->next;
    }
    
    // if not last ListNode
    if (i->next) {
        i->next->prev = i->prev;
    } else {
        end = i->prev;
    }
    
    delete i;
    length--;
}

ListNode* List::find(DataType val) {
    
}

int List::Length() {
    return length;
}

void List::setBegin(ListNode* b) {
    begin = b;
}

void List::setEnd(ListNode* e) {
    end = e;
}

// ListNode (struct) constructors

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
