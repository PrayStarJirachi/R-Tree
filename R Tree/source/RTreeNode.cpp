#ifdef SJTU_RTREENODE_HPP

#ifndef SJTU_RTREENODE_CPP
#define SJTU_RTREENODE_CPP

template<size_t M, size_t D>
RTreeNode<M, D>::RTreeNode() {
	size = level = 0;
	fater = nullptr;
}

template<size_t M, size_t D>
RTreeNode<M, D>::~RTreeNode() {
	for (int i = 0; i < size; i++) {
		if (level == 0) {
			delete child[i];
		}
		child[i] = nullptr;
	}
	father = nullptr;
	level = size = 0;
}

template<size_t M, size_t D>
void RTreeNode<M, D>::remove(const RTreeNode<M, D> *key) {
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

template<size_t M, size_t D>
void RTreeNode<M, D>::append(const RTreeNode<M, D> *key) {
	child[size++] = key;
}

#endif

#endif
