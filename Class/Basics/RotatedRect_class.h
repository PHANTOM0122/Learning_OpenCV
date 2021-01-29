#pragma once
#include "Point_Class.h"
#include "Size_class.h"
#include "Rect_class.h"
class RotatedRect {
public:
	RotatedRect();
	RotatedRect(const Point2f& center, const Size2f& size, float angle);
	RotatedRect(const Point2f& point1, const Point2f& point2, const Point2f& point3);

	void points(Point2f pts[])const;
	Rect boundingRect() const;
	Rect boundingRect2f() const;

	Point2f center;
	Size2f size;
	float angle;
};