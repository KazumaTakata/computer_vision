#include "opencv2/opencv.hpp"
#include <stdio.h>
#include <iostream>

using namespace cv;

int main(int argc, char **argv)
{

    //create a gui window:
    namedWindow("Output", 1);
    Mat img_1 = imread(argv[1], IMREAD_GRAYSCALE);
    int minHessian = 400;
    // Ptr<SURF> detector = SURF::create(minHessian);
    //initialize a 120X350 matrix of black pixels:
    Mat output = Mat::zeros(120, 350, CV_8UC3);

    std::vector<KeyPoint> keypoints_1;

    //write text on the matrix:
    putText(output,
            "Hello World :)",
            Point(15, 70),
            FONT_HERSHEY_PLAIN,
            3,
            Scalar(0, 255, 0),
            4);

    Vec3b data = output.at<Vec3b>(3, 4);
    Vec3b data1 = output.at<Vec3b>(3, 11);

    Mat A(1, 1, CV_32FC3),
        B(1, 1, CV_32FC3);

    A.at<Vec3f>(0, 0)[0] = 0;
    A.at<Vec3f>(0, 0)[1] = 1;
    A.at<Vec3f>(0, 0)[2] = 2;

    B.at<Vec3f>(0, 0)[0] = 3;
    B.at<Vec3f>(0, 0)[1] = 4;
    B.at<Vec3f>(0, 0)[2] = 5;

    Mat AxB = A.cross(B);
    Mat BxA = B.cross(A);

    //display the image:
    imshow("Output", output);

    //wait for the user to press any key:
    waitKey(0);

    return 0;
}