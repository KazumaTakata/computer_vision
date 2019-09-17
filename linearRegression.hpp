#ifndef HLINEARREG
#define HLINEARREG

#include "./matrix.hpp"

template <class T>
class LinearReg
{

    int dim;
    Mat<T> weight;
    T bias;

public:
    LinearReg(int _dim) : dim(_dim)
    {
        std::vector<int> size{dim, 1};
        Mat<T> mat(size, 1);
        weight = mat;
        initializeWithZero();
    }

    void initializeWithZero()
    {
        bias = 0;
        for (int i = 0; i < dim; i++)
        {
            weight.at(i, 0) = 0;
        }
    }

    T predict(Mat<T> &x)
    {
        return weight.dot(x) + bias;
    }

    T train(Mat<T> &x, T y)
    {
        weight = weight - x * (-2(y - predict(x)));
    }
};

#endif
