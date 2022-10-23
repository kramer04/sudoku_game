#include "entree.h"
constexpr auto num1to9 = "1 2 3 4 5 6 7 8 9";
Focus::Focus()
{}

bool Focus::si_focus(Gtk::Widget &widget)
{
  const Gtk::Root *root = widget.get_root();
  if (!root)
    return false;

  const Gtk::Widget *focused = root->get_focus();
  if (!focused)
    return false;

  return focused->is_ancestor(widget);
}

WidgetIsFocus::WidgetIsFocus()
{}
bool WidgetIsFocus::dansEntry(int const i, int const j)
{
  return ((i >= 0) && (i < L) && (j >= 0) && (j < C));
}
Ij WidgetIsFocus::wif(std::array<std::array<Gtk::Entry, C>, L> &widget)
{
  Ij ij {-1,-1};
  for (int i {0}; i < L; i++)
  {
    for (int j {0}; j < C; j++)
    {
      if (si_focus(widget [i][j]))
      {
        ij.i = i;
        ij.j = j;
      }
    }
  }
  return ij;
}

Sudoku::Sudoku():
  m_quit("Quit"), m_ok("Jouer"), m_save("Save"), m_restore("Restore"), m_solver("Solver"),
  m_mouse(Gtk::GestureClick::create()),
  m_actuel(), m_precedent(),
  m_num1to9str(),
  m_erreur(0), m_juste(0),
  m_sdkgrid("grilles")
{
  set_title("Sudoku 9x9");
  set_default_size(500, 250);
  set_resizable(false);
  set_child(m_box);

  m_hboxld.set_orientation(Gtk::Orientation::HORIZONTAL);
  m_hboxld.set_margin(5);
  m_hboxld.append(m_vboxlisted);
  m_hboxld.append(m_separator);
  m_hboxld.append(m_vboxinfo);

  m_vboxlisted.set_orientation(Gtk::Orientation::VERTICAL);
  m_vboxlisted.set_margin(5);
  m_vboxlisted.append(m_listeD);
  m_vboxlisted.append(m_num1to9frame);

  m_num1to9frame.set_margin(5);
  m_num1to9frame.set_child(m_num1to9);

  m_choixgrille = listgrid.sv(m_sdkgrid);
  m_listeD.append(("Choisir une grille"));
  for (auto l : m_choixgrille)
    m_listeD.append(l);
  m_listeD.set_active(0);
  m_listeD.set_margin(5);
  m_listeD.set_hexpand();
  m_listeD.set_halign(Gtk::Align::START);

  m_num1to9.set_margin(5);
  m_num1to9.set_halign(Gtk::Align::START);
  m_num1to9.set_text(num1to9);
  auto num1to9 = Gtk::CssProvider::create();
  num1to9->load_from_path("css/num1to9.css");
  auto ctx_num1to9 = m_num1to9.get_style_context();
  ctx_num1to9->add_class("num1to9");
  ctx_num1to9->add_provider(num1to9, GTK_STYLE_PROVIDER_PRIORITY_SETTINGS);

  m_separator.set_margin(10);
  m_separator.set_orientation(Gtk::Orientation::VERTICAL);

  m_infoframe.set_margin(5);
  m_infoframe.set_label("Info");
  m_infoframe.set_child(m_information);

  m_timeframe.set_margin(5);
  m_timeframe.set_label("Time");
  m_timeframe.set_child(m_dureejeu);

  m_dureejeu.set_margin(5);
  m_dureejeu.set_hexpand();
  m_dureejeu.set_halign(Gtk::Align::START);
  m_dureejeu.set_text("00:00:00");

  m_information.set_margin(5);
  m_information.set_hexpand();
  m_information.set_halign(Gtk::Align::START);

  m_vboxinfo.set_orientation(Gtk::Orientation::VERTICAL);
  m_vboxinfo.set_margin(5);
  m_vboxinfo.append(m_infoframe);
  m_vboxinfo.append(m_timeframe);

  m_ok.set_margin(5);
  auto button = Gtk::CssProvider::create();
  button->load_from_path("css/button.css");
  auto ctx_button = m_ok.get_style_context();
  ctx_button->add_class("button");
  ctx_button->add_provider(button, GTK_STYLE_PROVIDER_PRIORITY_SETTINGS);

  m_quit.set_hexpand();
  m_quit.set_halign(Gtk::Align::END);
  m_quit.set_margin(5);
  m_quit.set_name("button");
  button = Gtk::CssProvider::create();
  button->load_from_path("css/button.css");
  auto ctx_quit = m_quit.get_style_context();
  ctx_quit->add_class("button");
  ctx_quit->add_provider(button, GTK_STYLE_PROVIDER_PRIORITY_USER);

  m_save.set_margin(5);
  button = Gtk::CssProvider::create();
  button->load_from_path("css/button.css");
  auto ctx_save = m_save.get_style_context();
  ctx_save->add_provider(button, GTK_STYLE_PROVIDER_PRIORITY_USER);
  ctx_save->add_class("button");

  m_restore.set_margin(5);
  button = Gtk::CssProvider::create();
  button->load_from_path("css/button.css");
  auto ctx_restore = m_restore.get_style_context();
  ctx_restore->add_provider(button, GTK_STYLE_PROVIDER_PRIORITY_USER);
  ctx_restore->add_class("button");

  m_solver.set_margin(5);
  button = Gtk::CssProvider::create();
  button->load_from_path("css/button.css");
  auto ctx_solver = m_solver.get_style_context();
  ctx_solver->add_provider(button, GTK_STYLE_PROVIDER_PRIORITY_USER);
  ctx_solver->add_class("button");

  m_label.set_expand();
  m_label.set_halign(Gtk::Align::END);
  m_label.set_label(std::to_string(m_erreur));

  m_overlay.set_size_request(500, 400);
  m_overlay.queue_draw();
  m_overlay.add_overlay(lines);
  m_overlay.add_overlay(m_grid);

  m_hbox.set_orientation(Gtk::Orientation::HORIZONTAL);
  m_hbox.set_margin(5);
  m_hbox.append(m_ok);
  m_hbox.append(m_save);
  m_hbox.append(m_restore);
  m_hbox.append(m_solver);
  m_hbox.append(m_label);
  m_hbox.append(m_quit);

  m_box.set_orientation(Gtk::Orientation::VERTICAL);
  m_box.set_margin(5);
  m_box.append(m_hboxld);
  m_box.append(m_overlay);
  m_box.append(m_hbox);

  //entry  
  for (int i {0}; i < L; i++)
  {
    for (int j {0}; j < C; j++)
    {
      m_entry [i][j].set_text("");
      m_entry [i][j].set_alignment(Gtk::Align::CENTER);//aligne le texte
      m_entry [i][j].set_max_length(1);
      m_entry [i][j].set_margin(5);
      m_grid.attach(m_entry [i][j], j, i, 1, 1);
    }
  }

  m_mouse->set_propagation_phase(Gtk::PropagationPhase::CAPTURE);
  m_mouse->set_button(GDK_BUTTON_PRIMARY);
  add_controller(m_mouse);
  m_mouse->signal_released().connect(sigc::mem_fun(*this, &Sudoku::on_mouse_key_pressed), false);

  bool after {false};
  auto controller = Gtk::EventControllerKey::create();
  controller->set_propagation_phase(Gtk::PropagationPhase::CAPTURE);
  add_controller(controller);
  controller->signal_key_released().connect(sigc::bind(sigc::mem_fun(*this, &Sudoku::on_key_released), "capture"), after);

  m_ok.signal_clicked().connect([this]() {lance_jeu(); });
  m_quit.signal_clicked().connect([this]() {quit(); });
  m_save.signal_clicked().connect([this]() {save(m_sudoku, m_gridcontrol); });
  m_restore.signal_clicked().connect([this]() {restore(); });
}
//FONCTIONS
void Sudoku::clearcase(int i, int j)
{
  m_entry [i][j].set_editable();
  auto fournisseur = Gtk::CssProvider::create();
  fournisseur->load_from_path("css/entree.css");//fonds bleu
  auto ctx_entry = m_entry [i][j].get_style_context();
  ctx_entry->add_class("entree");
  ctx_entry->add_provider(fournisseur, GTK_STYLE_PROVIDER_PRIORITY_USER);
}
void Sudoku::lance_jeu()
{
  m_information.set_text("");
  Stream grille {m_listeD.get_active_text()};
  m_gridcontrol = grille.RandomGrid();
  m_sudoku = m_gridcontrol;
  solution.solver(m_gridcontrol);
  m_numcount.fill(0);
  m_num1to9.set_text(num1to9);
  m_num1to9str = num1to9;
  m_juste = 0;
  m_erreur = 0;
  m_label.set_label(std::to_string(m_erreur));
  m_dureejeu.set_text("00:00:00");
  for (int i {0}; i < L; i++)
  {
    for (int j {0}; j < C; j++)
    {
      m_sudoku [i][j] == 0 ? m_entry [i][j].set_text("") : m_entry [i][j].set_text(std::to_string(m_sudoku [i][j]));
      if (m_entry [i][j].get_text() != "")
      {
        test_numcount(m_sudoku [i][j] - 1);
        m_entry [i][j].set_editable(false);
        auto fournisseur = Gtk::CssProvider::create();
        fournisseur->load_from_path("css/entry.css");//fonds vert
        auto ctx_entry = m_entry [i][j].get_style_context();
        ctx_entry->add_class("entry");
        ctx_entry->add_provider(fournisseur, GTK_STYLE_PROVIDER_PRIORITY_USER);
      }
      else
        clearcase(i, j);
    }
  }
  m_start = std::chrono::steady_clock::now();
}
void Sudoku::on_mouse_key_pressed(int, double, double)
{
  ij = wif(m_entry);
  if (ij.i > -1 && ij.j > -1 && !m_entry [ij.i][ij.j].get_editable())
  {
    surligne(m_precedent, m_entry [ij.i][ij.j].get_text());
    m_precedent = m_entry [ij.i][ij.j].get_text();
  }
  if (ij.i > -1 && ij.j > -1 && m_entry [ij.i][ij.j].get_editable())
  {
    surligne(m_precedent);
  }
}
void Sudoku::on_key_released(guint keyval, guint, Gdk::ModifierType, const Glib::ustring &phase)
{
  ij = wif(m_entry);

  const gunichar unichar = gdk_keyval_to_unicode(keyval);
  if (unichar >= '0' && unichar <= '9' && m_entry [ij.i][ij.j].get_editable())
  {
    m_actuel = std::to_string(unichar - '0');
    m_entry [ij.i][ij.j].set_text(m_actuel);
    //surligne(m_precedent, m_actuel);
    if (m_gridcontrol [ij.i][ij.j] == (int) (unichar - '0'))
    {
      test_numcount(m_gridcontrol [ij.i][ij.j] - 1);
      m_sudoku [ij.i][ij.j] = (unichar - '0');
      m_entry [ij.i][ij.j].set_editable(false);
      auto fournisseur = Gtk::CssProvider::create();
      fournisseur->load_from_data(".green{background-color:#c0eca7;color:#080808;}");
      auto ctx_entry = m_entry [ij.i][ij.j].get_style_context();
      ctx_entry->add_class("green");
      ctx_entry->add_provider(fournisseur, GTK_STYLE_PROVIDER_PRIORITY_USER);
      m_precedent = m_actuel;
      surligne("", m_actuel);
      m_juste++;
      //if (m_juste == 81)
      //{
      m_end = std::chrono::steady_clock::now();
      std::chrono::steady_clock::duration duree = m_end - m_start;
      auto dp = std::chrono::floor<std::chrono::days>(duree);
      std::chrono::hh_mm_ss time {std::chrono::floor<std::chrono::seconds>(duree - dp)};
      auto h = time.hours();
      auto m = time.minutes();
      auto s = time.seconds();
      Glib::ustring heure {};
      (h.count() < 10) ? heure = "0" + std::to_string(h.count()) : heure = std::to_string(h.count());
      (m.count() < 10) ? heure += ":0" + std::to_string(m.count()) : heure += ":" + std::to_string(m.count());
      (s.count() < 10) ? heure += ":0" + std::to_string(s.count()) : heure += ":" + std::to_string(s.count());
      m_dureejeu.set_text(heure);
      //}
    }
    else
    {
      auto fournisseur = Gtk::CssProvider::create();
      fournisseur->load_from_data(".red{color:red;background-color:#e0e0e0;}");
      auto ctx_red = m_entry [ij.i][ij.j].get_style_context();
      ctx_red->add_class("red");
      ctx_red->add_provider(fournisseur, GTK_STYLE_PROVIDER_PRIORITY_USER);
      m_precedent = m_entry [ij.i][ij.j].get_text();
      //m_entry [ij.i][ij.j].set_text("");
      m_erreur++;
      m_label.set_label(std::to_string(m_erreur));
    }
  }
  if (keyval == GDK_KEY_Delete)
  {
    clearcase(ij.i, ij.j);
  }
  if (keyval == GDK_KEY_Down && dansEntry(ij.i, ij.j) && phase == "capture")
  {
    if (ij.i >= 0)
    {
      surligne(m_precedent, m_entry [ij.i][ij.j].get_text());
      m_precedent = m_entry [ij.i][ij.j].get_text();
    }
  }
  else if (keyval == GDK_KEY_Down && phase == "capture")
  {
    surligne(m_precedent);
  }
  if (keyval == GDK_KEY_Up && dansEntry(ij.i, ij.j) && phase == "capture")
  {
    if (ij.i < L)
    {
      surligne(m_precedent, m_entry [ij.i][ij.j].get_text());
      m_precedent = m_entry [ij.i][ij.j].get_text();
    }
  }
  if (keyval == GDK_KEY_Right && ij.j < (C - 1) && dansEntry(ij.i, ij.j) && phase == "capture")
  {
    m_entry [ij.i][ij.j + 1].grab_focus();
    surligne(m_precedent, m_entry [ij.i][ij.j + 1].get_text());
    m_precedent = m_entry [ij.i][ij.j + 1].get_text();
  }
  else if (keyval == GDK_KEY_Left && ij.j > 0 && phase == "capture")
  {
    m_entry [ij.i][ij.j - 1].grab_focus();
    surligne(m_precedent, m_entry [ij.i][ij.j - 1].get_text());
    m_precedent = m_entry [ij.i][ij.j - 1].get_text();
  }
}

