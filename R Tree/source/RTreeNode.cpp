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

#endif

#endif
