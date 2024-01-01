// Matrix class, capable of holding multi-dimensional solutions of systems.

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <memory>

#include "macros.hpp"

class Matrix;

class MatrixRow {
public:
    MatrixRow(const size_t n_cols);
    MatrixRow(MatrixRow&& r);

    MatrixRow(std::vector<double>&& v) : data_(v) {}

    double& operator[](const size_t i_col) {return data_[i_col]; };
    double operator[](const size_t i_col) const { return data_[i_col]; };

    const std::vector<double>& data() const { return data_; };

private:

    friend class Matrix;

    void resize(const size_t n_cols) 
    { 
        n_cols == data_.size() + 1u ? 
            data_.push_back(0.0) : 
            data_.resize(n_cols); 
    }

    std::vector<double> data_;
};

class Matrix {
public:
    Matrix(const size_t n_rows, const size_t n_cols);
    Matrix(Matrix&& m);

    ~Matrix();

    size_t n_rows() const { return n_rows_; };
    size_t n_cols() const { return n_cols_; };

    std::shared_ptr<MatrixRow> operator[](const size_t i_row) { return rows_[i_row]; };
    std::shared_ptr<const MatrixRow> operator[](const size_t i_row) const {return rows_[i_row]; };

    void insert_row(const std::vector<double>& r, const size_t i_row) { rows_[i_row] = std::make_shared<MatrixRow>(std::vector<double>(r.begin(), r.end())); }
    void insert_row(std::vector<double>&& r, const size_t i_row) { rows_[i_row] = std::make_shared<MatrixRow>(std::move(r)); }
    
    void resize(const size_t n_rows, const size_t n_cols);

private:
    size_t n_rows_;
    size_t n_cols_;

    std::vector<std::shared_ptr<MatrixRow>> rows_;

};

EXPORT_FUNCTION size_t get_matrix_n_rows(const Matrix* const m);
EXPORT_FUNCTION size_t get_matrix_n_cols(const Matrix* const m);
EXPORT_FUNCTION double get_matrix_element(const Matrix* const m, const size_t i_row, const size_t i_col);
EXPORT_FUNCTION void delete_matrix(Matrix const* m);

#endif