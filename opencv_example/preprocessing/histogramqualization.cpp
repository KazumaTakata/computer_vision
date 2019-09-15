#include "opencv2/opencv.hpp"
#include <cmath>

int main(int argc, char **argv)
{
    cv::Mat img = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
    if (img.empty())
        return -1;

    std::vector<int> histogram(256);
    std::vector<double> culm(256);

    for (int k = 0; k < 256; k++)
    {
        for (int i = 0; i < img.size().height; i++)
        {
            for (int j = 0; j < img.size().width; j++)
            {
                int pix = img.at<uchar>(i, j);
                if (pix == (uchar)k)
                {
                    histogram[k] += 1;
                }
            }
        }
    }

    for (int k = 0; k < 256; k++)
    {
        for (int k2 = 0; k2 < k + 1; k2++)
        {
            culm[k] += histogram[k2];
        }
        culm[k] = culm[k] / img.size().height / img.size().width;
    }

    cv::Mat output_img = cv::Mat::zeros(img.size(), 0);

    for (int i = 0; i < output_img.size().height; i++)
    {
        for (int j = 0; j < output_img.size().width; j++)
        {
            int pij = img.at<uchar>(i, j);
            output_img.at<uchar>(i, j) = (uchar)(255 * culm[pij]);
        }
    }

    cv::namedWindow("Example 2-1", cv::WINDOW_AUTOSIZE);
    cv::imshow("Example 2-1", output_img);
    cv::waitKey(0);
    cv::destroyWindow("Example 2-1");
    return 0;
}
