#include "standardna.h"
#include<vector>
#include<algorithm>

void biblioteka::sort(Image* image, SortingDirection direction)
{
        int n = image->getElementCount();
        std::vector<int> pos;
        for (int i = 0; i < n; i++)
            pos.push_back(i);

        std::sort(pos.begin(), pos.end(),
            [&](int a, int b)
            {
                if (direction == ASCENDING)
                    return image->getElement(a) < image->getElement(b);
                else
                    return image->getElement(a) > image->getElement(b);
            });

        std::vector<int> to(n);
        for (int i = 0; i < n; i++)
            to[pos[i]] = i;

        for (int i = 0; i < n;i++)
        {
            while (to[i] != i)
            {
                int j = to[i];
                image->swapElements(i, j);
                std::swap(to[i], to[j]);
            }
        }
}