#ifndef STREAMGRID_H
#define STREAMGRID_H  

#include <iostream>
#include <array>
#include <chrono>
#include <fstream>
#include <limits>
#include <random>
#include <glibmm-2.68/glibmm/ustring.h>

constexpr int L{9};
constexpr int C{9};
constexpr int G{9};

using Grid = std::array<std::array<int, C>, L>;

class Stream
{
  public:
  Stream() = default;
  Stream(Glib::ustring fichier);
  Grid RandomGrid();

  protected:
  void afficher(Grid const &grid) noexcept;
  std::ifstream &GotoLine(std::ifstream &file, unsigned const int num);
  uint TotalLigne(std::ifstream &input);

  std::string m_fichier;
  std::ifstream m_input;
};

#endif