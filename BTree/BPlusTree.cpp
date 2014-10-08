#include <exception>
#include "BPlusTree.h"

BPlusTree::BPlusTree() {
    this->root = nullptr;
}

BPlusTree::BPlusTree(const BPlusTree& orig) : root(nullptr) {
    BTreeNode *tp = orig.root;
    while (!tp->isLeaf) {
        tp = tp->children.begin()->child;
    }
    while (tp) {
        for(ListNode* lp = tp->children.begin(); lp; lp = lp->next) {
            insert(lp->index);
        }
        tp = tp->rbro;
    }
}

BPlusTree::BPlusTree(BPlusTree&& orig) : root(nullptr) {
    this->root = std::move(orig.root);
}

BPlusTree& BPlusTree::operator=(const BPlusTree& rv) {
    if (&rv != this) {
        this->removeNode(root);

        BTreeNode *tp = rv.root;
        while (!tp->isLeaf) {
            tp = tp->children.begin()->child;
        }
        while (tp) {
            for(ListNode* lp = tp->children.begin(); lp; lp = lp->next) {
                insert(lp->index);
            }
            tp = tp->rbro;
        }
    }
    return *this;
}

BPlusTree& BPlusTree::operator=(BPlusTree&& rv) {
    std::swap(rv.root, this->root);
    return *this;
}

void BPlusTree::removeNode(BTreeNode* node) {
    if (!node) {
        throw new std::exception(); // вообще говоря, такого быть не должно
    }
    
    if (!node->isLeaf) {
        for(ListNode* lp = node->children.begin(); lp; lp = lp->next) {
            removeNode(lp->child);
        }
    } else {
        delete node;
    }
}

BPlusTree::~BPlusTree() {
    if (!root) {
        return;
    }
    removeNode(root);
}

void BPlusTree::insert(DataType val) {
    if (!root) {
        root = new BTreeNode();
    }

    // searching a place for insert
    BTreeNode *tp = root;
    bool f = true;
    while (!tp->isLeaf) {
        f = false;
        for(ListNode* lp = tp->children.begin(); lp; lp = lp->next) {
            if (lp->index > val) {
                tp = lp->child;
                f = true;
                break;
            }
        }
        if (!f) {
            // right node (max)
            while (!tp->isLeaf) {
                tp = tp->children.end()->child;
            }
        }
    }
    
    if(!f) {
        //fixing delegates
        int tmp = tp->max();
        ListNode *d = tp->parent->children.find( tp->max() );
        tp->children.insert(val);
        while (d && d->child->parent && d->index == d->child->parent->max()) {
            d->index = val;
            d = d->child->parent->children.find( tmp );
        }
    } else {
        tp->children.insert(val);
    }
    
    
    // if D keys are in this Node then split Node
    if (tp->children.getLength() >= D) {
        split(tp);
    }
}

void BPlusTree::split(BTreeNode* node) {
    DataType m = node->max();
    
    // new right Node
    BTreeNode *bro = new BTreeNode();
    bro->parent = node->parent;
    bro->lbro = node;
    bro->rbro = node->rbro;
    bro->isLeaf = node->isLeaf;
    node->rbro = bro;
    
    // splitting
    ListNode *lp = node->children.begin();
    int len1 = node->keysCount()/2;
    int len2 = node->keysCount() - len1;
    for(int i = 0; i < len1; i++) {
        lp = lp->next;
    }
    node->children.setLength( len1 );
    bro->children.setLength( len2 );
    bro->children.setBegin( lp );
    bro->children.setEnd( node->children.end() );
    node->children.setEnd( lp->prev );
    lp->prev->next = nullptr;
    lp->prev = nullptr;
    
    // fixing of delegates
    if (node == root) {
        BTreeNode *tp = new BTreeNode();
        tp->isLeaf = false;
        tp->children.insert( node->max(), node );
        tp->children.insert( bro->max(), bro );
        root = tp;
        node->parent = root;
        bro->parent = root;
    } else {
        ListNode *par = node->parent->children.find( m );
        par->child = bro;
        node->parent->children.insert( node->max(), node );
    }
}

