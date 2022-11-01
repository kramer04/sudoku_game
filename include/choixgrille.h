#ifndef CHOIXGRILLE_H
#define CHOIXGRILLE_H

#include <filesystem>
#include <iterator>
#include <vector>

using Stringvec = std::vector<std::string>;
struct path_leaf_string
{
  std::string operator()(const std::filesystem::directory_entry &entry) const
  {
    //return entry.path().filename();
    return entry.path().string();
  }
};

class Choix
{
  public:
  Choix();
  Stringvec sv(std::string &grille);

  private:
  void read_directory(const std::string &name, Stringvec &v);
};

#endif