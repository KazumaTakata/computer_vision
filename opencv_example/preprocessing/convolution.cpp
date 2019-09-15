#include "opencv2/opencv.hpp"
#include <cmath>

using namespace std;

void CV_Conv(cv::Mat img, cv::Mat output_img, vector<vector<int>> filter);
cv::Mat CV_gaussian_filter(int size, double sigma);
double pi() { return std::atan(1) * 4; }

int main(int argc, char **argv)
{
    cv::Mat img = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
    if (img.empty())
        return -1;

    // vector<vector<int>> vect{
    //     {1, 0, -1}, {1, 0, -1}, {1, 0, -1}};

    // vector<vector<int>> vect{
    //     {1, 1, 1}, {0, 0, 0}, {-1, -1, -1}};

    cv::Mat gF = CV_gaussian_filter(3, 1);

    vector<vector<int>>
        vect{
            {0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};

    cv::Mat output_img = cv::Mat::zeros(img.size(), 0);

    CV_Conv(img, output_img, gF);

    cv::namedWindow("Example 2-1", cv::WINDOW_AUTOSIZE);
    cv::imshow("Example 2-1", output_img);
    cv::waitKey(0);
    cv::destroyWindow("Example 2-1");
    return 0;
}

void CV_Conv(cv::Mat img, cv::Mat output_img, vector<vector<int>> filter)
{

    int filter_size = filter.size();
    for (int i = 0; i < output_img.size().height; i++)
    {
        for (int j = 0; j < output_img.size().width; j++)
        {
            int conv_sum = 0;
            for (int i2 = 0; i2 < filter_size; i2++)
            {
                for (int j2 = 0; j2 < filter_size; j2++)
                {
                    int rindex = i - filter_size / 2 + i2;
                    int cindex = j - filter_size / 2 + j2;
                    int pij;
                    if (rindex >= 0 && rindex < img.size().height && cindex >= 0 && cindex < img.size().width)
                    {
                        pij = img.at<uchar>(rindex, cindex);
                    }
                    else
                    {
                        pij = 0;
                    }

                    int filter_value = filter[filter_size - 1 - i2][filter_size - 1 - j2];

                    conv_sum += pij * filter_value;
                }
            }
            output_img.at<uchar>(i, j) = conv_sum + 127;
        }
    }
}

double CV_gaussian(int m, int n, double sigma)
{
    return 1 / (2 * pi() * pow(sigma, 2)) * exp(-(pow(m, 2) + pow(n, 2)) / (2 * pow(sigma, 2)));
}

cv::Mat CV_gaussian_filter(int size, double sigma)
{
    int slide = size / 2;
    cv::Mat output_img = cv::Mat::zeros(cv::Size(size, size), CV_64FC1);
    for (int i = 0; i < output_img.size().height; i++)
    {
        for (int j = 0; j < output_img.size().width; j++)
        {
            float tmp = CV_gaussian(i - slide, j - slide, sigma);
            output_img.at<float>(i, j) = CV_gaussian(i - slide, j - slide, sigma);
        }
    }

    return output_img;
}