#include <cmath>
#include <fstream>
#include <iostream>

#include "Simulation.hpp"

// Inserimento dei parametri da riga di comando a tempo di esecuzione
void insert_parameters(SimulationParameters &params) {
  std::cout << "Inserisci il numero iniziale di prede (x): ";
  std::cin >> params.initial_x;
  std::cout << "Inserisci il numero iniziale di predatori (y): ";
  std::cin >> params.initial_y;
  std::cout << "Inserisci il valore del parametro A: ";
  std::cin >> params.A;
  std::cout << "Inserisci il valore del parametro B: ";
  std::cin >> params.B;
  std::cout << "Inserisci il valore del parametro C: ";
  std::cin >> params.C;
  std::cout << "Inserisci il valore del parametro D: ";
  std::cin >> params.D;
  std::cout << "Inserisci il passo temporale dt: ";
  std::cin >> params.dt;
}

void insert_steps(int &steps) {
  std::cout << "Quanti passi vuoi simulare? ";
  std::cin >> steps;
}

int main(int argc, char *argv[]) {
  SimulationParameters params;

  // Numero di passi da simulare
  int steps;

  // Numero sbagliato di parametri
  if (argc != 8 && argc != 1) {
    std::cerr << "Inserire 0 o 6 parametri da riga di comando" << std::endl;
    return 1;
  }

  // Parametri specificati come argomenti di invocazione
  if (argc == 8) {
    params.initial_x = std::stod(argv[1]);
    params.initial_y = std::stod(argv[2]);
    params.A = std::stod(argv[3]);
    params.B = std::stod(argv[4]);
    params.C = std::stod(argv[5]);
    params.D = std::stod(argv[6]);
    steps = std::stoi(argv[7]);
  }
  // Parametri specificati da riga di comando
  else if (argc == 1) {
    insert_parameters(params);
    insert_steps(steps);
  }

  Simulation sim(params);

  for (int i = 0; i < steps; ++i) {
    sim.evolve();
    // Print the values and save to file
    sim.print();
    sim.save_to_file("simulation_output.txt");
  }

  sim.print();
};