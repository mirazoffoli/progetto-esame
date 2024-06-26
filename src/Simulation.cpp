
#include "Simulation.hpp"

#include <sstream>

Simulation::Simulation(double x_parametro, double y_parametro,
                       double A_parametro, double B_parametro,
                       double C_parametro, double D_parametro) {
  if (x_parametro <= 0 || y_parametro <= 0 || A_parametro <= 0 ||
      B_parametro <= 0 || C_parametro <= 0 || D_parametro <= 0) {
    std::cout << "Errore, valori non validi \n";
    exit(1);
  }

  this->x = x_parametro;
  this->y = y_parametro;
  this->A = A_parametro;
  this->B = B_parametro;
  this->C = C_parametro;
  this->D = D_parametro;

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
  double dt = 0.001;
  double old_x = x;
  double old_y = y;

  double new_x = old_x + (A * old_x - B * old_x * old_y) * dt;
  double new_y = old_y + (C * old_x * old_y - D * old_y) * dt;

  if (new_x <= 0 || new_y <= 0) {
    std::cerr
        << "Errore: i valori di x e y non possono diventare zero o negativi.\n";
    exit(1);
  }

  x = new_x;
  y = new_y;

  if (x_eq != 0) {
    x_relative = x / x_eq;
  } else {
    x_relative = 0;
  }

  if (y_eq != 0) {
    y_relative = y / y_eq;
  } else {
    y_relative = 0;
  }

  H = -D * log(x) + C * x + B * y - A * log(y);
  t += dt;

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
  std::cout << "H(" << x << ", " << y << ") = " << H << std::endl << std::endl;
}

std::string Simulation::get_print_output() const {
  std::stringstream ss;
  ss << "x(" << t << ") = " << x << ", x_rel = " << x_relative << "\n";
  ss << "y(" << t << ") = " << y << ", y_rel = " << y_relative << "\n";
  ss << "H(" << x << ", " << y << ") = " << H << "\n";
  return ss.str();
}

void Simulation::save_to_file(const std::string& filename) {
  std::ofstream file(filename, std::ios::app);
  if (!file.is_open()) {
    std::cerr << "Errore nell'apertura del file\n";
    return;
  }
  file << "x(" << t << ") = " << x << ", x_rel = " << x_relative << "\n";
  file << "y(" << t << ") = " << y << ", y_rel = " << y_relative << "\n";
  file << "H(" << x << ", " << y << ") = " << H << "\n";
  file.close();
}
