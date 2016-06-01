#ifndef SJTU_RTREE_HPP
#define SJTU_RTREE_HPP

#include "RTreeCommon.hpp"
#include "RTreeNode.hpp"

namespace sjtu{

template<class T, size_t M, size_t D>
class RTree{
private:
	RTreeNode<M, D> *root;

	void __find(const RTreeNode<M, D> * const *now, const HyperBound<D> &bound, std::vector<T &> &storge)const;

public:
	RTree();

	bool insert(const HyperBound<D> &key, const T &value);
	bool remove(const HyperBound<D> &key);
	std::vector<T &> getPointSet(const HyperBound<D> &bound)const;

	virtual ~RTree();
};

#include "source/RTree.cpp"

}

#endif
