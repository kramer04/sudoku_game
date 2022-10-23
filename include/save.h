#ifndef SAVE_H
#define SAVE_H

#include "streamgrid.h"

class Save : public Stream
{
  public:
  Save(std::string const &pathfile);
  Save(std::string const &pathfile, Grid const &sudoku, Grid const &control);
  void writefile();
  Grid restore(bool control);

  private:
  std::string const m_pathfile;
  Grid m_sudoku, m_control;
  std::ofstream m_savefile;
  std::ifstream m_restorefile;
};
#endif