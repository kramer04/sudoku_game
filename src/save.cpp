#include "save.h"

Save::Save(std::string const &pathfile, Grid const &sudoku, Grid const &control): m_pathfile(pathfile),
m_sudoku(sudoku), m_control(control),
m_savefile(m_pathfile.c_str(), std::ios::out)
{}
void Save::writefile()
{
  //m_savefile.seekp(0, std::ios::beg);
  for (int i {0}; i < L; ++i)
    for (int j {0}; j < C; ++j)
      m_savefile << m_sudoku [i][j];
  m_savefile << std::endl;
  for (int i {0}; i < L; ++i)
    for (int j {0}; j < C; ++j)
      m_savefile << m_control [i][j];
  m_savefile.close();
}

Save::Save(std::string const &pathfile):m_pathfile(pathfile), m_restorefile(m_pathfile.c_str(), std::ios::in)
{}
Grid Save::restore(bool control)
{
  if (!m_restorefile.is_open())
  {
    m_restorefile.open(m_pathfile, std::ios::in);
    if (control)
      m_restorefile.seekg(82, std::ios::beg);    
  }
  
  std::string line {};
  getline(m_restorefile, line);
  for (int i {0}; i < G; i++)
    for (int j {0}; j < G; j++)
      m_sudoku [i][j] = (int) (line [(i * G) + j]) - '0';

  m_restorefile.close();
  
  afficher(m_sudoku);
  return m_sudoku;
}
