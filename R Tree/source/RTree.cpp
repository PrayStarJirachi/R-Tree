#ifdef SJTU_RTREE_HPP

#ifndef SJTU_RTREE_CPP
#define SJTU_RTREE_CPP


template<class T, size_t M, size_t D>
void RTree<T, M, D>::__find(const RTreeNode<M, D> * const x, const HyperBound<D> &bound, std::vector<T &> &storge)const {
	if (x -> level == 0) {
		for (int i = 0; i < x -> size; i++) {
			if (bound.isOverLap(x.child[i].first)) {
				storge.push_back(*static_cast<T *>(x.child[i].second));
			}
		}
		return;
	}
	for (int i = 0; i < x -> size; i++) {
		if (bound.isOverLap(x.child[i].first)) {
			__find(*static_cast<RTreeNode<M, D> *>(x.child[i]), bound, storge);
		}
	}
}

template<class T, size_t M, size_t D>
std::vector<T> RTree<T, M, D>::getPointSet(const HyperBound<M> &bound)const {
	static std::vector<T &> ret;
	ret.clear();
	__find(root, bound, ret);
	return ret;
}

#endif

#endif
