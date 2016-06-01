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
	tmp[0]->size = 0;
	tmp[1]->size = 0;
	pickSeeds(u, tmp[0], tmp[1]);
	
	while (u->size > 0) {
		if (tmp[0]->size > tmp[1]->size) {
			std::swap(tmp[0], tmp[1]);
		}
		if (tmp[0]->size + u->size <= m) {
			for (int i = 0; i < u->size; i ++) {
				tmp[0]->append(u->child[i]);
			}
			break;
		}
		pickNext(u, tmp[0], tmp[1]);
	}
	(*u) = *tmp[0];
	return tmp[1];
}

template<class T, size_t M, size_t D>
void pickSeeds(RTreeNode<M, D> *u, RTreeNode<M, D> *t0, RTreeNode<M, D> *t1) {
	std::pair<int, int> tmp = std::make_pair(-1, -1);
	double max = -1;
	for (int i = 0; i < u->size; i ++) {
		for (int j = i + 1; j < u->size; j ++) {
			if (std::abs(u->child[i]->box.area() - u->child[j]->box.area()) > max) {
				max = std::abs(u->child[i]->box.area() - u->child[j]->box.area());
				tmp = std::make_pair(i, j);
			}
		}
	}
	t0->append(u->child[i]);
	t1->append(u->child[j]);
	u->erase(u->child[i]);
	u->erase(u->child[j]);
}

template<class T, size_t M, size_t D>
void pickNext(RTreeNode<M, D> *u, RTreeNode<M, D> *t0, RTreeNode<M, D> *t1) {
	t0->update();
	t1->update();
	
	std::pair<int, RTreeNode<M, D>> best;
	int max = -1;
	for (int i = 0; i < u->size(); i ++) {
		double delta[2];
		delta[0] = (t0->box + u->child[i]->box).area() - t0->box.area();
		delta[1] = (t1->box + u->child[i]->box).area() - t1->box.area();
		if (delta[0] > max) {
			max = delta[0];
			best = std::make_pair(i, t0);
		}
		if (delta[1] > max) {
			max = delta[1];
			best = std::make_pair(i, t1);
		}
	}
	best.second->append(u->child[best.first]);
	u->erase(u->child[best.first]);
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
			root->append(u);
			root->append(brother);
			root->level = u->level + 1;
		}
		return ;
	}
	
	RTreeNode<M, D> *father = u->father;
	if (brother != nullptr) {
		father->append(brother);
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
