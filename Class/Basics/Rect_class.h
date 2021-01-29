#pragma once
#include "Point_Class.h"
#include "Size_class.h"

template<typename T>
class Rect_ {
public:
	Rect_();
	Rect_(T x, T y, T width, T height);
	Rect_(const Rect& r);
	Rect_(const Point_<T>& org, const Size_<T>& sz);
	Rect(const Point_<T>& pt1, const Point_<T>& pt2);

	Rect_& operator = (const Rect_& r);

	Point_<T> t1() const;
	Point_<T> br() const;
	Size_<T> size() const;
	T area() const;
	bool empty() const;
	bool contains(const Point_<T>& pt) const;


	T x, y;
};

typedef Rect_<int> Rect2i;
typedef Rect_<float> Rect2f;
typedef Rect_<double> Rect2d;
typedef Rect2i Rect;