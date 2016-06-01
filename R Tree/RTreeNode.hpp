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
	typedef std::pair<HyperBound<D>, void *> Entry;

	Entry child[M + 1];
	size_t level, size;

};

#include "Source/RTreeNode.cpp"

}

#endif
