#ifdef SJTU_RTREECOMMON_HPP

#ifndef SJTU_RTREECOMMON_CPP
#define SJTU_RTREECOMMON_CPP

Bound::Bound() : lowerBound(DBL_MAX), upperBound(-DBL_MAX) {
};

Bound::Bound(const double &lB, const double &rB) : lowerBound(lB), upperBound(rB) {
}

template<size_t M>
HyperBound<M>::HyperBound() {
}

template<size_t M>
HyperBound<M>::HyperBound(const std::vector<Bound> &rhs) {
	assert(rhs.size() == M);
	for (int i = 0; i < M; i++) {
		bounds[i] = rhs[i];
	}
}

template<size_t M>
double HyperBound<M>::area()const {
	double ret = 1.0;
	for (auto element : bounds) {
		ret *= element.upperBound - element.lowerBound;
	}
	return ret;
}

template<size_t M>
bool HyperBound<M>::isOverLap(const HyperBound<M> &rhs)const {
	for (int i = 0; i < M; i++) {
		Bound a = bounds[i], b = rhs.bounds[i];
		if (a.lowerBound > b.upperBound || b.lowerBound > a.upperBound) {
			return false;
		}
	}
	return true;
}

#endif

#endif
