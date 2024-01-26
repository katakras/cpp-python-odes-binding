#include <boost/test/unit_test.hpp>

#include "lib/matrix.hpp"

BOOST_AUTO_TEST_SUITE(matrices)

BOOST_AUTO_TEST_CASE(matrix_creation)
{
    auto matrix = std::make_shared<Matrix>(1u, 1u);
    BOOST_CHECK_EQUAL(matrix->n_cols(), 1u);
    BOOST_CHECK_EQUAL(matrix->n_rows(), 1u);
}

BOOST_AUTO_TEST_CASE(matrix_resizing)
{
    auto matrix = std::make_shared<Matrix>(1u, 1u);
    matrix->resize(2u, 2u);
    BOOST_CHECK_EQUAL(matrix->n_cols(), 2u);
    BOOST_CHECK_EQUAL(matrix->n_rows(), 2u);
}

BOOST_AUTO_TEST_SUITE_END()
