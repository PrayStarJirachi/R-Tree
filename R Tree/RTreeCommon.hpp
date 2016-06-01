#ifndef SJTU_RTREECOMMON_HPP
#define SJTU_RTREECOMMON_HPP

#include <cstddef>
#include <vector>
#include <algorithm>
#include <cassert>

namespace sjtu{

struct Bound{
	double lowerBound, upperBound;

	Bound();
	Bound(const double &x, const double &y);

};

template<size_t M>
class HyperBound{
friend double operator +(const HyperBound<M> &a, const HyperBound<M> &b) {
	double tmp = 0.0;
	for (int i = 0; i < M; i++) {
		Bound lA = a.bounds[i], lB = b.bounds[i];
		tmp *= (std::max(lA.upperBound, lB.upperBound) - std::min(lA.lowerBound, lB.lowerBound));
	}
	return tmp;
}
private:
	std::vector<Bound> bounds;

public:
	HyperBound(const std::vector<Bound> &rhs);

	double area()const;
	bool isOverLap(const HyperBound<M> &rhs);

};

#include "source/RTreeCommon.cpp"

}

#endif
