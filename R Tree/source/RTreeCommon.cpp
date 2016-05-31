#ifdef SJTU_RTREECOMMON_HPP

#ifndef SJTU_RTREECOMMON_CPP
#define SJTU_RTREECOMMON_CPP

Bound::Bound() : lowerBound(0), upperBound(0) {
};

Bound::Bound(const double &lB, const double &rB) : lowerBound(lB), upperBound(rB) {
}

template<size_t M>
HyperRectangle<M>::HyperRectangle(const std::vector<Bound> &rhs) : bounds(rhs) {
	assert(rhs.size() == M);
}

template<size_t M>
std::vector<Bound> HyperRectangle<M>::getBounds()const {
	return bounds;
}

template<size_t M>
double HyperRectangle<M>::area()const {
	double ret = 1.0;
	for (auto element : bounds) {
		ret *= element.upperBound - element.lowerBound;
	}
	return ret;
}

template<size_t M>
bool HyperRectangle<M>::isOverLap(const HyperRectangle<M> &rhs) {
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
