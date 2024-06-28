#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <stdexcept>  // Include this to use std::invalid_argument

#include "../src/Algorithm.hpp"
#include "doctest.h"

TEST_CASE("Testing Simulation constructor with valid parameters") {
  Simulation sim1(2000, 45, 0.1, 0.02, 0.05, 0.1);
  CHECK(sim1.getXRelative() == doctest::Approx(2000 / (0.1 / 0.05)));
  CHECK(sim1.getYRelative() == doctest::Approx(45 / (0.1 / 0.02)));
}

TEST_CASE("Testing Simulation constructor with valid parameters") {
  Simulation sim2(4000, 100, 0.01, 0.002, 0.005, 0.01);
  CHECK(sim2.getXRelative() == doctest::Approx(4000 / (0.01 / 0.005)));
  CHECK(sim2.getYRelative() == doctest::Approx(100 / (0.01 / 0.002)));
}

TEST_CASE("Testing Simulation constructor with invalid parameters") {
  CHECK_THROWS_AS(Simulation(-2000, 45, 0.1, 0, 0.05, 0.1),
                  std::invalid_argument);
}

TEST_CASE("Testing Simulation constructor with invalid parameters") {
  CHECK_THROWS_AS(Simulation(-5, 0, 0.1, 0, 0.05, 0.1), std::invalid_argument);
}

// TEST_CASE("Testing Simulation constructor with edge valid parameters") {
//   Simulation sim1(1, 1, 1, 1, 1, 1);
//   CHECK(sim1.getXRelative() == doctest::Approx(1 / (1 / 1)));
//   CHECK(sim1.getYRelative() == doctest::Approx(1 / (1 / 1)));
// }
