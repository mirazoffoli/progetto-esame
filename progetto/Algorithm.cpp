
// Scrivi una classe Simulation
// Con i metodi:
// - metodo costruttore che prende in input i valori iniziali di x e di y e A,
// B, C e D, controllando che questi ultimi siano validi e lanciando un errore
// in c.
// - metodo evolve() che manda avanti di t=1 la simulazione in base alle
// equazioni nella traccia
// - un metodo che stampi a schermo lo stato della simulazione (cioè il valore
// di x e y)
// cambiare nomi variabili e mettere _parametro
// perchè simulazione va a p?
// deve chiedere di inserire dei dati A B C .. e xy iniziali
//

#include <cmath>
#include <iostream>

class Simulation {
 private:
  double x, y;        // popolazione prede e predatori
  double A, B, C, D;  // parametri eq Lotka-Volterra
  double dt;

 public:
  // Simulation: metodo (cioè funzione dentro a una classe) per dare dei valori
  // agli attributi (cioè alle variabili) della classe (qui, x, y, A, B, C)
  Simulation(double x_parametro, double y_parametro, double A_parametro,
             double B_parametro, double C_parametro, double D_parametro,
             double dt_parametro) {
    if (x_parametro <= 0 || y_parametro <= 0 || A_parametro <= 0 ||
        B_parametro <= 0 || C_parametro <= 0 || D_parametro <= 0) {
      std::cout << "Errore, valori non validi \n";
      exit(1);  // Esce dal programma se i valori non sono validi
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
    this->dt = dt_parametro;
  }

  void evolve() {
    double new_x = x + ((A - B * y) * x) * dt;
    double new_y = y + ((C * x - D) * y) * dt;
  };
  void print() {
    std::cout << "Stato della simulazione:\n";
    std::cout << "Prede (x) = " << x << "\n";
    std::cout << "Predatori (y) = " << y << "\n";
  };
};
int main() {
  double x_iniziale, y_iniziale, A, B, C, D, dt;

  // Richiesta di inserimento dei dati iniziali all'utente
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
  std::cout << "Inserisci il passo temporale (dt): ";
  std::cin >> dt;

  // Creazione dell'istanza della simulazione con i valori forniti dall'utente
  Simulation sim(x_iniziale, y_iniziale, A, B, C, D, dt);

  // Creazione di un'istanza della simulazione con valori iniziali validi
  // Simulation sim(10.0, 5.0, 1.1, 0.4, 0.1, 0.4, 20);

  // Esegue la simulazione per un certo numero di passi
  int steps = 100;
  for (int i = 0; i < steps; ++i) {
    sim.evolve();
  }

  // Stampa lo stato finale della simulazione
  std::cout << "Stato della simulazione dopo l'evoluzione:\n";
  sim.print();

  return 0;
}
