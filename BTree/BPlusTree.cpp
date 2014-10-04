#include <exception>

#include "BPlusTree.h"
#include "List.h"

class List;
struct ListNode;

BPlusTree::BPlusTree() {
    this->root = nullptr;
}

BPlusTree::BPlusTree(const BPlusTree& orig) {
}

BPlusTree::~BPlusTree() {
}

void BPlusTree::insert(DataType val) {
    if (!root) {
        root = new BTreeNode();
    }
    // searching a place for insert
    BTreeNode *tp = root;
    while (!tp->isLeaf) {
        for(ListNode* lp = tp->children.begin(); lp->next; lp = lp->next) {
            if (lp->index > val) {
                tp = lp->child;
                break;
            }
        }
    }
    tp->children.insert(val);
    
    // if D keys are in this Node then split Node
    if (tp->children.Length() >= D) {
        split(tp);
    }
}

void BPlusTree::split(BTreeNode* node) {
    // new right Node
    BTreeNode *bro = new BTreeNode();
    bro->parent = node->parent;
    bro->lbro = node;
    bro->rbro = node->rbro;
    bro->isLeaf = node->isLeaf;
    node->rbro = bro;
    
    // splitting
    ListNode *lp = node->children.begin();
    for(int i = 0; i < node->children.Length()/2; i++) {
        lp = lp->next;
    }
    bro->children.setBegin( lp->next );
    bro->children.setEnd( node->children.end() );
    node->children.setEnd( lp );
    
    // fixing of delegates
    if (node == root) {
        BTreeNode *tp = new BTreeNode();
        tp->isLeaf = false;
        tp->children.insert( node->children.end()->index, node );
        tp->children.insert( 0, bro );
        root = tp;
        node->parent = root;
        bro->parent = root;
    } else {
        if (node->parent->children.Length() < D-1) {
            // todo: right node test
            node->parent->children.find( bro->children.end()->index )->child = bro;
            node->parent->children.insert( node->children.end()->index, node );
        }
    }
}

BTreeNode::BTreeNode() {
    this->lbro = nullptr;
    this->rbro = nullptr;
    this->parent = nullptr;
    this->isLeaf = true;
}

int BTreeNode::keysCount() {
    // if node is right then it has no last delegate
    return children.Length() - (rbro ? 1 : 0);
}

void BPlusTree::remove(int val) {
    if (!root) {
        // tree is empty
        throw new std::exception();
    }
    
    BTreeNode *tp = root;
    while (!tp->isLeaf) {
        for(ListNode* lp = tp->children.begin(); lp->next; lp = lp->next) {
            if (val < lp->index) {
                tp = lp->child;
                break;
            }
        }
    }
    
    tp->children.remove(val);
    // if less then A*D keys are in this Node take fuse
    if (tp->children.Length() <= D*A) {
        if (tp->lbro && tp->lbro->children.Length() > D*A+1) {
            share(tp, tp->lbro);
        } else if (tp->rbro && tp->rbro->children.Length() > D*A+1) {
            share(tp, tp->rbro);
        } else if (tp->lbro && tp->lbro->children.Length() <= D*A+1) {
            fuse(tp, tp->lbro);
        } else if (tp->rbro && tp->rbro->children.Length() <= D*A+1) {
            fuse(tp, tp->rbro);
        } else {
            // removing this node, all its childs will belong to parent
        }
    }
}

void BTreeNode::draw(std::ostream& out) {
    out << "[";
    for(ListNode* lp = this->children.begin(); lp->next; lp = lp->next) {
        out << lp->index << (lp->next ? ',' : ']');
    }
}

void BPlusTree::draw(std::ostream& out) const {
    BTreeNode *tp = root;
    do {
        for(BTreeNode *ti = tp; ti->rbro; ti = ti->rbro) {
            ti->draw(out);
        }
        out << std::endl;
        tp = tp->children.begin()->child;
    } while (!tp->isLeaf);
}
