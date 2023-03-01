#define BOOST_TEST_MODULE HelloworldTests
#include <boost/test/unit_test.hpp>

#include "../src/helloworld.h"

// BOOST_AUTO_TEST_CASE(FailTest)
// {
//     BOOST_CHECK_EQUAL(5, hello(1));
// }

BOOST_AUTO_TEST_CASE(PassTest)
{
    BOOST_CHECK_EQUAL(7, hello(2));
}