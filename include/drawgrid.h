#ifndef DRAWGRID_H
#define DRAWGRID_H

#include <gtkmm/drawingarea.h>
#include <cairomm-1.16/cairomm/context.h>

class DrawGrid : public Gtk::DrawingArea
{
  public:
  DrawGrid();
  virtual ~DrawGrid();

  protected:
  void on_draw(const Cairo::RefPtr<Cairo::Context> &cr, int width, int height);
};

#endif