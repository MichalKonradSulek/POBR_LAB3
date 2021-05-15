// POBR_LAB3.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <fstream>
#include "task1.h"
#include "task2.h"


int main()
{
    std::ofstream outputFile;
    outputFile.open("../output.txt");
    if (outputFile.good()) {
        task1(outputFile);
        task2(outputFile);
    }
    else {
        task1(std::cerr);
        task2(std::cerr);
    }

    return 0;
}
