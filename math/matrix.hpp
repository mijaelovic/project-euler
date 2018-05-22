#pragma once

#include<vector>
#include<stdexcept>

/**
 * A numerical matrix.
 **/
template <class T>
class matrix_t
{
private:
    std::vector<T> m_mtx;
    size_t m_rows;
    size_t m_cols;
public:
    matrix_t(size_t r, size_t c) : 
        m_rows(r), m_cols(c), m_mtx(r * c, 0) 
    {
    }
    template <size_t r, size_t c>
    matrix_t(T (&a)[r][c]) :
        m_rows(r), m_cols(c), m_mtx(r * c, 0)
    {
        for (size_t i=0; i<m_rows; ++i)
            for (size_t j=0; j<m_cols; ++j)
                (*this)(i, j) = a[i][j];
    }
    matrix_t<T>& operator = (const matrix_t<T>& rhs)
    {
        if (this != rhs)
        {
            m_rows = rhs.m_rows;
            m_cols = rhs.m_cols;
            m_mtx = rhs.m_mtx;
        }
        return *this;
    }
    const matrix_t<T> operator -() const
    {
        matrix_t<T> ret = *this;
        for (size_t i=0; i<m_rows; ++i)
            for (size_t j=0; j<m_cols; ++j)
                ret(i, j) = -ret(i, j);
        return ret;
    }
    T& operator()(size_t i, size_t j) 
    {
        if (i > m_rows)
            throw new std::out_of_range("Row index out of range");
        if (j > m_cols)
            throw new std::out_of_range("Col index out of range");
        return m_mtx[i * m_cols + j];
    }
    T operator()(size_t i, size_t j) const
    {
        if (i > m_rows)
            throw new std::out_of_range("Row index out of range");
        if (j > m_cols)
            throw new std::out_of_range("Col index out of range");
        return m_mtx[i * m_cols + j];
    }
    const size_t rows() const
    {
        return m_rows;
    }
    const size_t cols() const
    {
        return m_cols;
    }
    const matrix_t<T> operator * (const matrix_t<T>& rhs) const 
    {
        if (m_cols != rhs.m_rows)
            throw new std::length_error("Different number of columns and rows");
        matrix_t<T> ret(m_rows, rhs.cols);
        for (size_t i=0; i<m_rows; ++i)
            for (size_t j=0; j<m_cols; ++j)
                for (size_t k=0; k<rhs.m_cols; ++k)
                    ret(i, k) += (*this)(i, j) * rhs(j, k);
        return ret;
    }
};

