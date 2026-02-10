#pragma once
#include"sorting.h"
class quickBubble : public SortingAlgorithm
{
public:
	void sort(Image* image, SortingDirection direction);
	int partition(Image* image, int down, int up, int& currComp, SortingDirection direction);
	quickBubble(int c1) { c = c1; }
private:
	int c;
};

