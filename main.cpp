#include <iostream>
#include<algorithm>
#include "mergeSort.h"
#include "image_processor.h"
#include "sorting.h"
#include "quickBubble.h"
#include "Tabela.h"
#include "utils.h"
#include"standardna.h"
using namespace std;
Image* ucitaj(const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) return nullptr;

    int rows, cols;
    file >> rows;
    file >> cols;

    const int pixelCount = rows * cols;
    auto* pixels = new Pixel[pixelCount];

    for (int i = 0; i < pixelCount; i++) {
        std::string line;
        file >> line;

        size_t commaPos = line.find(',');
        pixels[i].index = stoi(line.substr(0, commaPos));
        pixels[i].value = line[commaPos + 1];
    }

    auto* image = new Image(pixels, rows, cols);

    file.close();
    return image;
}//ovo je kod prepisan iz image_processor.h
int main()
{
    const char* outputFile = "";

    Stopwatch sw;
    Tabela t;
    SortingDirection sd = DESCENDING;
    int izbor;
    int c;
    int k;
    long long time;
    int y = 0;

    while (true)
    {
        cout << "1. hibridni merge sort sa insertion sortom\n";
        cout << "2. hibridni quick sort sa bubble sortom\n";
        cout << "3. izmeri za sve slike i ispisi tabelu\n";
        cout << "4. izlaz\n";
        cout << "unesite vas izbor: ";
        cin >> izbor;

        if (izbor == 1)
        {
            const char* inputFile1 = "";
            cout << "unesite parametar k: ";
            cin >> k;


            SortingAlgorithm* algorithm = new mergeInsertion(k);
            ImageProcessor::reconstructImage(inputFile1, outputFile, algorithm);
            delete algorithm;

        }
        else if (izbor == 2)
        {
            const char* inputFile2 = "";
            cout << "unesite parametar c: ";
            cin >> c;

            SortingAlgorithm* algorithm = new quickBubble(c);
            ImageProcessor::reconstructImage(inputFile2, outputFile, algorithm);
            delete algorithm;

        }
        else if (izbor == 3)
        {

            cout << "unesite c (za quickBubble): ";
            cin >> c;
            cout << "unesite k (za mergeInsertion): ";
            cin >> k;

            const char* slike[] = {
                "image_1_asc.txt",  "image_1_desc.txt",  "image_1_rand.txt",
                "image_2_asc.txt",  "image_2_desc.txt",  "image_2_rand.txt",
                "image_3_asc.txt",  "image_3_desc.txt",  "image_3_rand.txt",
                "image_4_asc.txt",  "image_4_desc.txt",  "image_4_rand.txt"
            };
            for (const char* inputFile : slike)
            {
                {
                    SortingAlgorithm* alg = new mergeInsertion(k);
                    Image* image = ucitaj(inputFile);
                    sw.start();
                    alg->sort(image, sd);
                    time = sw.stop();
                    delete image;

                    delete alg;
                    t.ubaci(inputFile, time);
                }

                // quickBubble
                {
                    SortingAlgorithm* alg = new quickBubble(c);
                    Image* image = ucitaj(inputFile);
                    sw.start();
                    alg->sort(image, sd);
                    time = sw.stop();
                    delete image;
                    delete alg;
                    t.ubaci(inputFile, time);
                }

                {
                    SortingAlgorithm* alg = new biblioteka();

                    Image* image = ucitaj(inputFile);
                    sw.start();
                    alg->sort(image, sd);
                    time = sw.stop();
                    delete image;

                    delete alg;
                    t.ubaci(inputFile, time);


                }
            }
            t.ispis();
            cout << "\n";
        }
        else
            break;
    }

    return 0;
}
