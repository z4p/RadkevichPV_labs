#ifndef BPLUSTREE_H
#define	BPLUSTREE_H

#include "List.h"

const int    D = 6;     // max count of elements in BTreeNode
const double A = 0.5;   // A*D - min count of elements in BTreeNode

struct BTreeNode {
    BTreeNode *parent;      // ссылка на родителя
    List childs;            // список (делегат от дочернего нода (index), ссылка на него)
    BTreeNode *rchild;      // ссылка на правый дочерний нод (не делегирует ключа)
    BTreeNode *lbro, *rbro; // ссылки на левого и правого брата
    bool isLeaf;            // является ли нода листом?
    BTreeNode();
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
    
private:
    BTreeNode *root;

    void share(BTreeNode* node1, BTreeNode* node2); // перераспределение элементов соседних узлов
    void split(BTreeNode* node);                    // разбиение одного узла на два
    void fuse(BTreeNode* node1, BTreeNode* node2);  // объединение двух соседних узлов в один
};

#endif	/* BPLUSTREE_H */
