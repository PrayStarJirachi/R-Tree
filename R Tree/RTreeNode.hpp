#ifndef SJTU_RTREENODE_HPP
#define SJTU_RTREENODE_CPP

namespace sjtu{

template<class M, class C>
class RTree;

template<class M, class C>
class RTreeNode{
friend class RTree<M, C>;
private:
	RTreeNode *child[C], father;
};

#include "Source/RTreeNode.cpp"

}

#endif
