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
	size_t level;

};

#include "Source/RTreeNode.cpp"

}

#endif
