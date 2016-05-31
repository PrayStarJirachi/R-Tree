#ifndef SJTU_RTREENODE_HPP
#define SJTU_RTREENODE_CPP

namespace sjtu{

template<class M, class D>
class RTree;

template<class M, class D>
class RTreeNode{
friend class RTree<M, D>;
private:
	void *child[M + 1];
	RTreeNode<M, D> *father;
	HyperRectangle<D> box[M + 1];
	size_t level;

};

#include "Source/RTreeNode.cpp"

}

#endif
