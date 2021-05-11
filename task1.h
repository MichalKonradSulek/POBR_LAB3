#pragma once
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "matModifications.h"
#include "coefficientCalculations.h"

struct Task1Result {
    unsigned id = 0;
    std::string fileName = "";
    unsigned area = 0;
    unsigned perimeter = 0;
    double w3 = 0;
    double m1 = 0;
    double m7 = 0;
};

void printResult(std::ostream& os, const Task1Result& task1Result) {
    os << task1Result.id << ". Plik \"" << task1Result.fileName
        << "\" S=" << task1Result.area << ", L=" << task1Result.perimeter
        << ", W3=" << task1Result.w3 << ", M1=" << task1Result.m1
        << ", M7=" << task1Result.m7 << std::endl;
}

void produceResultTask1(std::ostream& fileOutput, const std::string& fileName, const unsigned id) {
    const double DOUBLE_THRESHOLD = 0.5;
    cv::Mat image = cv::imread(fileName);
    cv::Mat binaryImage = convertToBinary(image, 127);
    cv::Mat croppedImage = cropImage(binaryImage, DOUBLE_THRESHOLD);
    Task1Result result;
    result.id = 1;
    result.fileName = fileName;
    result.area = calculateArea(croppedImage, DOUBLE_THRESHOLD);
    result.perimeter = calculatePerimeter(croppedImage, DOUBLE_THRESHOLD);
    result.w3 = calculateW3(result.area, result.perimeter);
    ImageMomentums imageMomentums = calculateImageMomentums(croppedImage);
    result.m1 = calculateM1(imageMomentums);
    result.m7 = calculateM7(imageMomentums);
    printResult(std::cout, result);
    printResult(fileOutput, result);
}

void task1(std::ostream& fileOutput) {
    std::cout << "Task1\n";
    fileOutput << "Task1\n";
    produceResultTask1(fileOutput, "elipsa.dib", 1);
    produceResultTask1(fileOutput, "elipsa1.dib", 2);
    produceResultTask1(fileOutput, "kolo.dib", 3);
    produceResultTask1(fileOutput, "prost.dib", 4);
    produceResultTask1(fileOutput, "troj.dib", 5);
}
