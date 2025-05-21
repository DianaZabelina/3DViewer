#include "../Model/Model.h"
namespace s21 {
class Controller_GL {
 public:
  Controller_GL() {}
  ~Controller_GL() {}
  bool read_file(std::string file) { return model.read_file(file); }
  void change_state_obj(double s, double r_x, double r_y, double r_z,
                        double m_x, double m_y, double m_z) {
    model.change_state_obj(s, r_x, r_y, r_z, m_x, m_y, m_z);
  }
  void reset_vtx() { model.reset_vtx(); }
  double x_vtx(unsigned int i) { return model.x_vtx(i); }
  double y_vtx(unsigned int i) { return model.y_vtx(i); }
  double z_vtx(unsigned int i) { return model.z_vtx(i); }
  unsigned int polygon(unsigned int i) { return model.polygon(i); }
  size_t count_polygon() { return model.count_polygon(); }
  size_t count_vtx() { return model.count_vtx(); }
  double width() { return model.width(); }

 private:
  Model model;
};
}  // namespace s21