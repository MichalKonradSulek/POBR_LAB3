#pragma once
#include<cmath>
#include "opencv2/core/core.hpp"

int calculateArea(const cv::Mat1d& image, const double threshold) {
    unsigned area = 0;
    for (unsigned imageRow = 0; imageRow < image.rows; ++imageRow) {
        for (unsigned imageCol = 0; imageCol < image.cols; ++imageCol) {
            if (image(imageRow, imageCol) < threshold) {
                ++area;
            }
        }
    }
    return area;
}

unsigned calculatePerimeter(const cv::Mat1d& image, const double threshold) {
    unsigned perimeter = 0;
    for (unsigned imageRow = 1; imageRow < image.rows - 1; ++imageRow) {
        for (unsigned imageCol = 1; imageCol < image.cols - 1; ++imageCol) {
            if (image(imageRow, imageCol) < threshold
                && (image(imageRow - 1, imageCol) >= threshold || image(imageRow + 1, imageCol) >= threshold
                    || image(imageRow, imageCol - 1) >= threshold || image(imageRow + 1, imageCol + 1) >= threshold)) {
                ++perimeter;
            }
        }
    }
    for (unsigned imageRow = 0; imageRow < image.rows; ++imageRow) {
        if (image(imageRow, 0) < threshold) ++perimeter;
        if (image(imageRow, image.cols - 1) < threshold) ++perimeter;
    }
    for (unsigned imageCol = 1; imageCol < image.cols - 1; ++imageCol) {
        if (image(0, imageCol) < threshold) ++perimeter;
        if (image(image.rows - 1, imageCol) < threshold) ++perimeter;
    }
    return perimeter;
}

double calculateW3(const unsigned area, const unsigned perimeter) {
    const double PI = atan(1) * 4;
    double squareRoot = sqrt(PI * area);
    return perimeter / (2 * squareRoot) - 1;
}

double calculateMomentum(const cv::Mat1d& image, const unsigned p, const unsigned q) {
    double sum = 0;
    for (unsigned imageRow = 0; imageRow < image.rows; ++imageRow) {
        for (unsigned imageCol = 0; imageCol < image.cols; ++imageCol) {
            sum += image(imageRow, imageCol) * pow(imageRow, p) * pow(imageCol, q);
        }
    }
    return sum;
}

struct ImageMomentums {
    double m00 = 0;
    double m01 = 0;
    double m10 = 0;
    double m11 = 0;
    double m02 = 0;
    double m20 = 0;
};

ImageMomentums calculateImageMomentums(const cv::Mat1d& image) {
    ImageMomentums result;
    for (unsigned imageRow = 0; imageRow < image.rows; ++imageRow) {
        for (unsigned imageCol = 0; imageCol < image.cols; ++imageCol) {
            result.m00 += image(imageRow, imageCol);
            result.m01 += image(imageRow, imageCol) * (imageRow + 0.5);
            result.m10 += image(imageRow, imageCol) * (imageCol + 0.5);
            result.m11 += image(imageRow, imageCol) * (imageCol + 0.5) * (imageRow + 0.5);
            result.m02 += image(imageRow, imageCol) * pow((imageRow + 0.5), 2);
            result.m20 += image(imageRow, imageCol) * pow((imageCol + 0.5), 2);
        }
    }
    return result;
}

double calculateM1(const ImageMomentums& momentums) {
    const double M02 = momentums.m02 - pow(momentums.m01, 2) / momentums.m00;
    const double M20 = momentums.m20 - pow(momentums.m10, 2) / momentums.m00;
    return (M20 + M02) / pow(momentums.m00, 2);
}

double calculateM7(const ImageMomentums& momentums) {
    const double M11 = momentums.m11 - momentums.m10 * momentums.m01 / momentums.m00;
    const double M02 = momentums.m02 - pow(momentums.m01, 2) / momentums.m00;
    const double M20 = momentums.m20 - pow(momentums.m10, 2) / momentums.m00;
    return (M20 * M02 - pow(M11, 2)) / pow(momentums.m00, 4);
}

cv::Point calculateGeometricCenter(const cv::Mat1d& image) {
    return cv::Point(image.cols / 2, image.rows / 2);
}

cv::Point calculateCenterOfGravity(const double mx, const double my, const double m0) {
    return cv::Point(mx / m0, my / m0);
}

double calculateAngle(const cv::Point& centerPoint, const cv::Point& anotherPoint) {
    double dx = anotherPoint.x - centerPoint.x;
    double dy = - (anotherPoint.y - centerPoint.y);
    if (dy == 0) {
        return 90.0 * ((0.0 < dx) - (dx < 0.0));
    }
    else {
        const double PI = atan(1) * 4;
        double result = atan(dx / dy) * 180 / PI;
        return result;
    }
}
