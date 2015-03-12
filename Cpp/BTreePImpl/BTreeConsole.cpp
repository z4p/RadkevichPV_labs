#include "BTreeConsole.h"

BTreeConsole::BTreeConsole() : BTreeBridge() {}

BTreeConsole::BTreeConsole(const BTreeConsole& orig) : BTreeBridge(orig) {}

BTreeConsole::BTreeConsole(const BTreeConsole&& orig) : BTreeBridge(orig) {}

BTreeConsole& BTreeConsole::operator=(const BTreeConsole& rv) {}

BTreeConsole& BTreeConsole::operator=(const BTreeConsole&& rv) {}

BTreeConsole::~BTreeConsole() {}

void BTreeConsole::draw(std::ostream& out) {
    BTreeNode node;
    if (getCurrentNode(node)) do {
        drawNode(node, out);
        out << std::endl;
    } while (getCurrentNode(node));
    
}

void BTreeConsole::drawNode(BTreeNode& node, std::ostream& out) {
    out << "[";
    for(ListNode* lp = node.children.begin(); lp; lp = lp->next) {
        out << lp->index << (lp->next ? ',' : ']');
    }
}
