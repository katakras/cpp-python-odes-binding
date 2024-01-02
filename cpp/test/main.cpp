#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

#include "matrix.hpp"


BOOST_AUTO_TEST_CASE(matrix_test)
{
    auto matrix = std::make_shared<Matrix>(1u, 1u);
    BOOST_CHECK_EQUAL(matrix->n_cols(), 1u);
    BOOST_CHECK_EQUAL(matrix->n_rows(), 1u);
}
