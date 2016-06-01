#ifndef SJTU_RTREE_HPP
#define SJTU_RTREE_HPP

#include "RTreeCommon.hpp"
#include "RTreeNode.hpp"

namespace sjtu{

template<class T, size_t M, size_t D>
class RTree{
private:
	RTreeNode<T, M, D> *root;

	void __clear(RTreeNode<T, M, D> *now);
	void __find(const RTreeNode<T, M, D> * const now, const HyperBound<D> &bound, std::vector<T> &storge)const;
	RTreeNode<T, M, D> * splitNode(RTreeNode<T, M, D> *now);
	RTreeNode<T, M, D> * Find_Leaf(HyperBound<D> &key, RTreeNode<T, M, D> *t);
	void CondenseTree(RTreeNode<T, M, D> *t, std::vector<RTreeNode<T, M, D> *> &Q);
	RTreeNode<T, M, D> * chooseLeaf(const HyperBound<D> &key, const T &value);
	void adjust(RTreeNode<T, M, D> *u, RTreeNode<T, M, D> *brother);
	void pickSeeds(RTreeNode<T, M, D> *u, RTreeNode<T, M, D> *t0, RTreeNode<T, M, D> *t1);
	void pickNext(RTreeNode<T, M, D> *u, RTreeNode<T, M, D> *t0, RTreeNode<T, M, D> *t1);

public:
	RTree();
	void insert(const HyperBound<D> &key, const T &value);
	bool remove(const HyperBound<D> &key);
	std::vector<T> getPointSet(const HyperBound<D> &bound)const;

	virtual ~RTree();
};

#include "Source/RTree.cpp"

}

#endif
