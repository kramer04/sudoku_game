#include "choixgrille.h"

Choix::Choix() {}

Stringvec Choix::sv(std::string &grille)
{
  Stringvec v;
  read_directory(grille, v);

  return v;
}
void Choix::read_directory(const std::string &name, Stringvec &v)
{
  std::filesystem::path p(name);
  std::filesystem::directory_iterator start(p);
  std::filesystem::directory_iterator end;
  std::transform(start, end, std::back_inserter(v), path_leaf_string());
}