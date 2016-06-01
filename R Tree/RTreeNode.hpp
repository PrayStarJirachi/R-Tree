#ifndef SJTU_RTREENODE_HPP
#define SJTU_RTREENODE_CPP

#include "RTreeCommon.hpp"

namespace sjtu{

template<class T, size_t M, size_t D>
struct RTreeNode{
	HyperBound<D> box;
	void *child[M + 1];
	RTreeNode<T, M, D> *father;
	size_t level, size;

	RTreeNode();
	virtual ~RTreeNode();

	void remove(const RTreeNode<T, M, D> *key);
	void append(RTreeNode<T, M, D> *key);
	void update();

};

template<class T, size_t M, size_t D>
RTreeNode<T, M, D>::RTreeNode() {
	size = level = 0;
	father = nullptr;
}

template<class T, size_t M, size_t D>
RTreeNode<T, M, D>::~RTreeNode() {
	for (int i = 0; i < size; i++) {
		if (level == 0) {
			delete static_cast<std::pair<HyperBound<D>, T> *>(child[i]);
		}
		child[i] = nullptr;
	}
	father = nullptr;
	level = size = 0;
}

template<class T, size_t M, size_t D>
void RTreeNode<T, M, D>::remove(const RTreeNode<T, M, D> *key) {
	for (int i = 0; i < size; i++) {
		if (child[i] == key) {
			for (int j = i; j < size - 1; j++) {
				child[j] = child[j + 1];
			}
			size--;
			break;
		}
	}
}

template<class T, size_t M, size_t D>
void RTreeNode<T, M, D>::append(RTreeNode<T, M, D> *key) {
	child[size++] = key;
	key -> father = this;
}

template<class T, size_t M, size_t D>
void RTreeNode<T, M, D>::update() {
	box = HyperBound<D>();
	for (int i = 0; i < size; i++) {
		box = box + static_cast<RTreeNode<T, M, D> *>(child[i]) -> box;
	}
}

}

#endif
