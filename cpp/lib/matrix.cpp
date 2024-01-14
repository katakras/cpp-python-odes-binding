#include <utility>

#include "matrix.hpp"

MatrixRow::MatrixRow(const size_t n_cols) : data_(n_cols, 0.0)
{    
}

MatrixRow::MatrixRow(MatrixRow&& r) : data_(std::move(r.data_))
{    
}

namespace
{
    std::vector<std::shared_ptr<MatrixRow>> create_initial_matrix_data(const size_t n_rows, const size_t n_cols)
    {
        const auto& make_row = [&n_cols](){return std::make_shared<MatrixRow>(n_cols); };
        return std::vector<std::shared_ptr<MatrixRow>>(n_rows, make_row());
    }
}

Matrix::Matrix(const size_t n_rows, const size_t n_cols) : 
    n_rows_(n_rows), n_cols_(n_cols), rows_(create_initial_matrix_data(n_rows, n_cols))
{
}

Matrix::Matrix(Matrix&& m) : n_rows_(m.n_rows_), n_cols_(m.n_cols_), rows_(std::move(m.rows_))
{
}

Matrix::Matrix(const Matrix& m) : n_rows_(m.n_rows_), n_cols_(m.n_cols_), rows_(m.rows_)
{
}

Matrix::~Matrix()
{
}

void Matrix::resize(const size_t n_rows, const size_t n_cols)
{
    const bool resizes_rows = n_cols == n_cols_ ? false : true;
    n_rows_ = n_rows;
    n_cols_ = n_cols;
    if(resizes_rows) 
    {
        for(auto& row : rows_)
        {
            row->resize(n_cols);
        }
    }
    rows_.resize(n_rows, std::make_shared<MatrixRow>(n_cols));
}


size_t get_matrix_n_cols(const Matrix* const m) 
{ 
    return m->n_cols(); 
}

double get_matrix_element(const Matrix* const m, const size_t i_row, const size_t i_col) 
{
    const auto& row = (*m)[i_row]; 
    return (*row)[i_col];
}

void delete_matrix(Matrix const* m) 
{ 
    delete m; 
}