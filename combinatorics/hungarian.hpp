#pragma once

#include<limits>
#include<vector>
#include<stdexcept>
#include "../math/matrix.hpp"

const size_t MAX_INDEX = std::numeric_limits<size_t>::max();

/**
 * Creates a zero by minimizing a(i, j) - u(i) + v(j), by doing two operations incrementing u and/or v.
 * @param u A vector for each row
 * @param v A vector for each column
 * @param row_mate A vector matching columns to rows
 * @param col_mate A vector matching rows to columns
 * @param row_dad A vector matching columns to parent rows
 * @param row_slack A vector matching columns to slack rows
 **/
template <class T>
std::pair<size_t, size_t> find_zero(const matrix_t<T>& a,
                                    std::vector<T>& u, 
                                    std::vector<T>& v,
                                    std::vector<size_t>& row_mate,
                                    std::vector<size_t>& col_mate,
                                    std::vector<size_t>& row_dad,
                                    std::vector<size_t>& row_slack)
{
    static const T INF = std::numeric_limits<T>::max();

    std::vector<T> slack(a.cols(), INF);
    std::fill(row_dad.begin(), row_dad.end(), MAX_INDEX);
    std::vector<size_t> unmatched_row;
    for (size_t i=0; i<a.rows(); i++)
        if (col_mate[i] == MAX_INDEX)
            unmatched_row.push_back(i);

    while (true)
    {
        for (size_t q=0; q<unmatched_row.size(); ++q)
        {
            size_t i = unmatched_row[q];
            for (size_t j=0; j<a.cols(); ++j)
                if (slack[j] != 0)
                {
                    if (a(i, j) - u[i] + v[j] < slack[j])
                    {
                        slack[j] = a(i, j) - u[i] + v[j];
                        if (slack[j] == 0)
                        {
                            if (row_mate[j] == MAX_INDEX)
                                return std::make_pair(i, j);
                            row_dad[j] = i;
                            unmatched_row.push_back(row_mate[j]);
                        }
                        else row_slack[j] = i;
                    }
                }
        }

        T s = INF;
        for (size_t j=0; j<a.cols(); ++j)
            if (slack[j] != 0 && slack[j] < s)
                s = slack[j];

        for (size_t q=0; q<unmatched_row.size(); ++q)
            u[unmatched_row[q]] += s;

        for (size_t j=0; j<a.cols(); ++j)
            if (slack[j] != 0)
            {
                slack[j] -= s;
                if (slack[j] == 0)
                {
                    size_t i = row_slack[j];
                    if (row_mate[j] == MAX_INDEX)
                    {
                        for (size_t k=j+1; k<a.cols(); ++k)
                            if (slack[k] == 0)
                                v[k] += s;
                        return std::make_pair(i, j);
                    }
                    else
                    {
                        row_dad[j] = i;
                        unmatched_row.push_back(row_mate[j]);
                    }
                }
            }
            else {
                v[j] += s; //increasing zeros
            }
    }
}

/**
 * The Hungarian method is a combinatorial optimization algorithm that solves the assignment problem in polynomial time.
 **/
template <class T>
std::vector<size_t> hungarian(const matrix_t<T>& a)
{
    if (a.rows() != a.cols())
        throw new std::length_error("Must be square matrix");

    std::vector<T> u(a.rows(), 0);
    std::vector<T> v(a.cols(), 0);
    std::vector<size_t> row_mate(a.cols(), MAX_INDEX);
    std::vector<size_t> col_mate(a.rows(), MAX_INDEX);
    std::vector<size_t> row_dad(a.cols(), MAX_INDEX);
    std::vector<size_t> row_slack(a.cols(), MAX_INDEX);

    size_t unmatched = 0;
    for (size_t i=0; i<a.rows(); ++i) 
    {
        size_t pos = 0;
        for (size_t j=1; j<a.cols(); ++j)
            if (a(i, j) < a(i, pos)) 
                pos = j;
        u[i] = a(i, pos);
        if (row_mate[pos] == MAX_INDEX) 
        {
            row_mate[pos] = i;
            col_mate[i] = pos;
        } 
        else ++unmatched;
    }

    for (size_t t=0; t<unmatched; ++t) 
    {
        std::pair<size_t, size_t> ret = find_zero<T>(a, u, v, row_mate, col_mate, row_dad, row_slack);
        size_t i = ret.first;
        size_t j = ret.second;
        while (true) {
            size_t temp = col_mate[i];
            col_mate[i] = j;
            row_mate[j] = i;
            if (temp == MAX_INDEX) break;
            i = row_dad[temp];
            j = temp;
        }
    }
    return col_mate;
}
