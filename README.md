# progetto-esame

## Compilare con Cmake
Dalla cartella principale del progetto (progetto-esame):
```bash
cmake -S . -B ../build
``` 
Verranno creati del file nella cartella build

Spostati nella cartella build e compila il progetto:
``` bash
cd build
make
``` 

Nella cartella build verrà compilato l'eseguibile main, che puoi eseguire

L'eseguibile prodotto si chiama `main` 


Per compilare codice simulazione:
g++ -std=c++11 src/algorithm.cpp src/main_algorithm.cpp -o main_algorithm
./main_algorithm

Per compilare i test:
g++ -std=c++11 test/test_simulazione.cpp src/algorithm.cpp -o test_simulazione
Poi:
./test_simulazione


compilare con cmake:
in build : rm -rf build/*
           cmake ..
           make
           ./main
           /all.t oppure ctest
           