void Sudoku::surligne(Glib::ustring const precedent, Glib::ustring const actuel)
{
  for (int i {0}; i < L; i++)
  {
    for (int j {0}; j < C; j++)
    {
      if (m_entry [i][j].get_editable() && m_entry [i][j].get_text() != "")
      {
        auto erreur = Gtk::CssProvider::create();
        erreur->load_from_data(".error{background-color:#a7d3ec;}");
        auto blue = m_entry [i][j].get_style_context();
        blue->add_class("error");
        blue->add_provider(erreur, GTK_STYLE_PROVIDER_PRIORITY_USER);
      }
      
      if (m_entry [i][j].get_text() == precedent && !m_entry [i][j].get_editable())
      {
        auto provider = Gtk::CssProvider::create();
        provider->load_from_data(".green{background-color:#c0eca7;}.green:hover{background-color:#66cdaa;}");
        auto green = m_entry [i][j].get_style_context();
        green->add_class("green");
        green->add_provider(provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
      }

      if (m_entry [i][j].get_text() == actuel && m_entry [i][j].get_text() != "")
      {
        auto fournisseur = Gtk::CssProvider::create();
        fournisseur->load_from_data(".yellow{background-color:yellow;}");
        auto ctx_yellow = m_entry [i][j].get_style_context();
        ctx_yellow->add_class("yellow");
        ctx_yellow->add_provider(fournisseur, GTK_STYLE_PROVIDER_PRIORITY_USER);
      }
    }
  }
}
void Sudoku::save(Grid &filesudoku, Grid &filecontrol)
{
  Save sudoku {"save/save.txt", filesudoku, filecontrol};
  sudoku.writefile();
  m_information.set_text("Fichier sauvegardé");
}
void Sudoku::restore()
{
  Save sudoku {"save/save.txt"};
  m_sudoku = sudoku.restore(false);
  m_num1to9str = num1to9;
  m_num1to9.set_text(num1to9);
  m_numcount.fill(0);
  m_juste = 0;
  m_erreur = 0;
  m_label.set_label(std::to_string(m_erreur));
  m_dureejeu.set_text("00:00:00");
  for (int i {0}; i < L; i++)
  {
    for (int j {0}; j < C; j++)
    {
      m_sudoku [i][j] == 0 ? m_entry [i][j].set_text("") : m_entry [i][j].set_text(std::to_string(m_sudoku [i][j]));
      if (m_entry [i][j].get_text() != "")
      {
        test_numcount(m_sudoku [i][j] - 1);
        m_entry [i][j].set_editable(false);
        auto fournisseur = Gtk::CssProvider::create();
        fournisseur->load_from_path("css/entry.css");//fonds vert
        auto ctx_entry = m_entry [i][j].get_style_context();
        ctx_entry->add_class("entry");
        ctx_entry->add_provider(fournisseur, GTK_STYLE_PROVIDER_PRIORITY_USER);
      }
      else
        clearcase(i, j);
    }
  }
  m_gridcontrol = sudoku.restore(true);
  m_information.set_text("Fichier restauré");
  m_start = std::chrono::steady_clock::now();
}
void Sudoku::quit()
{
  hide();
}
//compte les nombres et les retire de la liste si 9 est atteint
void Sudoku::test_numcount(int j)
{
  m_numcount [j] += 1;
  //std::cout << "m_numcount [" << j << "]" << m_numcount [j] << std::endl;
  if (m_numcount [j] == 9)
  {
    m_num1to9str [2 * j] = ' ';
    m_num1to9.set_text(m_num1to9str);
  }
}