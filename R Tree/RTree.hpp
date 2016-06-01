#ifndef SJTU_RTREE_HPP
#define SJTU_RTREE_HPP

#include "RTreeCommon.hpp"
#include "RTreeNode.hpp"

namespace sjtu{

template<class T, size_t M, size_t D>
class RTree{
private:
	RTreeNode *root;

public:
	RTree();
	void insert(const HyperBound<D> &key, const T &value);
	bool remove(const HyperBound<D> &key);
	std::vector<HyperPoint<M> > getPointSet(const HyperBound<D> &bound);

};

#include "source/RTree.cpp"

}

template<class T, size_t M, size_t D>
RTreeNode<M, D>* RTree<T, M, D>::splitNode(RTreeNode<M, D>* u) {
	RTreeNode *tmp[2];
	tmp[0] = new RTreeNode<M, D>(*u);
	tmp[1] = new RTreeNode<M, D>(*u);
	pickSeeds(u, tmp[0], tmp[1]);
	
	for (int i = 0; i < u->size; i ++) {
		
	}
}

template<class T, size_t M, size_t D>
void RTree<T, M, D>::chooseLeaf(const HyperBound<D> &key, const T &value) {
	RTreeNode<M, D> *u = root;
	while (true) {
		if (u->level == 0) {
			return u;
		}
		RTreeNode *v;
		double max = -DBL_MAX;
		for (int i = 0; i < u->size; i ++) {
			double s = (*u->child[i]->box + key).area();
			if (s > max) {
				max = s;
				v = u->child[i];
			}
		}
		u = v;
	}
}

template<class T, size_t M, size_t D>
void RTree<T, M, D>::adjust(RTreeNode<M, D> *u, RTreeNode<M, D> *brother) {
	if (u == root) {
		if (brother != nullptr) {
			root = new RTreeNode();
			root->child[root->size ++] = u;
			root->child[root->size ++] = brother;
			root->level = u->level + 1;
			u->father = root;
			brother->father = root;
		}
		return ;
	}
	
	RTreeNode<M, D> *father = u->father;
	if (brother != nullptr) {
		father->child[father->size ++] = brother;
		brother.father = father;
	}
	father->box = HyperBound();
	for (int i = 0; i < father->size; i ++) {
		father->box += father->child[i]->box;
	}
	
	RTreeNode<M, D> *v;
	if (father->size > M) {
		v = splitNode(father);
	}
	adjust(father, v);
}

template<class T, size_t M, size_t D>
void RTree<T, M, D>::insert(const HyperBound<D> &key, const T &value) {
	RTreeNode<M, D> *target = chooseLeaf(key, value);
	
	target->child[target->size ++] = new std::pair(key, value);
	
	RTreeNode<M, D> *v;
	if (target->size > M) {
		v = splitNode(target);
	}
	adjust(target, v);
}

#endif
