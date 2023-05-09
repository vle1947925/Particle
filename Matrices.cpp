#include "Matrices.h"

namespace Matrices
{
    RotationMatrix::RotationMatrix(double theta) : Matrix(2, 2)
    {
        double cosTheta = cos(theta);
        double sinTheta = sin(theta);

        a[0][0] = cosTheta;
        a[0][1] = -sinTheta;
        a[1][0] = sinTheta;
        a[1][1] = cosTheta;

    }

    ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2)
    {
        a[0][0] = scale;
        a[0][1] = 0;
        a[1][0] = 0;
        a[1][1] = scale;
    }

    TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols)
    {
        for (int j = 0; j < nCols; j++)
        {
            a[0][j] = xShift;
            a[1][j] = yShift;
        }
    }

    Matrix::Matrix(int _rows, int _cols)
    {
        rows = _rows;
        cols = _cols;

        a.resize(rows);

        for (size_t i = 0; i < rows; i++)
        {
            a[i].resize(cols);
            for (size_t j = 0; j < cols; j++)
            {
                a[i][j] = 0;
            }
        }
        a.resize(rows, vector<double>(cols, 0));
    }

    Matrix operator+(const Matrix& a, const Matrix& b)
    {
        Matrix c(a.getRows(), b.getCols());
        if ((a.getRows() != b.getRows()) || (a.getCols() != b.getCols()))
        {
            throw runtime_error("Error: dimensions must agree");
        }

        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < b.getCols(); j++)
            {
                c(i, j) = a(i, j) + b(i, j);
            }
        }
        return c;
    }

    Matrix operator*(const Matrix& a, const Matrix& b)
    {
        if (a.getCols() != b.getRows())
        {
            throw runtime_error("Error: dimensions must agree");
        }
        Matrix c(a.getRows(), b.getCols());
        for (int i = 0; i < a.getRows(); i++)
        {
            for (int k = 0; k < b.getCols(); k++)
            {
                for (int j = 0; j < a.getCols(); j++)
                {
                    c(i, k) += a(i, j) * b(j, k);
                }
            }
        }
        return c;
    }

    bool operator==(const Matrix& a, const Matrix& b)
    {
        if ((a.getRows() != b.getRows()) && (a.getCols() != b.getCols()))
        {
            return false;
        }

        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < b.getRows(); j++)
            {
                if (fabs(a(i, j) - b(i, j)) < 0.001)
                {
                    return false;
                    break;
                }
            }
        }
        return true;
    }

    bool operator!=(const Matrix& a, const Matrix& b)
    {
        if ((a.getRows() == b.getRows()) && (a.getCols() == b.getCols()))
        {
            return false;
        }

        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < b.getRows(); j++)
            {
                if (fabs(a(i, j) - b(i, j)) > 0.001)
                {
                    return false;
                    break;
                }
            }
        }
        return true;

    }

    ostream& operator<<(ostream& os, const Matrix& a)
    {
        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < a.getCols(); j++)
            {
                os << setw(15) << a(i, j) << " ";
            }
            os << endl;
        }
        return os;
    }


}