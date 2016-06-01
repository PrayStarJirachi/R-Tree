#ifndef SJTU_RTREENODE_HPP
#define SJTU_RTREENODE_CPP

#include "RTreeCommon.hpp"

namespace sjtu{

template<class M, class D>
class RTree;

template<class M, class D>
class RTreeNode{
friend class RTree<M, D>;
private:
	HyperBound<M, D> box;
	void *child[M + 1], father;
	size_t level, size;

	RTreeNode();
	virtual ~RTreeNode();

};

#include "Source/RTreeNode.cpp"

}

#endif
