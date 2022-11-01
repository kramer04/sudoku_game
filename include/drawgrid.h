#ifndef DRAWGRID_H
#define DRAWGRID_H

#include <gtkmm-4.0/gtkmm/drawingarea.h>

class DrawGrid: public Gtk::DrawingArea
{
  public:
  DrawGrid();
  virtual ~DrawGrid();

  protected:
  void on_draw(const Cairo::RefPtr<Cairo::Context> &cr, int width, int height);
};

#endif