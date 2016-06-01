#ifndef SJTU_RTREENODE_HPP
#define SJTU_RTREENODE_CPP

#include "RTreeCommon.hpp"

namespace sjtu{

template<size_t M, size_t D>
struct RTreeNode{
	HyperBound<M, D> box;
	void *child[M + 1], father;
	size_t level, size;

	RTreeNode();
	virtual ~RTreeNode();

	void remove(const RTreeNode<M, D> *key);
	void append(const RTreeNode<M, D> *key);

};

#include "Source/RTreeNode.cpp"

}

#endif
