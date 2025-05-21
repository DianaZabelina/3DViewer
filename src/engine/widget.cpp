#include "widget.h"
using namespace s21;
Widget::Widget(QWidget* parent) : QOpenGLWidget(parent) {}
void Widget::initializeGL() { glEnable(GL_DEPTH_TEST); }

void Widget::paintGL() {
  projection();
  glPointSize(point_size);
  glLineWidth(line_width);
  glClearColor(r, g, b, 0);
  glLineStipple(3, 666);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  if (!flag) {
    draw_points();
    draw_lines();
  }
}

void Widget::draw_points() {
  if (point_flag) {
    if (point_flag == 2) glEnable(GL_POINT_SMOOTH);
    glColor3d(r_point, g_point, b_point);
    for (unsigned int i = 0; i < controller.count_vtx(); i++) {
      glBegin(GL_POINTS);
      glVertex3f(controller.x_vtx(i), controller.y_vtx(i), controller.z_vtx(i));
      glEnd();
    }
    if (point_flag == 2) glDisable(GL_POINT_SMOOTH);
  }
}

void Widget::draw_lines() {
  if (line_flag) glEnable(GL_LINE_STIPPLE);
  glColor3d(r_line, g_line, b_line);
  for (unsigned int i = 0; i < controller.count_polygon(); i++) {
    if (i == 0 || controller.polygon(i - 1) == 0) glBegin(GL_LINE_LOOP);
    if (controller.polygon(i) != 0)
      glVertex3f(controller.x_vtx(controller.polygon(i) - 1),
                 controller.y_vtx(controller.polygon(i) - 1),
                 controller.z_vtx(controller.polygon(i) - 1));
    else
      glEnd();
  }

  if (line_flag) glDisable(GL_LINE_STIPPLE);
}

void Widget::projection() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (projection_flag) {
    float fov = controller.width() / (2 * tan((60 * M_PI / 180) / 2));
    glFrustum(-controller.width(), controller.width(), -controller.width(),
              controller.width(), fov, 100000);
    glTranslated(0, 0, -controller.width() * 3);
  } else
    glOrtho(-controller.width(), controller.width(), -controller.width(),
            controller.width(), -controller.width(), controller.width());
}

bool Widget::read_file(std::string file) {
  flag = controller.read_file(file);
  return flag;
}

void Widget::rgb(double r_, double g_, double b_, int type) {
  if (!type) {
    r = r_;
    g = g_;
    b = b_;
  } else if (type == 1) {
    r_line = r_;
    g_line = g_;
    b_line = b_;
  } else if (type == 2) {
    r_point = r_;
    g_point = g_;
    b_point = b_;
  }
  update();
}

void Widget::types_width(int p, bool l, bool pr, double p_size,
                         double l_width) {
  line_flag = l;
  point_flag = p;
  projection_flag = pr;
  point_size = p_size;
  line_width = l_width;

  update();
}
void Widget::change_state_obj(double s, double r_x, double r_y, double r_z,
                              double m_x, double m_y, double m_z) {
  controller.change_state_obj(s, r_x, r_y, r_z, m_x, m_y, m_z);
  update();
}

unsigned int Widget::count_vtx() { return controller.count_vtx(); }

unsigned int Widget::count_pol() {
  unsigned int count = 0;
  for (size_t i = 0; i < controller.count_polygon(); i++) {
    if (controller.polygon(i) != 0) count++;
  }
  return count;
}
void Widget::reset_vtx() { controller.reset_vtx(); }

Widget::~Widget() {}
