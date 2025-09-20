# OptimisationTP (C++)

C++ implementations for optimization and metaheuristic algorithms from coursework.

## Contents
- **TPPartie1.cpp** — introductory optimization algorithms
- **TPPartie2.cpp** — exact methods and heuristics
- **TP3-Metaheuristiques.cpp** — local search / simulated annealing / tabu search
- **TP1_GU_ZHANG.pdf**, **TP2_GU_ZHANG.pdf** — project statements and write-ups

## Build
```sh
g++ -O2 -std=c++17 TPPartie1.cpp -o tp1
g++ -O2 -std=c++17 TPPartie2.cpp -o tp2
g++ -O2 -std=c++17 TP3-Metaheuristiques.cpp -o tp3
```
## Run
```sh
./tp1 [args...]
./tp2 [args...]
./tp3 [args...]
```
## Note
- Each TP is self-contained.
- Heuristic parameters are adjustable at the top of the source files.


