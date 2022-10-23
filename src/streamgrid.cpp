#include "streamgrid.h"

Stream::Stream(Glib::ustring fichier): m_fichier(fichier), m_input(m_fichier, std::ios::in)
{}

void Stream::afficher(Grid const &grid) noexcept
{
  std::cout << "+-----+-----+-----+\n";
  for (int x = 0; x < G; x++)
  {
    std::cout << "|";
    for (int y = 0; y < G; y++)
    {
      std::cout << grid [x][y];
      ((y + 1) % (G / 3)) ? std::cout << " " : std::cout << "|";
    }
    std::cout << '\n';
    if (!((x + 1) % (G / 3)))
    {
      std::cout << "+-----+-----+-----+\n";
    }
  }
  std::cout << std::endl;
}
std::ifstream &Stream::GotoLine(std::ifstream &file, unsigned const int num)
{
  file.close();
  file.open(m_fichier);
  file.seekg(std::ios::beg);
  for (uint i {0}; i < num - 1; ++i)
  {
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  return file;
}
uint Stream::TotalLigne(std::ifstream &m_input)
{
  auto max_size = std::numeric_limits <std::streamsize>::max();
  uint count {1};
  std::string line {};
  m_input.clear();
  m_input.seekg(0, std::ios::beg);
  //nombre de lignes
  if (m_input.fail())
  {
    std::cerr << "Erreur ouverture du fichier " << m_fichier << std::endl;
    m_input.close();
    exit(1);
  }
  for (;;)
  {
    getline(m_input, line);
    if (m_input.eof() || m_input.bad())
      break;
    else if (m_input.fail())
    {
      m_input.clear(); // unset failbit
      m_input.ignore(max_size, '\n'); // skip bad m_input
    }
    else
      count++;
  }

  std::cout << "nombre de lignes -> " << count << std::endl;
  return count;
}
Grid Stream::RandomGrid()
{
  uint total = TotalLigne(m_input);
  std::string line {};
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type>dist(1, total);
  uint_fast32_t ligne = dist(rng);
  std::cout << "Numéro de la ligne -> " << ligne << std::endl;

  GotoLine(m_input, ligne);
  m_input >> line;
  std::cout << "Grille tirée au hasard ->\n" << line << std::endl;

  Grid grid;
  for (int i {0}; i < G; i++)
    for (int j {0}; j < G; j++)
      grid [i][j] = (int) (line [(i * G) + j]) - '0'; //Une case (i,j) dans un tableau peut être représentée par un nombre (i*LARGEUR_TABLEAU) + j

  afficher(grid);

  return grid;
}