#include "catch.hpp"
#include <gmpp/integer.hpp>
#include <limits>

TEST_CASE("default constructed gmpp::integer are equal", "[gmpp][integer]")
{
    gmpp::integer a;
    REQUIRE(a.compare(gmpp::integer{}) == 0);
}

TEST_CASE("default constructed gmpp::integer is equal to gmpp::integer{0}", "[gmpp][integer]")
{
    gmpp::integer a;
    REQUIRE(a.compare(gmpp::integer{0}) == 0);
}

TEST_CASE("compare greater", "[gmpp][integer]")
{
    gmpp::integer one{1};
    gmpp::integer two{2};

    SECTION("using gmpp::integer::compare") {
        CHECK(one.compare(two) < 0);
        CHECK(two.compare(one) > 0);
    }

    SECTION("using helper operators") {
        CHECK(one < two);
        CHECK(two > one);
        CHECK(one != two);
    }
}

TEST_CASE("add gmpp::integer", "[gmpp][integer][add]")
{
    const gmpp::integer expected{42};
    REQUIRE(expected == (gmpp::integer{20} + gmpp::integer{22}));
}

TEST_CASE("subtract gmpp::integer", "[gmpp][integer][sub]")
{
    const gmpp::integer expected{42};
    REQUIRE(expected == (gmpp::integer{62} - gmpp::integer{20}));
}

TEST_CASE("multiply gmpp::integer", "[gmpp][integer][mul]")
{
    const gmpp::integer expected{42};
    REQUIRE(expected == (gmpp::integer{21} * gmpp::integer{2}));
}

TEST_CASE("divide floor gmpp::integer quotient", "[gmpp][integer][fdiv][div]")
{
    gmpp::integer value{10};
    value.div_floor_quotient(gmpp::integer{3});

    REQUIRE(value == gmpp::integer{3});
}

TEST_CASE("divide floor gmpp::integer reminder", "[gmpp][integer][fdiv][div]")
{
    gmpp::integer value{10};
    value.div_floor_reminder(gmpp::integer{3});

    REQUIRE(value == gmpp::integer{1});
}

TEST_CASE("divide floor gmpp::integer q/r", "[gmpp][integer][fdiv][div]")
{
    gmpp::integer value{10};
    auto ret = value.div_floor_qr(gmpp::integer{3});

    CHECK(ret.quotient == gmpp::integer{3});
    CHECK(ret.reminder == gmpp::integer{1});

    // alternative syntax:
    // auto [q, r] = value.div_floor_qr(gmpp::integer{3});
}

TEST_CASE("divide ceil gmpp::integer", "[gmpp][integer][cdiv][div]")
{
    gmpp::integer value{10};
    value.div_ceil_quotient(gmpp::integer{3});

    REQUIRE(value == gmpp::integer{4});
}

TEST_CASE("div operator easy syntax", "[gmpp][integer][div][operator]")
{
    using namespace gmpp::literals;
    auto [q, r] = 10_bi / 3_bi;
    CHECK(q == 3_bi);
    CHECK(r == 1_bi);

    auto q1 = quotient(10_bi / 3_bi);
    CHECK(q1 == 3_bi);

    auto r2 = reminder(10_bi / 3_bi);
    CHECK(r2 == 1_bi);
}

TEST_CASE("gmpp::integer fits", "[gmpp][integer][fits]")
{
    gmpp::integer a{std::numeric_limits<unsigned short>::max()};
    CHECK(a.fits<unsigned short>());

    // a++, no longer fits
    a.add(gmpp::integer{1});
    CHECK(a.fits<unsigned short>() == false);

    // but should fit in long
    CHECK(a.fits<unsigned long>());
}

TEST_CASE("gmpp::integer to string", "[gmpp][integer][to_string]")
{
    gmpp::integer a{42};
    CHECK(a.to_string() == "42");
}

TEST_CASE("increment and decrement operators", "[gmpp][integer][increment][decrement]")
{
    gmpp::integer a{10};
    REQUIRE(++a == gmpp::integer{11});
    REQUIRE(a++ == gmpp::integer{11});
    REQUIRE(a == gmpp::integer{12});
    REQUIRE(--a == gmpp::integer{11});
    REQUIRE(a-- == gmpp::integer{11});
    REQUIRE(a == gmpp::integer{10});
}