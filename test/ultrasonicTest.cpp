#define BOOST_TEST_MODULE UltrasonicTest
#include <boost/test/unit_test.hpp>

#include "../src/os/ultrasonicSensorClass.h"

BOOST_AUTO_TEST_CASE(UltrasonicTest)
{
    //ultrasonicSensorClass s = ultrasonicSensorClass("18", "24");
    BOOST_CHECK_EQUAL(1, 1);
}