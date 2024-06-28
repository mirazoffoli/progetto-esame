#include "Algorithm.hpp"

#include <cmath>
#include <fstream>
#include <iostream>

Simulation::Simulation(double x_parametro, double y_parametro,
                       double A_parametro, double B_parametro,
                       double C_parametro, double D_parametro) {
  // Simulation: metodo (cioè funzione dentro a una classe) per dare dei
  // valori
  // agli attributi (cioè alle variabili) della classe (qui, x, y, A, B, C)

  if (x_parametro <= 0 || y_parametro <= 0 || A_parametro <= 0 ||
      B_parametro <= 0 || C_parametro <= 0 || D_parametro <= 0) {
    std::cout << "Errore, valori non validi \n";
    throw std::invalid_argument("Invalid parameter value(s)");
  }
  // this è una parola chiave del linguaggio C++ che, usando la sintassi this
  // -> attributo = valore, ti consente di dare dei valori agli
  // attributi=variabili di una classe

  this->x = x_parametro;
  this->y = y_parametro;
  this->A = A_parametro;
  this->B = B_parametro;
  this->C = C_parametro;
  this->D = D_parametro;

  // Calcola i valori di equilibrio
  this->x_eq = D / C;
  this->y_eq = A / B;

  x_relative = x / x_eq;
  y_relative = y / y_eq;

  t = 0.0;
}

double Simulation::getXRelative() const { return x_relative; }

double Simulation::getYRelative() const { return y_relative; }

double Simulation::getH() const { return H; }

void Simulation::evolve() {
  // Calcola i nuovi valori di x e y e li assegna agli attributi della classe

  // x prede
  // A: quanto le prede si riproducono (senza predatori, le prede aumentano di
  // Ax a iterazione) B: tasso mortalità prede (che probabilità ha ogni
  // predatore di ammazzare una preda) C: quanto i predatori si riproducono D:
  // tasso mortalità predatori

  // Calcola i nuovi valori di x e y
  double dt = 0.001;  // Piccolo passo temporale
  double old_x = x;
  double old_y = y;

  double new_x = old_x + (A * old_x - B * old_x * old_y) * dt;
  double new_y = old_y + (C * old_x * old_y - D * old_y) * dt;

  // Assicurati che x e y non diventino zero o negativi
  if (new_x <= 0 || new_y <= 0) {
    std::cerr << "Errore: i valori di x e y non possono diventare zero o "
                 "negativi.\n";
    exit(1);
  }

  x = new_x;
  y = new_y;

  // Recalculate relative values
  if (x_eq != 0) {
    x_relative = x / x_eq;
  } else {
    x_relative = 0;  // Handle division by zero gracefully
  }

  if (y_eq != 0) {
    y_relative = y / y_eq;
  } else {
    y_relative = 0;  // Handle division by zero gracefully
  }

  // Calcola H(x, y)
  H = -D * log(x) + C * x + B * y - A * log(y);
  t += dt;

  // Se overflow, esco e segnalo errore
  if (std::isinf(new_x) || std::isinf(new_y)) {
    std::cerr << "Errore: overflow durante la simulazione.\n";
    exit(1);
  }

  std::cout << "Dopo evolve: x = " << x << ", y = " << y << "\n";
}

void Simulation::print() {
  std::cout << "x(" << t << ") = " << x << ", x_rel = " << x_relative
            << std::endl;
  std::cout << "y(" << t << ") = " << y << ", y_rel = " << y_relative
            << std::endl;
  // Stampa a schermo l'integrale primitivo H(x, y)
  std::cout << "H(" << x << ", " << y << ") = " << H << std::endl << std::endl;
};

void Simulation::save_to_file(const std::string& filename) {
  std::ofstream file(filename,
                     std::ios::app);  // Apri il file in modalità append
  if (!file.is_open()) {
    std::cerr << "Errore nell'apertura del file\n";
    return;
  }
  file << "x(" << t << ") = " << x << ", x_rel = " << x_relative << "\n";
  file << "y(" << t << ") = " << y << ", y_rel = " << y_relative << "\n";
  file << "H(" << x << ", " << y << ") = " << H << "\n";
  file.close();
};
