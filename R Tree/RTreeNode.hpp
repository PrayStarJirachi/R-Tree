#ifndef SJTU_RTREENODE_HPP
#define SJTU_RTREENODE_CPP

namespace sjtu{

template<class M, class D>
class RTree;

template<class M, class D>
class RTreeNode{
friend class RTree<M, D>;
private:
	void *child[M];
	RTreeNode *father;
	HyperRectangle box[D];
	size_t level;

};

#include "Source/RTreeNode.cpp"

}

#endif
