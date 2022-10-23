#ifndef ENTREE_H
#define ENTREE_H

#include "choixgrille.h"
#include "streamgrid.h"
#include "solver.h"
#include "drawgrid.h"
#include "save.h"
#include <chrono>
#include <iostream>
#include <gtkmm/window.h>
#include <gtkmm/eventcontrollerkey.h>
#include <gtkmm/cssprovider.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/entry.h>
#include <gtkmm/frame.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <gtkmm/gestureclick.h>
#include <gtkmm/overlay.h>
#include <gtkmm/separator.h>

struct Ij
{
  int i, j;
};

class Focus:public Gtk::Window
{
  public:
  Focus();
  protected:
  bool si_focus(Gtk::Widget &widget);
};

class WidgetIsFocus: public Focus
{
  public:
  WidgetIsFocus();

  protected:
  bool dansEntry(int const i, int const j);
  Ij wif(std::array<std::array<Gtk::Entry, C>, L> &widget);

};
class Sudoku: public WidgetIsFocus
{
  public:
  Sudoku();

  private:
  Gtk::Box m_box, m_hbox, m_hboxld, m_vboxinfo, m_vboxlisted;
  Gtk::Grid m_grid;
  Gtk::Button m_quit, m_ok, m_save, m_restore, m_solver;
  Gtk::Label m_label, m_information, m_dureejeu, m_num1to9;
  //Gtk::Entry m_entry [L][C];
  std::array<std::array<Gtk::Entry, C>, L> m_entry;
  Gtk::Overlay m_overlay;
  Gtk::ComboBoxText m_listeD;
  Gtk::Frame m_infoframe, m_timeframe, m_num1to9frame;
  Gtk::Separator m_separator;

  void on_mouse_key_pressed(int n_press, double x, double y);
  void on_key_released(guint keyval, guint keycode, Gdk::ModifierType state, const Glib::ustring &phase);
  void surligne(Glib::ustring const precedent, Glib::ustring const actuel = "0");
  void quit();
  void clearcase(int i, int j);
  void lance_jeu();
  void save(Grid &filesudoku, Grid &filecontrol);
  void restore();
  void test_numcount(int j);

  Ij ij;

  Glib::RefPtr<Gtk::GestureClick> m_mouse;
  Glib::ustring m_actuel, m_precedent;
  std::string m_num1to9str;
  std::array<int, 9> m_numcount;
  uint m_erreur, m_juste;
  Grid m_gridcontrol;
  Grid m_sudoku;
  std::string m_sdkgrid;//path to grids
  Stringvec m_choixgrille;
  std::chrono::steady_clock::time_point m_start, m_end;

  Solver solution;
  DrawGrid lines;
  Choix listgrid;
};

#endif