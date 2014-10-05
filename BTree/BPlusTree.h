#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include "List.h"
#include <iostream>

const int    D = 6;     // max count of elements in BTreeNode
const double A = 0.5;   // A*D - min count of elements in BTreeNode

struct BTreeNode {
    BTreeNode *parent;      // ссылка на родителя
    List children;          // список (делегат от дочернего нода (index), ссылка на него)
    // rchild, вообще говоря, плохая идея. Лучше просто проверять наличие rbro, и 
    // если его нет - не считать последнего делегата (отправлять по нему 
    // при поиске/обходе). Тогда максимумом для нода
    // будет D-1 ключей НЕ СЧИТАЯ ссылку на последний (Length: children.Length + (rbro ? 0:1))
    // BTreeNode *rchild;      // ссылка на правый дочерний нод (не делегирует ключа)
    BTreeNode *lbro, *rbro; // ссылки на левого и правого брата
    bool isLeaf;            // является ли нода листом?
    BTreeNode();
    int keysCount();
    void draw(std::ostream& out);
//    BTreeNode(DataType val, BTreeNode *parent = nullptr);
};

class BPlusTree {
public:
    BPlusTree();
    BPlusTree(const BPlusTree& orig);
    ~BPlusTree();
    
    void insert(DataType val);
    void remove(DataType val);
    ListNode* find(DataType val);
    void draw(std::ostream& out) const;
    
private:
    BTreeNode *root;

    void share(BTreeNode* node1, BTreeNode* node2); // перераспределение элементов соседних узлов
    void split(BTreeNode* node);                    // разбиение одного узла на два
    void fuse(BTreeNode* node1, BTreeNode* node2);  // объединение двух соседних узлов в один
};

#endif /* BPLUSTREE_H */
