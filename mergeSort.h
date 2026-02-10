#pragma once
#include "sorting.h"
#include<vector>
class mergeInsertion : public SortingAlgorithm
{
public:
	void sort(Image* image, SortingDirection direction) override;
	void merge(int left, int right, int mid,std::vector<int>& v1, std::vector<int>&v2, Image* image,SortingDirection direction);
	mergeInsertion(int k1) { k = k1; }
private:
	int k;
};