BTreeNode::BTreeNode() {
    this->lbro = nullptr;
    this->rbro = nullptr;
    this->parent = nullptr;
    this->isLeaf = true;
}

BTreeNode::BTreeNode(const BTreeNode& orig) {
    children = List(orig.children);
    lbro = orig.lbro;
    rbro = orig.rbro;
    isLeaf = orig.isLeaf;
    parent = orig.parent;
}

int BTreeNode::keysCount() {
    return children.getLength();
}

void BPlusTree::fuse(BTreeNode* node1, BTreeNode* node2) {
    if (node1->rbro != node2) {
        // node1 and node2 should be neighbours
        throw new std::exception();
    }
    
    node1->parent->children.remove(node1->max());
    for(ListNode *lp = node1->children.begin(); lp; lp = lp->next) {
        node2->children.insert(lp->index, lp->child);
    }
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
    if (tp->children.getLength() <= D*A) {
        if (tp->lbro && tp->lbro->children.getLength() > D*A+1) {
            share(tp, tp->lbro);
        } else if (tp->rbro && tp->rbro->children.getLength() > D*A+1) {
            share(tp, tp->rbro);
        } else if (tp->lbro && tp->lbro->children.getLength() <= D*A+1) {
            fuse(tp, tp->lbro);
        } else if (tp->rbro && tp->rbro->children.getLength() <= D*A+1) {
            fuse(tp, tp->rbro);
        } else {
            for(ListNode *lp = tp->children.begin(); lp; lp = lp->next) {
                tp->parent->children.insert(lp->index, lp->child);
            }
        }
    }
}

void BPlusTree::share(BTreeNode* lnode, BTreeNode* rnode) {
    int nd1Cnt = (lnode->keysCount() + rnode->keysCount()) / 2;
    int nd2Cnt = lnode->keysCount() + rnode->keysCount() - nd1Cnt;
    ListNode *lp;
    
    if (lnode->keysCount() < rnode->keysCount()) {
        lp = lnode->children.end();
        lp->next = rnode->children.begin();
        rnode->children.begin()->prev = lp;
        for(int i = lnode->keysCount(); i < nd1Cnt; i++) {
            lp = lp->next;
        }
    } else {
        lp = rnode->children.begin();
        lp->prev = lnode->children.end();
        lnode->children.end()->next = lp;
        for(int i = lnode->keysCount(); i > nd1Cnt; i--) {
            lp = lp->prev;
        }
        lp = lp->prev;
    }
    lnode->children.setEnd(lp);
    rnode->children.setBegin(lp->next);
    lp->next->prev = nullptr;
    lp->next = nullptr;
    lnode->children.setLength(nd1Cnt);
    rnode->children.setLength(nd2Cnt);
}

void BTreeNode::draw(std::ostream& out) {
    out << "[";
    for(ListNode* lp = this->children.begin(); lp; lp = lp->next) {
        out << lp->index << (lp->next ? ',' : ']');
    }
}

void BPlusTree::draw(std::ostream& out) const {
    BTreeNode *tp = root;
    do {
        for(BTreeNode *ti = tp; ti; ti = ti->rbro) {
            ti->draw(out);
        }
        if (!tp->isLeaf) {
            out << std::endl;
        }
        tp = tp->children.begin()->child;
    } while (tp);
}

ListNode* BPlusTree::find(DataType val) {
    if (!root) {
        // tree is empty
        throw new std::exception();
    }
    
    BTreeNode *tp = root;
    bool f;
    while (!tp->isLeaf) {
        f = false;
        for(ListNode* lp = tp->children.begin(); lp; lp = lp->next) {
            if (lp->index > val) {
                tp = lp->child;
                f = true;
                break;
            }
        }
        if (!f) {
            return nullptr;
        }
    }
    
    return tp->children.find(val);
}

DataType BTreeNode::max() {
    return this->children.end()->index;
}

