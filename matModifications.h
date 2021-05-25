#pragma once
#include "opencv2/core/core.hpp"

cv::Mat1d convertToBinary(const cv::Mat& image, const unsigned threshold) {
    CV_Assert(image.channels() == 3);
    cv::Mat3b image_ = image;
    cv::Mat1d result = cv::Mat1d(image_.rows, image_.cols);
    for (unsigned imageRow = 0; imageRow < image_.rows; ++imageRow) {
        for (unsigned imageCol = 0; imageCol < image_.cols; ++imageCol) {
            if (image_(imageRow, imageCol)[0] + image_(imageRow, imageCol)[1] + image_(imageRow, imageCol)[2] > 3 * threshold) {
                result(imageRow, imageCol) = 0;
            }
            else {
                result(imageRow, imageCol) = 1;
            }
        }
    }
    return result;
}

cv::Mat1d cropImage(const cv::Mat1d& image, const double threshold) {
    unsigned minRow = 0, maxRow = image.rows, minCol = image.cols, maxCol = 0;
    bool isAlreadyFound = false;
    for (unsigned imageRow = 0; imageRow < image.rows; ++imageRow) {
        for (unsigned imageCol = 0; imageCol < image.cols; ++imageCol) {
            if (image(imageRow, imageCol) < threshold) {
                if (!isAlreadyFound) {
                    minRow = imageRow;
                    isAlreadyFound = true;
                }
                maxRow = imageRow;
                if (imageCol < minCol) minCol = imageCol;
                if (imageCol > maxCol) maxCol = imageCol;
            }
        }
    }
    if (minCol == image.cols) minCol = 0;
    if (maxCol == 0) maxCol = image.cols - 1;

    if (minCol > 0) minCol = minCol - 1;
    if (maxCol < image.cols - 1) maxCol = maxCol + 1;
    if (minRow > 0) minRow = minRow - 1;
    if (maxRow < image.rows - 1) maxRow = maxRow + 1;

    cv::Mat1b result = cv::Mat1b(maxRow - minRow + 1, maxCol - minCol + 1);
    for (unsigned imageRow = minRow; imageRow <= maxRow; ++imageRow) {
        for (unsigned imageCol = minCol; imageCol <= maxCol; ++imageCol) {
            result(imageRow - minRow, imageCol - minCol) = image(imageRow, imageCol);
        }
    }
    return result;
}

cv::Mat1d filterPixels(const cv::Mat& image, const cv::Vec3b& filter) {
    CV_Assert(image.channels() == 3);
    cv::Mat3b image_ = image;
    cv::Mat1d result = cv::Mat1d(image_.rows, image_.cols);
    for (unsigned imageRow = 0; imageRow < image_.rows; ++imageRow) {
        for (unsigned imageCol = 0; imageCol < image_.cols; ++imageCol) {
            if (image_(imageRow, imageCol) == filter) {
                result(imageRow, imageCol) = 1;
            }
            else {
                result(imageRow, imageCol) = 0;
            }
        }
    }
    return result;
}
