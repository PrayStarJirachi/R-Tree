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
	RTreeNode<M, D> *father;
	HyperRectangle<D> box[M];
	size_t size, level;

};

#include "Source/RTreeNode.cpp"

}

#endif
