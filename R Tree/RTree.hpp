#ifndef SJTU_RTREE_HPP
#define SJTU_RTREE_HPP

#include "RTreeCommon.hpp"
#include "RTreeNode.hpp"

namespace sjtu{

template<size_t M, size_t D>
class RTree{
private:
	RTreeNode *root;
	RTreeNode* Find_Leaf(HyperPoint *p, RTreeNode *t);
public:
	RTree();
	bool insert(const HyperPoint<M> &rhs);
	bool remove(const HyperPoint<M> &rhs);
	std::vector<HyperPoint<M> > getPointSet(const HyperRectangle<M> &rhs);

};

#include "source/RTree.cpp"

}

#endif
