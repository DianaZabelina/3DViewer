#include <math.h>

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
namespace s21 {
class Model {
 private:
  std::vector<double> vtx;  // x y z x1 y1 z1 x2 y2 z2 ...
  std::vector<double> changed_vtx;
  std::vector<unsigned int> polygons;  // 1 3 2 0
  double width_ = 0;
  void parse_vertex(std::string str);
  void parse_polygons(std::string str);
  void scale(double a);
  void rotate_x(double r);
  void rotate_y(double r);
  void rotate_z(double r);
  void move_x(double a);
  void move_y(double a);
  void move_z(double a);
  void find_width(double *x_width, double *y_width, double *z_width);
  void clear_obj();
  void calc_centers();
  double r_x_ = 0, r_y_ = 0, r_z_ = 0, m_x_ = 0, m_y_ = 0, m_z_ = 0, s_ = 1;

 public:
  Model() {}
  ~Model() {}
  bool read_file(std::string file_name);
  void change_state_obj(double s, double r_x, double r_y, double r_z,
                        double m_x, double m_y, double m_z);
  void reset_vtx();
  double x_vtx(unsigned int i);
  double y_vtx(unsigned int i);
  double z_vtx(unsigned int i);
  unsigned int polygon(unsigned int i);
  size_t count_polygon();
  size_t count_vtx();
  double width();
};
}  // namespace s21