#include "matrix.hpp"
#include <vector>

int main()
{

    std::vector<int> size{2, 3};
    Mat<float> mat(size, 1);

    std::vector<int> size2{3, 2};

    Mat<float> mat2(size2, 2);

    Mat<float> mat3 = mat * mat2;

    mat3.print();

    return 0;
}