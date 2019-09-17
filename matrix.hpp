#ifndef HMATRIX
#define HMATRIX

#include <vector>
#include <iostream>

// todo: set rule of three
//     : operator overload
template <class T>
class Mat
{

    int dim;
    int Ndata;
    T *data;
    std::vector<int> sizes;

    // Mat(const Mat &mat);

public:
    Mat(const std::vector<int> &_sizes, T initValue) : sizes(_sizes), Ndata(1)
    {
        dim = sizes.size();
        for (int i = 0; i < dim; i++)
        {
            Ndata *= sizes[i];
        }
        data = new T[Ndata];

        for (int i = 0; i < Ndata; i++)
        {
            data[i] = initValue;
        }
    }

    // copy constructor
    // do deep copy
    Mat(const Mat &that)
    {
        dim = that.dim;
        Ndata = that.Ndata;
        sizes = that.sizes;
        data = new T[Ndata];
        for (int i = 0; i < Ndata; i++)
        {
            data[i] = that.data[i];
        }
    }

    ~Mat()
    {
        delete[] data;
    }

    Mat &operator=(const Mat &that)
    {
        if (this != &that)
        {
            delete[] data;

            dim = that.dim;
            Ndata = that.Ndata;
            sizes = that.sizes;

            data = new T[Ndata];
            for (int i = 0; i < Ndata; i++)
            {
                data[i] = that.data[i];
            }
        }

        return *this;
    }

    // 2d row major
    inline T at(int row, int col) const
    {
        int index = row * sizes.at(1) + col;
        return data[index];
    }

    inline void setAt(int row, int col, T value)
    {
        int index = row * sizes.at(1) + col;
        data[index] = value;
    }

    Mat operator*(const Mat &that)
    {
        std::vector<int> newsizes{sizes[0], that.sizes[1]};
        Mat newMat(newsizes, 0);

        int row1 = sizes[0];
        int col2 = that.sizes[1];

        assert(sizes[1] == that.sizes[0] && "matrix dimention should be matched");

        for (int i = 0; i < row1; i++)
        {
            for (int j = 0; j < col2; j++)
            {
                T sum = 0;
                for (int k = 0; k < sizes[1]; k++)
                {
                    sum += at(i, k) * that.at(k, j);
                }
                newMat.setAt(i, j, sum);
            }
        }

        return newMat;
    }

    Mat operator*(const T scala)
    {
        Mat newMat(sizes, 0);
        int row = sizes[0];
        int col = sizes[1];

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {

                newMat.setAt(i, j, at(i, j) * scala);
            }
        }

        return newMat;
    }

    Mat operator+(const Mat &that)
    {
        std::vector<int> newsizes{sizes[0], that.sizes[1]};
        Mat newMat(newsizes, 0);

        assert(sizes[0] == that.sizes[0] && "matrix dimention should be matched");
        assert(sizes[1] == that.sizes[1] && "matrix dimention should be matched");

        int row = sizes[0];
        int col = sizes[1];

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                newMat.setAt(i, j, at(i, j) + that.at(i, j));
            }
        }

        return newMat;
    }

    Mat transpose()
    {
        std::vector<int> newsizes{sizes[1], sizes[0]};
        Mat newMat(newsizes, 0);

        int row = sizes[0];
        int col = sizes[1];

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                newMat.setAt(j, i, at(i, j));
            }
        }

        return newMat;
    }

    Mat operator-(const Mat &that)
    {
        std::vector<int> newsizes{sizes[0], that.sizes[1]};
        Mat newMat(newsizes, 0);

        assert(sizes[0] == that.sizes[0] && "matrix dimention should be matched");
        assert(sizes[1] == that.sizes[1] && "matrix dimention should be matched");

        int row = sizes[0];
        int col = sizes[1];

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                newMat.setAt(i, j, at(i, j) - that.at(i, j));
            }
        }

        return newMat;
    }

    T dot(const Mat &that)
    {
        assert(1 == that.sizes[1] && "right operand is not vector");
        assert(1 == sizes[1] && "left operand is not vector");

        T sum = 0;
        for (int i = 0; i < sizes[0]; i++)
        {
            sum += data[i] * that.data[i];
        }

        return sum;
    }

    void print()
    {
        std::cout << "[\n";
        for (int i = 0; i < sizes[0]; i++)
        {
            std::cout << " [";
            for (int j = 0; j < sizes[1]; j++)
            {
                std::cout << at(i, j);
            }
            std::cout << "]\n";
        }
        std::cout << "]";
    }
};

#endif