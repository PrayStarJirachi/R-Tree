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
	HyperBound<D> box;
	void *child[M + 1];
	size_t level, size;

};

//#include "Source/RTreeNode.cpp"

}

#endif
