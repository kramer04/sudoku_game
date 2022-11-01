#ifndef SAVE_H
#define SAVE_H

#include "streamgrid.h"

struct Restore
{
  uint erreur;
  Glib::ustring heure;
  Grid sudoku, control;
  std::chrono::system_clock::rep start;
};

class Save : public Stream
{
  public:
  Save(std::string const &pathfile);
  Save(std::string const &pathfile, Grid const &sudoku, Grid const &control, Glib::ustring const &heure, uint &erreur, std::chrono::_V2::system_clock::duration &start);
  void writefile();
  //Grid restore(bool control);
  Restore restore();

  private:
  std::string const m_pathfile;
  Grid m_sudoku, m_control;
  Glib::ustring m_heure;
  uint m_erreur;
  std::ofstream m_savefile;
  std::ifstream m_restorefile;
  //std::chrono::system_clock::time_point m_start;
  std::chrono::nanoseconds m_start;
};
#endif