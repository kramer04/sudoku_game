#include "solver.h"

//int boucle{0}, total{0};

Solver::Solver() : m_boucle(0), m_total(0)
{}
void Solver::afficher(Grille &grille) noexcept
{
  std::cout << "+-----+-----+-----+\n";
  for (int x = 0; x < N; x++)
  {
    std::cout << "|";
    for (int y = 0; y < N; y++)
    {
      std::cout << grille [x][y];
      ((y + 1) % n) ? std::cout << " " : std::cout << "|";
    }
    std::cout << '\n';
    if (!((x + 1) % n))
    {
      std::cout << "+-----+-----+-----+\n";
    }
  }
  std::cout << std::endl;
}

bool Solver::backtrack(Grille &grille, int pos) noexcept
{
  if (pos == N * N)
  {
    return true;
  }
  int i = pos / N, j = pos % N;

  if (grille [i][j] != 0)
  {
    return backtrack(grille, pos + 1);
  }

  for (int k{1}; k <= N; k++)
  {
    if (rien_ligne_colonne(grille, k, i, j) && rien_carre_nxn(grille, k, i, j))
    {
      grille [i][j] = k;
      if (backtrack(grille, pos + 1))
      {
        return true;
      }
    }
  }
  grille [i][j] = 0;
  return false;
}
// bloc, retourne FAUX si la valeur est trouvée, sinon VRAI
bool Solver::rien_carre_nxn(Grille &grille, int k, int l, int c) noexcept
{
  int ii = l - (l % n), jj = c - (c % n);
  for (l = ii; l < ii + n; l++)
  {
    for (c = jj; c < jj + n; c++)
    {
      if (grille [l][c] == k)
      {
        return false;
      }
    }
  }
  return true;
}
//ligne colonne retourne FAUX si la valeur est trouvée, sinon VRAI
bool Solver::rien_ligne_colonne(Grille &grille, int k, int l, int c) noexcept
{
  for (int i{0}; i < N; i++)
  {
    if (grille [l][i] == k || grille [i][c] == k)
    {
      return false;
    }
  }
  return true;
}
void Solver::singleton(Grille &grille) noexcept
{
  int singleton{0};
  do
  {
    singleton = 0;
    //carré
    for (int i{0}; i < N; i += n)
    {
      for (int j{0}; j < N; j += n)
      {
        int posI{0}, posJ{0};
        for (int k{1}; k <= N; k++)
        {
          int count = 0;
          for (int ii{i}; ii < i + n; ii++)
          {
            for (int jj{j}; jj < j + n; jj++)
            {
              if (grille [ii][jj] == 0 && rien_ligne_colonne(grille, k, ii, jj) && rien_carre_nxn(grille, k, ii, jj))
              {
                posI = ii;
                posJ = jj;
                count++;
              }
            }
          }
          if (count == 1)
          {
            grille [posI][posJ] = k;
            singleton++;
          }
        }
      }
    }
    //lignes
    for (int i{0}; i < N; i++)
    {
      int posI{0}, posJ{0};
      for (int k{1}; k <= N; k++)
      {
        int count{0};
        for (int j{0}; j < N; j++)
        {
          if (grille [i][j] == 0 && rien_ligne_colonne(grille, k, i, j) && rien_carre_nxn(grille, k, i, j))
          {
            posI = i;
            posJ = j;
            count++;
          }
        }
        if (count == 1)
        {
          grille [posI][posJ] = k;
          singleton++;
        }
      }
    }
    //colonnes
    for (int j{0}; j < N; j++)
    {
      int posI{0}, posJ{0};
      for (int k{1}; k <= N; k++)
      {
        int count{0};
        for (int i{0}; i < N; i++)
        {
          if (grille [i][j] == 0 && rien_ligne_colonne(grille, k, i, j) && rien_carre_nxn(grille, k, i, j))
          {
            posI = i;
            posJ = j;
            count++;
          }
        }
        if (count == 1)
        {
          grille [posI][posJ] = k;
          singleton++;
        }
      }
    }
    m_total += singleton;
    m_boucle++;
  } while (singleton);
}
void Solver::solver(Grille &grille) noexcept
{
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();
  singleton(grille);

  if (backtrack(grille, 0))
  {
    end = std::chrono::system_clock::now();
    std::cout << "Total singletons trouvés -> " << m_total << "\n";
    std::cout << "Total boucle singleton -> " << m_boucle - 1 << "\n";
    m_boucle = 0;
    m_total = 0;
    std::cout << std::endl;
    std::cout << "Solution\n";
    afficher(grille);
    std::chrono::duration<double> duree = end - start;
    std::cout.precision(9);
    std::cout << "Durée = " << std::fixed << duree.count() << "s" << std::endl;;
  }
  else
  {
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> duree = end - start;
    std::cout.precision(9);
    std::cout << "Pas de solution" << std::endl;
    std::cout << "Durée = " << std::fixed << duree.count() << "s\n";
  }
}