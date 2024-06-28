#include <cmath>
#include <fstream>
#include <iostream>

#include "Algorithm.hpp"

int main(int argc, char* argv[]) {
  double x_iniziale, y_iniziale, A, B, C, D, dt;

  if (argc != 7 && argc != 1) {
    std::cerr << "Inserire 0 o 6 parametri da riga di comando" << std::endl;
    return 1;
  }
  if (argc == 7) {
    x_iniziale = std::stod(argv[1]);
    y_iniziale = std::stod(argv[2]);
    A = std::stod(argv[3]);
    B = std::stod(argv[4]);
    C = std::stod(argv[5]);
    D = std::stod(argv[6]);
  }

  else if (argc == 1) {
    std::cout << "Inserisci il numero iniziale di prede (x): ";
    std::cin >> x_iniziale;
    std::cout << "Inserisci il numero iniziale di predatori (y): ";
    std::cin >> y_iniziale;
    std::cout << "Inserisci il valore del parametro A: ";
    std::cin >> A;
    std::cout << "Inserisci il valore del parametro B: ";
    std::cin >> B;
    std::cout << "Inserisci il valore del parametro C: ";
    std::cin >> C;
    std::cout << "Inserisci il valore del parametro D: ";
    std::cin >> D;
  }

  Simulation sim(x_iniziale, y_iniziale, A, B, C, D);

  // Eseguo la simulazione
  int steps;
  std::cout << "Quanti passi vuoi simulare? ";
  std::cin >> steps;

  for (int i = 0; i < steps; ++i) {
    sim.evolve();
    // Print the values and save to file
    sim.print();
    sim.save_to_file("simulation_output.txt");
  }

  sim.print();

  // Accessing private member variables via public getter methods
  std::cout << "Verifica dei risultati:" << std::endl;
  std::cout << "Punti di equilibrio: x_eq = " << D / C << ", y_eq = " << A / B
            << std::endl;
  std::cout << "Stabilità dei punti di equilibrio (x_rel, y_rel): ("
            << sim.getXRelative() << ", " << sim.getYRelative() << ")"
            << std::endl;
  std::cout << "Valore del Hamiltoniano H(x, y): " << sim.getH() << std::endl;

  return 0;
};