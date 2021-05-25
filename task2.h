#pragma once
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc.hpp>

#include "matModifications.h"
#include "coefficientCalculations.h"

struct Task2Result {
    unsigned id = 0;
    unsigned red = 0;
    double angle = 0;
    unsigned area = 0;
    unsigned perimeter = 0;
    double w3 = 0;
    double m1 = 0;
    double m7 = 0;
};

void printResult(std::ostream& os, const Task2Result& task2Result) {
    os << task2Result.id << ". Strzalka R=" << task2Result.red
        << ", nachylenie=" << task2Result.angle << ", S=" << task2Result.area << ", L=" << task2Result.perimeter
        << ", W3=" << task2Result.w3 << ", M1=" << task2Result.m1
        << ", M7=" << task2Result.m7 << std::endl;
}

void produceResultTask2(std::ostream& fileOutput, const cv::Mat& image, const cv::Vec3b& filter, unsigned id) {
    const double DOUBLE_THRESHOLD = 0.5;
    cv::Mat filteredArrow = filterPixels(image, filter);
    cv::Mat croppedImage = cropImage(filteredArrow, 0.5);
    ImageMomentums imageMomentums = calculateImageMomentums(croppedImage);
    cv::Point centerOfImage = calculateGeometricCenter(croppedImage);
    cv::Point centerOfGravity = calculateCenterOfGravity(imageMomentums.m10, imageMomentums.m01, imageMomentums.m00);
    //cv::circle(croppedImage, centerOfImage, 2, cv::Scalar(0.5, 0.5, 0.5));
    //cv::circle(croppedImage, centerOfGravity, 2, cv::Scalar(0.7, 0.7, 0.7));
    //cv::imshow("", croppedImage);
    //cv::waitKey(-1);
    Task2Result result;
    result.id = id;
    result.red = filter[2];
    result.angle = calculateAngle(centerOfGravity, centerOfImage);
    result.area = calculateArea(croppedImage, DOUBLE_THRESHOLD);
    result.perimeter = calculatePerimeter(croppedImage, DOUBLE_THRESHOLD);
    result.w3 = calculateW3(result.area, result.perimeter);
    result.m1 = calculateM1(imageMomentums);
    result.m7 = calculateM7(imageMomentums);
    printResult(std::cout, result);
    printResult(fileOutput, result);
}

void analyzeArrows(std::ostream& fileOutput, const std::string& fileName) {
    cv::Mat image = cv::imread(fileName);
    std::cout << "File: \"" << fileName << "\"\n";
    fileOutput << "File: \"" << fileName << "\"\n";
    produceResultTask2(fileOutput, image, cv::Vec3b(0, 180, 0), 1);
    produceResultTask2(fileOutput, image, cv::Vec3b(0, 135, 45), 2);
    produceResultTask2(fileOutput, image, cv::Vec3b(0, 90, 90), 3);
    produceResultTask2(fileOutput, image, cv::Vec3b(0, 45, 135), 4);
    produceResultTask2(fileOutput, image, cv::Vec3b(0, 0, 180), 5);
}

void task2(std::ostream& fileOutput) {
    std::cout << "Task2\n";
    fileOutput << "Task2\n";
    analyzeArrows(fileOutput, "../strzalki_1.dib");
    analyzeArrows(fileOutput, "../strzalki_2.dib");
}