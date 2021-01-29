#pragma once

class Range {
public:
	Range();
	Range(int _start, int _end);

	int size() const;
	bool empty() const;
	static Range all();

	int start, end;
};
