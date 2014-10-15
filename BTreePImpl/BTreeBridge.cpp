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

BTreeBridge& BTreeBridge::operator=(const BTreeBridge& rv) {
    if (&rv != this) {
        delete pimpl;
        pimpl = new BPlusTree(*rv.pimpl);
    }
    return *this;
}

BTreeBridge& BTreeBridge::operator=(BTreeBridge&& rv) {
    std::swap(this->pimpl, rv.pimpl);
    return *this;
}

BTreeBridge::~BTreeBridge() {
    delete pimpl;
}
