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
class HyperPoint{
private:
	double data[M];

};

template<size_t M>
class HyperRectangle{
friend double operator +(const HyperRectangle<M> &a, const HyperRectangle<M> &b) {
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
	HyperRectangle(const std::vector<HyperPoint> &rhs);

	std::vector<Bound> getBounds()const;
	double area()const;
	bool isOverLap(const HyperRectangle<M> &rhs);

};

#include "source/RTreeCommon.cpp"

}

#endif
