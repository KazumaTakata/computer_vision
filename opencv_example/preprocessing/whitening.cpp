#include "opencv2/opencv.hpp"
#include <cmath>
#include "./preprocess.hpp"

int main(int argc, char **argv)
{
    cv::Mat img = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
    if (img.empty())
        return -1;

    double mean = CV_Mean(img);
    double std_div = CV_Deviation(img, mean);

    cv::Mat output_img = cv::Mat::zeros(img.size(), 0);

    CV_Whiten(img, output_img);
    cv::namedWindow("Example 2-1", cv::WINDOW_AUTOSIZE);
    cv::imshow("Example 2-1", output_img);
    cv::waitKey(0);
    cv::destroyWindow("Example 2-1");
    return 0;
}

double CV_Mean(cv::Mat mat)
{
    double sum = cv::sum(mat)[0];
    int numOfElement = mat.size().width * mat.size().height;
    return sum / numOfElement;
}

double CV_Deviation(cv::Mat mat, double mean)
{
    double sum_sigma = 0;

    for (int i = 0; i < mat.size().height; i++)
    {
        for (int j = 0; j < mat.size().width; j++)
        {
            int type = mat.at<uchar>(i, j);
            sum_sigma += pow(mat.at<uchar>(i, j) - mean, 2);
        }
    }

    int numOfElement = mat.size().width * mat.size().height;
    return pow(sum_sigma / numOfElement, 0.5);
}

void CV_Whiten(cv::Mat inputmat, cv::Mat outputmat)
{

    double mean = CV_Mean(inputmat);
    double sigma = CV_Deviation(inputmat, mean);

    for (int i = 0; i < outputmat.size().height; i++)
    {
        for (int j = 0; j < outputmat.size().width; j++)
        {
            uchar pix = inputmat.at<uchar>(i, j);
            outputmat.at<u_char>(i, j) = (uchar)((pix - (uchar)mean + 127) / sigma * 40);
        }
    }
}