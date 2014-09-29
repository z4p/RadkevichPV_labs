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
        while (i->index > val && i->next) {
            i = i->next;
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
        throw std::exception();
    }
    
    for(ListNode *i = begin; i->next; i = i->next) {
        if (i->index == val) {
            
        }
    }
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
