#ifndef WIDGET_H
#define WIDGET_H
#define GL_SILENCE_DEPRECATION
#include <QOpenGLWidget>
#include <QWidget>

#include "../Controller/Controller_GL.h"

class Widget : public QOpenGLWidget {
  Q_OBJECT

 public:
  Widget(QWidget *parent = nullptr);
  void initializeGL() override;
  void paintGL() override;
  bool read_file(std::string file);
  void rgb(double r_, double g_, double b_, int type);
  void types_width(int p, bool l, bool pr, double p_size, double l_width);
  void change_state_obj(double s, double r_x, double r_y, double r_z,
                        double m_x, double m_y, double m_z);
  unsigned int count_vtx();
  unsigned int count_pol();
  void reset_vtx();
  ~Widget();

 private:
  s21::Controller_GL controller;
  void draw_points();
  void draw_lines();
  void projection();
  int point_flag = 1;
  float r = 0, g = 0, b = 0;
  float r_line = 1, g_line = 0, b_line = 0;
  float r_point = 0, g_point = 1, b_point = 0;
  float line_width = 1, point_size = 1;
  bool flag = 1, line_flag = 0, projection_flag = 0;
};
#endif  // WIDGET_H
