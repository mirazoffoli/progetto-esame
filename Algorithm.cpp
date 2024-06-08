
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
// dovrei mettere double al posto di long?

#include <cmath>
#include <fstream>
#include <iostream>

class Simulation {
 private:
  long x, y;                      // popolazione prede e predatori
  double x_relative, y_relative;  // valori relativi delle popolazioni
  double A, B, C, D;              // parametri eq Lotka-Volterra
  // vanno aggiusti i valri di equilibrio double x_eq, y_eq;
  long t;

 public:
  Simulation(long x_parametro, long y_parametro, double A_parametro,
             double B_parametro, double C_parametro, double D_parametro) {
    // Simulation: metodo (cioè funzione dentro a una classe) per dare dei
    // valori
    // agli attributi (cioè alle variabili) della classe (qui, x, y, A, B, C)

    if (x_parametro <= 0 || y_parametro <= 0 || A_parametro <= 0 ||
        B_parametro <= 0 || C_parametro <= 0 || D_parametro <= 0) {
      std::cout << "Errore, valori non validi \n";
      exit(1);  // Esce dal programma se i valori non sono validi
    }

    // Calcola i valori di equilibrio
    // this->x_eq = D / C;
    // this->y_eq = A / B;

    // this è una parola chiave del linguaggio C++ che, usando la sintassi this
    // -> attributo = valore, ti consente di dare dei valori agli
    // attributi=variabili di una classe
    // this->x = x_parametro / x_eq;
    // this->y = y_parametro / y_eq;
    this->x = x_parametro;
    this->y = y_parametro;
    this->A = A_parametro;
    this->B = B_parametro;
    this->C = C_parametro;
    this->D = D_parametro;
    this->t = 0;
  }

  void evolve() {
    // Calcola i nuovi valori di x e y e li assegna agli attributi della classe

    print();
    // x prede
    // A: quanto le prede si riproducono (senza predatori, le prede aumentano di
    // Ax a iterazione) B: tasso mortalità prede (che probabilità ha ogni
    // predatore di ammazzare una preda) C: quanto i predatori si riproducono D:
    // tasso mortalità predatori

    // Print all simulation parameters for debugging purposes
    std::cout << "A = " << A << ", B = " << B << ", C = " << C << ", D = " << D
              << "\n";
    x += round((A - B * y) * x);
    y += round((C * x - D) * y);
    t++;

    // Assicurati che x e y non diventino zero
    if (x <= 0 || y <= 0) {
      std::cerr << "Errore: i valori di x e y non possono diventare zero.\n";
      exit(1);
    }

    // Calcolo del valore di H(x, y)
    double H = -D * log(x) + C * x + B * y - A * log(y);
    std::cout << "H(" << x << ", " << y << ") = " << H << std::endl;

    // Se overflow, esco e segnalo errore
    if (std::isinf(x) || std::isinf(y)) {
      std::cerr << "Errore: overflow durante la simulazione.\n";
      exit(1);
    }

    std::cout << "Dopo evolve: x = " << x << ", y = " << y << "\n";
  }

  void print() {
    std::cout << "x(" << t << ") = " << x << std::endl;
    std::cout << "y(" << t << ") = " << y << std::endl;
    // Stampa a schermo l'integrale primitivo H(x, y)
    std::cout << "H(" << x << ", " << y << ") = " << std::endl;
  };
  void save_to_file(const std::string& filename) {
    std::ofstream file(filename,
                       std::ios::app);  // Apri il file in modalità append
    if (!file.is_open()) {
      std::cerr << "Errore nell'apertura del file\n";
      return;
    }
    file << "x(" << t << ") = " << x << "\n";
    file << "y(" << t << ") = " << y << "\n";
    file << "H(" << x << ", " << y << ") = \n";
    file.close();
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

  // // Creazione dell'istanza della simulazione con i valori forniti
  // dall'utente Simulation sim(x_iniziale, y_iniziale, A, B, C, D);
  Simulation sim(1000, 1000, 0.02, 0.001, 0.0015, 0.0003);

  // Esegue la simulazione per un certo numero di passi
  int steps;
  std::cout << "Quanti passi vuoi simulare? ";
  std::cin >> steps;
  for (int i = 0; i < steps; ++i) {
    sim.evolve();
    sim.save_to_file("simulation_output.txt");
  }

  // Stampa lo stato finale della simulazione
  std::cout << "Stato della simulazione dopo l'evoluzione:\n";
  sim.print();

  return 0;
};