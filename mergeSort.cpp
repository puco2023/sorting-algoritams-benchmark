#include "mergeSort.h"
#include <utility>
#include <vector>
#include <algorithm>

void mergeInsertion::merge(int left, int right, int mid, std::vector<int>& v1, std::vector<int>& v2, Image* image, SortingDirection direction)
{
    int l = left;
    int r = mid;
    int u = left;

    while (l < mid && r < right)
    {
        if ((direction == ASCENDING && image->getElement(v1[l]) <= image->getElement(v1[r])) ||
            (direction == DESCENDING && image->getElement(v1[l]) > image->getElement(v1[r])))
            v2[u++] = v1[l++];
        else
            v2[u++] = v1[r++];
    }
    while (l < mid)   v2[u++] = v1[l++];
    while (r < right) v2[u++] = v1[r++];
}

void mergeInsertion::sort(Image* image, SortingDirection direction)
{
    const int n = image->getElementCount();
    if (n <= 1) return;
    std::vector<int> v1(n), v2(n);
    for (int i = 0; i < n; i++) v1[i] = i;

    int step = 1;
    while (step < n)
    {
        if (step >= k)
            break;
        int left = 0;
        while (left < n)
        {
            int mid = std::min(left + step, n);
            int right = std::min(left + 2 * step, n);
            merge(left, right, mid, v1, v2, image, direction);

            left += 2 * step;
        }
        std::swap(v1, v2);
        step *= 2;
    }

    int block = step;
    for (int start = 0; start < n; start += block)
    {
        int end = std::min(start + block, n);
        for (int i = start + 1; i < end; i++)
        {
            int keyPos = v1[i];
            int j = i - 1;
            while (j >= start &&
                ((direction == ASCENDING && image->getElement(keyPos) < image->getElement(v1[j])) ||
                    (direction == DESCENDING && image->getElement(keyPos) > image->getElement(v1[j]))))
            {
                v1[j + 1] = v1[j];
                j--;
            }
            v1[j + 1] = keyPos;
        }
    }//ovaj deo insertion sorta je preuzet sa prezentacije

    while (step < n)
    {
        int left = 0;
        while (left < n)
        {
            int mid = std::min(left + step, n);
            int right = std::min(left + 2 * step, n);
            merge(left, right, mid, v1, v2, image, direction);
            left += 2 * step;
        }
        std::swap(v1, v2);
        step *= 2;
    }

    std::vector<int> to(n);
    for (int newPos = 0; newPos < n; newPos++)
        to[v1[newPos]] = newPos;

    for (int i = 0; i < n; i++)
    {
        while (to[i] != i)
        {
            int j = to[i];
            image->swapElements(i, j);
            std::swap(to[i], to[j]);
        }
    }
}
