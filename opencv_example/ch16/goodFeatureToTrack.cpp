#include "opencv2/opencv.hpp"

int main(int argc, char **argv)
{
    cv::Mat img = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
    if (img.empty())
        return -1;
    cv::namedWindow("Example 2-1", cv::WINDOW_AUTOSIZE);
    cv::Mat outimg;

    std::vector<cv::Point2f> corners;

    cv::goodFeaturesToTrack(img, corners, 1000, 0.01, 5, cv::noArray(), 3, false, 0.04);

    std::vector<cv::KeyPoint> keypoints;
    for (size_t i = 0; i < corners.size(); i++)
    {
        keypoints.push_back(cv::KeyPoint(corners[i], 1.f));
    }

    cv::drawKeypoints(img, keypoints, outimg, cv::Scalar::all(-1), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    cv::imshow("Example 2-1", outimg);
    cv::waitKey(0);
    cv::destroyWindow("Example 2-1");
    return 0;
}