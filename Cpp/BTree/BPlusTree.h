#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include "List.h"
#include <iostream>

const int    D = 4;     // max count of elements in BTreeNode
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
    BTreeNode(const BTreeNode& orig);
    int keysCount();
    void draw(std::ostream& out);//калі ёсць паводзіны, то гэта ужо хутчэй клас, а не структура з адпаведнымі наступствамі.
    DataType max(); 
//    BTreeNode(DataType val, BTreeNode *parent = nullptr);
};

class BPlusTree {
public:
    BPlusTree();
    BPlusTree(const BPlusTree& orig);
    BPlusTree(BPlusTree&& orig);
    BPlusTree& operator=(const BPlusTree& rv);
    BPlusTree& operator=(BPlusTree&& rv);
    ~BPlusTree();
    
    void insert(DataType val);
    void remove(DataType val);
    ListNode* find(DataType val);
    void draw(std::ostream& out) const;
    
private:
    BTreeNode *root;

    void removeNode(BTreeNode* node);
    // removes node and all its children
    // IT JUST REALISE ALLOCATED MEMORY, IT DOESN'T CHANGE PARENT'S LINK
    
    void share(BTreeNode* lnode, BTreeNode* rnode); // перераспределение элементов соседних узлов
    void split(BTreeNode* node);                    // разбиение одного узла на два
    void fuse(BTreeNode* node1, BTreeNode* node2);  // объединение двух соседних узлов в один
};

#endif /* BPLUSTREE_H */
