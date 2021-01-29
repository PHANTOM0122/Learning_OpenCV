#pragma once

template<typename T>
class Size_ {
public:
	Size_();
	Size_(T _width, T _height);
	Size(const Size& sz);

	Size_& operator = (const size_& sz);

	T area() const;
	bool empty() const;

	T  _width, _height;
};

typedef Size_<int> Size2i;
typedef Size_<float> Size2f;
typedef Size_<double> Size2d;
typedef Size2i Size;