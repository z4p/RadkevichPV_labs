#include "BTreeBridge.h"

BTreeBridge::BTreeBridge() : pimpl(nullptr) {
    pimpl = new BPlusTree();
}

BTreeBridge::BTreeBridge(const BTreeBridge& orig) : pimpl(nullptr) {
    pimpl = new BPlusTree(*orig.pimpl);
}

BTreeBridge::BTreeBridge(const BTreeBridge&& orig) : pimpl(nullptr) {
    pimpl = std::move(orig.pimpl);
}

BTreeBridge::~BTreeBridge() {
    delete pimpl;
}
