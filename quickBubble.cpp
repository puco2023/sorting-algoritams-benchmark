#include "quickBubble.h"
#include <tuple>
#include <vector>
#include <cmath>

int quickBubble::partition(Image* image, int down, int up, int& currComp, SortingDirection direction)
{
    int mid = (down + up) / 2;
    image->swapElements(down, mid);
    int pivot = image->getElement(down);

    int i = down + 1;
    int j = up;

    while (i < j)
    {
        if (direction == ASCENDING)
        {
            while (i < j && image->getElement(i) <= pivot)
            {
                i++;
                currComp++;
            }

            while (j > down && image->getElement(j) > pivot)
            {
                j--;
                currComp++;
            }
        }
        else
        {
            while (i < j && image->getElement(i) >= pivot)
            {
                i++;
                currComp++;
            }

            while (j > down && image->getElement(j) < pivot)
            {
                j--;
                currComp++;
            }
        }

        if (i < j)
            image->swapElements(i, j);
    }

    image->swapElements(down, j);

    if (currComp >= c * image->getElementCount() * log10(image->getElementCount()) / log10(2))
        return -1;

    return j;
}//ovaj deo koda je preuzet sa slajda 42.

void quickBubble::sort(Image* image, SortingDirection direction)
{
    int currComp = 0;

    std::vector<std::tuple<int, int>> intervals;
    intervals.push_back({ 0, image->getElementCount() - 1 });
    while (!intervals.empty())
    {
        std::tuple<int,int> t = intervals.back();
        intervals.pop_back();

        int l = std::get<0>(t);
        int r = std::get<1>(t);
        if (l >= r) continue;

        int p = this->partition(image, l, r, currComp, direction);

        if (p == -1)
        {
            intervals.push_back({ l, r });
            break;
        }

        if (p > l + 1)
            intervals.push_back({ l, p - 1 });
        if (p < r - 1)
            intervals.push_back({ p + 1, r });
    }

    while (!intervals.empty())
    {
        std::tuple<int,int> t = intervals.back();
        intervals.pop_back();

        int l = std::get<0>(t);
        int r = std::get<1>(t);
        if (l >= r) continue;

        bool swapped;
        for (int i = l; i < r; i++)
        {
            swapped = false;
            for (int j = l; j < r - (i - l); j++)
            {
                if (((image->getElement(j) > image->getElement(j + 1)) && direction == ASCENDING) ||
                    ((image->getElement(j) < image->getElement(j + 1)) && direction == DESCENDING))
                {
                    image->swapElements(j, j + 1);
                    swapped = true;
                }
            }
            if (!swapped) break;
        }
    }
}


