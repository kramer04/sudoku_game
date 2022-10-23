#ifndef SOLVER_H
#define SOLVER_H

#include <array>
#include <chrono>
#include <iostream>

constexpr int n = 3;
constexpr int N = n * n;

using Grille = std::array<std::array<int, N>, N>;

class Solver
{
public:
  Solver();
  void solver(Grille &grille) noexcept;
private:
  //Liste des fonctions
  bool rien_carre_nxn(Grille &grille, int k, int i, int j) noexcept;
  bool rien_ligne_colonne(Grille &grille, int k, int i, int c) noexcept;
  void singleton(Grille &grille) noexcept;
  bool backtrack(Grille &grille, int pos) noexcept;
  void afficher(Grille &grille) noexcept;

  int m_boucle, m_total;

};


#endif