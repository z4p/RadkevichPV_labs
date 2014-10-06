#ifndef LIST_H
#define LIST_H

#include <iostream>
#define DataType int

/*
 * List - двусвязный список для B+деревьев
 * Вставка происходит в отсортированный список (список отсортирован всегда)
 */

class BPlusTree;
struct BTreeNode;

struct ListNode {
    ListNode *prev, *next;
    DataType index;
    BTreeNode *child;
    ListNode();
    ListNode(DataType val, BTreeNode* child);
};

class List {
public:
    List();
    List(const List& orig);
    ~List();
    
    void insert(DataType val, BTreeNode* child = nullptr);
    void remove(DataType val);
    ListNode* find(DataType val);
    int getLength() const;
    void setLength(int len);

    ListNode* begin();
    ListNode* end();
    void setBegin(ListNode* b);
    void setEnd(ListNode* e);
    
private:
    ListNode *_begin, *_end;
    int length;
};

#endif /* LIST_H */
