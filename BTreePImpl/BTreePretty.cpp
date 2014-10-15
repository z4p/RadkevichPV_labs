#include "BTreePretty.h"

BTreePretty::BTreePretty() {}

BTreePretty::BTreePretty(const BTreePretty& orig) : BTreeConsole(orig) {}

BTreePretty::BTreePretty(const BTreePretty&& orig) : BTreeConsole(orig) {}

BTreePretty& BTreePretty::operator=(const BTreePretty& rv) {}

BTreePretty& BTreePretty::operator=(const BTreePretty&& rv) {}

BTreePretty::~BTreePretty() {
}

void BTreePretty::drawNode(BTreeNode& node, std::ostream& out) {
    out << "[- ";
    for(ListNode* lp = node.children.begin(); lp; lp = lp->next) {
        out << lp->index << (lp->next ? " = " : " -]");
    }
}
