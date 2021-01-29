#pragma once
using namespace std;

template<typename T> class Point_ {
public:
	Point_();
	Point_(T _x, T _y);
	Point_(const Point_& pt);

	Point_& operator = (const Point_& pt);
	
	T dot(const Point_& pt) const;
	double ddot(const Point_& pt) const;
	double cross(const Point_& pt) const;
	bool inside(const Rect_<_Tp>& r) const;
	// ... etc
	
	T x, y;
};

typedef Point_<int> Point2i;
typedef Point_<float> Point2f;
typedef Point_<double> Point2d;
typedef Point2i Point;
