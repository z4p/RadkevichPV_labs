#include <exception>

#include "BPlusTree.h"
#include "List.h"

BPlusTree::BPlusTree() {
    this->root = nullptr;
}

BPlusTree::BPlusTree(const BPlusTree& orig) {
}

BPlusTree::~BPlusTree() {
}

BPlusTree::insert(DataType val) {
    if (!root) {
        root = new BTreeNode();
    }
    
    // searching place for insert
    BTreeNode *tp = root;
    
    while (!tp->isLeaf) {
        for(ListNode* lp = tp->childs.begin(); lp = lp->next; lp->next != nullptr) {
            if (lp->index > val) {
                tp = lp->child;
                break;
            }
        }
    }
    
    tp->childs.insert(val);
    
    // if D keys are in this Node then split Node
    if (tp->childs.Length() >= D) {
        split(tp);
    }
}

BPlusTree::split(BTreeNode* node) {
    // new right Node
    BTreeNode *bro = new BTreeNode();
    bro->parent = node->parent;
    bro->lbro = node;
    bro->rbro = node->rbro;
    bro->isLeaf = node->isLeaf;
    node->rbro = bro;
    
    // splitting
    ListNode lp = node->childs.begin();
    for(int i = 0; i < node->childs.Length()/2; i++) {
        lp = lp->next;
    }
    bro->childs.setBegin( lp->next );
    bro->childs.setEnd( node->childs.end() );
    node->childs.setEnd( lp );
    
    // fixing of delegates
    if (node == root) {
        BTreeNode tp = new BTreeNode();
        tp->isLeaf = false;
        tp->rchild = bro;
        tp->childs.insert( node->childs.end()->index, node);
        root = tp;
        node->parent = root;
        bro->parent = root;
    } else {
        if (node->parent->childs.Length() < D-1) {
            // todo: right node test
            node->parent->childs.find( bro->childs.end()->index )->child = bro;
            node->parent->childs.insert( node->childs.end()->index, node );
        }
    }
}

BTreeNode::BTreeNode() {
    this->lbro = nullptr;
    this->rbro = nullptr;
    this->parent = nullptr;
    this->isLeaf = true;
    this->rchild = nullptr;
}

void BPlusTree::remove(int val) {
    if (!root) {
        // tree is empty
        throw new std::exception();
    }
    
    BTreeNode *tp = root;
    while (!tp->isLeaf) {
        for(ListNode* lp = tp->childs.begin(); lp = lp->next; lp->next != nullptr) {
            if (val < lp->index) {
                tp = lp->child;
                break;
            }
        }
    }
    
    tp->childs.remove(val);
    // if less then A*D keys are in this Node take fuse
    if (tp->childs.Length() <= D*A) {
        if (tp->lbro && tp->lbro->childs.Length() > D*A+1) {
            share(tp, tp->lbro);
        } else if (tp->rbro && tp->rbro->childs.Length() > D*A+1) {
            share(tp, tp->rbro);
        } else if (tp->lbro && tp->lbro->childs.Length() <= D*A+1) {
            fuse(tp, tp->lbro);
        } else if (tp->rbro && tp->rbro->childs.Length() <= D*A+1) {
            fuse(tp, tp->rbro);
        } else {
            // removing this node, all its childs will belong to parent
        }
    }
}
