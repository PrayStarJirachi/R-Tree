#ifndef SJTU_RTREE_HPP
#define SJTU_RTREE_HPP

#include "RTreeCommon.hpp"
#include "RTreeNode.hpp"

namespace sjtu{

template<class T, size_t M, size_t D>
class RTree{
	
private:
	RTreeNode *root;
	RTreeNode* Find_Leaf(HyperBound<D> &key, RTreeNode *t);
	void CondenseTree(RTreeNode *t, vector<RTreeNode*> &Q);
public:
	RTree();
	bool insert(const HyperBound<D> &key, const T &value);
	bool remove(const HyperBound<D> &key);
	std::vector<HyperPoint<M> > getPointSet(const HyperBound<D> &bound);

};

#include "source/RTree.cpp"

}

#endif
