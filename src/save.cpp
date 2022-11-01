#include "save.h"

Save::Save(std::string const &pathfile, Grid const &sudoku, Grid const &control, Glib::ustring const &heure, uint &erreur, std::chrono::_V2::system_clock::duration &start):
  m_pathfile(pathfile),
  m_sudoku(sudoku), m_control(control),
  m_heure(heure),
  m_erreur(erreur),
  m_savefile(m_pathfile.c_str(), std::ios::out | std::ios::binary),
  m_start(start)
{}
void Save::writefile()
{
  //m_savefile.seekp(0, std::ios::beg);
  for (int i {0}; i < L; ++i)
    for (int j {0}; j < C; ++j)
      m_savefile << m_sudoku [i][j];
  m_savefile << '\n';
  for (int i {0}; i < L; ++i)
    for (int j {0}; j < C; ++j)
      m_savefile << m_control [i][j];
  m_savefile << '\n';
  m_savefile << m_heure << '\n';
  m_savefile << m_erreur << '\n';

  using namespace std::chrono_literals;
  auto const cache_time = m_start.count();
  m_savefile.write(reinterpret_cast<char const *>(&cache_time), sizeof cache_time);
  //m_savefile << reinterpret_cast<char const *>(&cache_time);
  m_savefile.close();
}

Save::Save(std::string const &pathfile):m_pathfile(pathfile), m_restorefile(m_pathfile.c_str(), std::ios::in | std::ios::binary)
{}
Restore Save::restore()
{
  Restore r;
  if (!m_restorefile.is_open())
    m_restorefile.open(m_pathfile, std::ios::in | std::ios::binary);

  std::string line {};
  getline(m_restorefile, line);
  for (int i {0}; i < G; i++)
    for (int j {0}; j < G; j++)
      r.sudoku [i][j] = (int) (line [(i * G) + j]) - '0';
  getline(m_restorefile, line);
  for (int i {0}; i < G; i++)
    for (int j {0}; j < G; j++)
      r.control [i][j] = (int) (line [(i * G) + j]) - '0';
  
  getline(m_restorefile, line);
  r.heure = line;
  getline(m_restorefile, line);
  r.erreur = std::stoi(line);

  //m_restorefile.seekg(164, std::ios::beg);
  using namespace std::chrono_literals;
  m_restorefile.read(reinterpret_cast<char *>(&r.start), sizeof r.start);  
  m_restorefile.close();
  
  return r;
}
/* Grid Save::restore(bool control)
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
} */
