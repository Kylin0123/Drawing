#pragma once
class Cutable
{
public:
	Cutable();
	~Cutable();
	virtual bool cut(int xmin, int ymin, int xmax, int ymax) = 0;
};

