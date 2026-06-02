#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "math_utils.h"

TEST_CASE("testing add function")
{
    CHECK(add(1, 2) == 3);
    CHECK(add(-1, 1) == 0);
    CHECK(add(0, 0) == 0);
    CHECK(add(100, 99) == 199);
    CHECK(add(200, 199) == 399);
    CHECK(add(-5, -3) == -8);
}
