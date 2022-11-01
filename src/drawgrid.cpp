#include "drawgrid.h"
#include <cairomm-1.16/cairomm/context.h>

DrawGrid::DrawGrid()
{
  set_content_width(500);
  set_content_height(400);
  set_draw_func(sigc::mem_fun(*this, &DrawGrid::on_draw));
}
DrawGrid::~DrawGrid()
{}

void DrawGrid::on_draw(const Cairo::RefPtr<Cairo::Context> &cr, int width, int height)
{
  // coordonnées (0,0) soit en haut à gauche
  int xc, yc;
  xc = width;
  yc = height;

  cr->set_line_width(2.0);

  // tracé en coordonnées absolues
  cr->set_source_rgb(0.812, 0.157, 0.157);
  cr->move_to(0, 1);
  cr->line_to(xc, 1);
  cr->move_to(0, 132);
  cr->line_to(xc, 132);
  cr->move_to(0, 264);
  cr->line_to(xc, 264);
  cr->move_to(0, 399);
  cr->line_to(xc, 399);
  cr->move_to(1, 0);
  cr->line_to(1, yc);
  cr->move_to(168, 0);
  cr->line_to(168, yc);
  cr->move_to(335, 0);
  cr->line_to(335, yc);
  cr->move_to(499, 0);
  cr->line_to(499, yc);
  cr->stroke();

  //tracé avec coordonnées relatives
  /*   cr->move_to(0, 0);
    cr->rel_move_to(0, 132);
    cr->rel_line_to(xc, 0);
    cr->rel_move_to(0, 132);
    cr->rel_line_to(-xc, 0);
    cr->rel_move_to(168, -264);
    cr->rel_line_to(0, yc);
    cr->rel_move_to(168, 0);
    cr->rel_line_to(0, -yc);
    cr->stroke(); */
}