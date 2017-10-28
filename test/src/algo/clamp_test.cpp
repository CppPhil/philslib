#include "../../doctest.h"
#include "../../../include/pl/algo/clamp.hpp"
#include <functional> // std::greater

TEST_CASE("clamp_test")
{
    CHECK(pl::algo::clamp(3, 2, 4) == 3);
    CHECK(pl::algo::clamp(3, 4, 5) == 4);
    CHECK(pl::algo::clamp(3, 1, 2) == 2);
}

TEST_CASE("clamp_test_comparator")
{
    CHECK(pl::algo::clamp(1, 2,  0, std::greater<>{ }) == 1);
    CHECK(pl::algo::clamp(1, 0, -1, std::greater<>{ }) == 0);
    CHECK(pl::algo::clamp(1, 3,  2, std::greater<>{ }) == 2);
}
