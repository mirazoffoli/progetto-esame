#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

class Simulation {
 private:
  double x, y;                    // popolazione prede e predatori
  double x_relative, y_relative;  // valori relativi delle popolazioni
  double A, B, C, D;              // parametri eq Lotka-Volterra
  double x_eq, y_eq;  // valori di equilibrio (dovrebbero stabilizzarsi ad 1 se
                      // il sistema è in equilibrio)
  double H;           // Valore di H(x, y)
  double t;

 public:
  Simulation(double x_parametro, double y_parametro, double A_parametro,
             double B_parametro, double C_parametro, double D_parametro);

  double getXRelative() const;
  double getYRelative() const;
  double getH() const;
  void evolve();
  void print();
  std::string get_print_output() const;  // New method to get output as string
  void save_to_file(const std::string& filename);
};

#endif  // SIMULATION_HPP
