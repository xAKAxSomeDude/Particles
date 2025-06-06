#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

namespace Matrices
{
    class Matrix
    {
        public:
            ///Construct a matrix of the specified size.
            ///Initialize each element to 0.
            Matrix(int _rows, int _cols) : rows(_rows), cols(_cols)
            {
                a.resize(rows, vector<double>(cols, 0.0));
            }
            ///************************************
            ///inline accessors / mutators, these are done:

            ///Read element at row i, column j
            ///usage:  double x = a(i,j);
            const double& operator()(int i, int j) const
            {
                return a.at(i).at(j);
            }

            ///Assign element at row i, column j
            ///usage:  a(i,j) = x;
            double& operator()(int i, int j)
            {
                return a.at(i).at(j);
            }

            int getRows() const{return rows;}
            int getCols() const{return cols;}
            ///************************************
        protected:
            ///changed to protected so sublasses can modify
            vector<vector<double>> a;
        private:
            int rows;
            int cols;
    };

    ///Add each corresponding element.
    ///usage:  c = a + b;
    inline Matrix operator+(const Matrix& a, const Matrix& b)
    {
    
        if (a.getCols() != b.getCols() || a.getRows() != b.getRows())
        {
            throw(runtime_error("Error Matricies dont' match. Addition"));
        }
        Matrix c (a.getRows(), a.getCols());
        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < a.getCols(); j++)
            {
                c(i,j) = a(i,j)+b(i,j);
            }
            
        }
        
        return c;
    };

    ///Matrix multiply.  See description.
    ///usage:  c = a * b;
    inline Matrix operator*(const Matrix& a, const Matrix& b)
    {
        if (a.getCols() != b.getRows())
        {
                    throw runtime_error("Error: Matrices don't match for multiplication.");
        }
        Matrix c(a.getRows(), b.getCols());
    
        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < b.getCols(); j++)
            {
                c(i, j) = 0;
                for (int k = 0; k < a.getCols(); k++)
                {
                    c(i, j) += a(i, k) * b(k, j);
                }
            }
        }
        return c;
    };

    ///Matrix comparison.  See description.
    ///usage:  a == b
inline bool operator==(const Matrix& a, const Matrix& b)
{
    if (a.getCols() != b.getCols() || a.getRows() != b.getRows())
        return false;

    const double EPSILON = 1e-5;
    for (int i = 0; i < a.getRows(); ++i)
    {
        for (int j = 0; j < a.getCols(); ++j)
        {
            if (fabs(a(i, j) - b(i, j)) > EPSILON)
                return false;
        }
    }
    return true;
}


    ///Matrix comparison.  See description.
    ///usage:  a != b
    inline bool operator!=(const Matrix& a, const Matrix& b)
    {
        if (a.getCols() != b.getCols() || a.getRows() != b.getRows())
        {
            return true;
        }
        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < a.getCols(); j++)
            {
                if (a(i,j) != b(i,j))
                {
                    return true;
                }
            }
        }
        return false;
    };

    ///Output matrix.
    ///Separate columns by ' ' and rows by '\n'
    inline ostream& operator<<(ostream& os, const Matrix& a)
    {
        for (int i = 0; i < a.getRows(); ++i)
        {
            for (int j = 0; j < a.getCols(); ++j)
            {
                os << std::setw(8) << a(i, j) << ' ';
            }
            os << '\n';
        }
        return os;
    };
};
    /*******************************************************************************/

    ///2D rotation matrix
    ///usage:  A = R * A rotates A theta radians counter-clockwise
namespace Matrices
{
class RotationMatrix : public Matrix
    {
        public:
            ///Call the parent constructor to create a 2x2 matrix
            explicit RotationMatrix(double theta)
            : Matrix(2, 2)
            ///Then assign each element as follows:
            /*
            cos(theta)  -sin(theta)
            sin(theta)   cos(theta)
            */
            {
                {
                    (*this)(0, 0) = cos(theta);  (*this)(0, 1) = -sin(theta);
                    (*this)(1, 0) = sin(theta);  (*this)(1, 1) = cos(theta);
                }
            }
    };

    ///2D scaling matrix
    ///usage:  A = S * A expands or contracts A by the specified scaling factor
class ScalingMatrix : public Matrix
    {
        public:
            ///Call the parent constructor to create a 2x2 matrix
            ///Then assign each element as follows:
            explicit ScalingMatrix(double scale)
            : Matrix(2, 2)
            /*
            scale   0
            0       scale
            */
            {
            (*this)(0, 0) = scale;  (*this)(0, 1) = 0;
            (*this)(1, 0) = 0;      (*this)(1, 1) = scale;
            }
    };

    ///2D Translation matrix
    ///usage:  A = T + A will shift all coordinates of A by (xShift, yShift)
class TranslationMatrix : public Matrix
    {
        public:
            ///Call the parent constructor to create a 2xn matrix
            explicit TranslationMatrix(double xShift, double yShift, int nCols)
            : Matrix(2, nCols)
            ///Then assign each element as follows:
            /*
            xShift  xShift  xShift  ...
            yShift  yShift  yShift  ...
            */
           {
            for (int i = 0; i < nCols; ++i)
            {
                (*this)(0, i) = xShift;
                (*this)(1, i) = yShift;
            }
            }
            ///paramaters are xShift, yShift, and nCols
            ///nCols represents the number of columns in the matrix
            ///where each column contains one (x,y) coordinate pair
    };
};
#endif // MATRIX_H_INCLUDED