#include "../../doctest.h"
#include "../../../include/pl/algo/clamp.hpp"

TEST_CASE("clamp_test")
{
    CHECK(pl::algo::clamp(3, 2, 4) == 3);
    CHECK(pl::algo::clamp(3, 4, 5) == 4);
    CHECK(pl::algo::clamp(3, 1, 2) == 2);
}
