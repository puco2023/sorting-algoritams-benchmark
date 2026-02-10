#pragma once
#include<vector>
#include<string>
#include"sorting.h"
#include"mergeSort.h"
#include"quickBubble.h"
class Tabela
{
public:
	void ubaci(std::string i, long long time) {
        ime.push_back(i);
        vreme.push_back(time);
	}
    void ispis()
    {
        std::cout << "FILE\t\t" << "mergeInsertion\t\t" << "quickBubble\t\t" <<"stdSort\t\t" << std::endl;
        int k = 0;
        const char* slike[] = {
    "image_1_asc.txt",  "image_1_desc.txt",  "image_1_rand.txt",
    "image_2_asc.txt",  "image_2_desc.txt",  "image_2_rand.txt",
    "image_3_asc.txt",  "image_3_desc.txt",  "image_3_rand.txt",
    "image_4_asc.txt",  "image_4_desc.txt",  "image_4_rand.txt"
        };
        for (int i = 0; i < 12; i++)
        {
            std::cout << slike[i] << "\t";
            for (int j = 0; j <3; j++)
            {

                std::cout << vreme[i*3+j]<<"ms\t\t\t";

            }
            std::cout << std::endl;

        }

    }
private:
	std::vector<long long> vreme;
	std::vector<std::string> ime;
};

