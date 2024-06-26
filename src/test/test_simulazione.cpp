#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../Simulation.hpp"
#include "../doctest.h"

TEST_CASE("Testing Simulation class") {
  Simulation sim(10, 5, 1.0, 0.1, 0.1, 1.0);

  CHECK(sim.getXRelative() > 0);
  CHECK(sim.getYRelative() > 0);
  CHECK(sim.getH() != doctest::Approx(0.0));

  sim.evolve();

  CHECK(sim.getXRelative() > 0);
  CHECK(sim.getYRelative() > 0);
  CHECK(sim.getH() != doctest::Approx(0.0));

  // Verify the output
  std::string output = sim.get_print_output();
  CHECK(output.find("x(") != std::string::npos);
  CHECK(output.find("y(") != std::string::npos);
  CHECK(output.find("H(") != std::string::npos);
}
