#include <catch2/catch_test_macros.hpp>

TEST_CASE("2*2=4", "[mult]")
{
    REQUIRE(2 * 2 == 4);
}