#include <gtest/gtest.h>

#include "../Model/Model.h"
using namespace s21;
TEST(Viewer, Read_file) {
  s21::Model a;
  EXPECT_TRUE(a.read_file("bad_file.txt"));
}
TEST(Viewer, Read_file_2) {
  s21::Model a;
  EXPECT_FALSE(a.read_file("data/1.txt"));
}
TEST(Viewer, Scale) {
  s21::Model a;
  a.read_file("data/1.txt");
  a.reset_vtx();
  std::vector<double> vtx;
  double s = 0.72;
  for (unsigned int i = 0; i < a.count_vtx(); i++) {
    vtx.push_back(a.x_vtx(i) * s);
    vtx.push_back(a.y_vtx(i) * s);
    vtx.push_back(a.z_vtx(i) * s);
  }
  a.change_state_obj(s * 10, 0, 0, 0, 0, 0, 0);
  for (unsigned int i = 0; i < a.count_vtx(); i++) {
    EXPECT_FLOAT_EQ(vtx[i * 3], a.x_vtx(i));
    EXPECT_FLOAT_EQ(vtx[i * 3 + 1], a.y_vtx(i));
    EXPECT_FLOAT_EQ(vtx[i * 3 + 2], a.z_vtx(i));
  }
}
TEST(Viewer, Move_X) {
  s21::Model a;
  EXPECT_FALSE(a.read_file("data/1.txt"));
  a.reset_vtx();
  std::vector<double> vtx;
  double m = 1.426;
  for (unsigned int i = 0; i < a.count_vtx(); i++) {
    vtx.push_back(a.x_vtx(i) + m);
    vtx.push_back(a.y_vtx(i));
    vtx.push_back(a.z_vtx(i));
  }
  a.change_state_obj(1, 0, 0, 0, m, 0, 0);
  for (unsigned int i = 0; i < a.count_vtx(); i++) {
    EXPECT_FLOAT_EQ(vtx[i * 3], a.x_vtx(i));
    EXPECT_FLOAT_EQ(vtx[i * 3 + 1], a.y_vtx(i));
    EXPECT_FLOAT_EQ(vtx[i * 3 + 2], a.z_vtx(i));
  }
}
TEST(Viewer, Move_Y) {
  s21::Model a;
  EXPECT_FALSE(a.read_file("data/1.txt"));
  a.reset_vtx();
  std::vector<double> vtx;
  double m = 1.426;
  for (unsigned int i = 0; i < a.count_vtx(); i++) {
    vtx.push_back(a.x_vtx(i));
    vtx.push_back(a.y_vtx(i) + m);
    vtx.push_back(a.z_vtx(i));
  }
  a.change_state_obj(1, 0, 0, 0, 0, m, 0);
  for (unsigned int i = 0; i < a.count_vtx(); i++) {
    EXPECT_FLOAT_EQ(vtx[i * 3], a.x_vtx(i));
    EXPECT_FLOAT_EQ(vtx[i * 3 + 1], a.y_vtx(i));
    EXPECT_FLOAT_EQ(vtx[i * 3 + 2], a.z_vtx(i));
  }
}
TEST(Viewer, Move_Z) {
  s21::Model a;
  EXPECT_FALSE(a.read_file("data/1.txt"));
  a.reset_vtx();
  std::vector<double> vtx;
  double m = 1.426;
  for (unsigned int i = 0; i < a.count_vtx(); i++) {
    vtx.push_back(a.x_vtx(i));
    vtx.push_back(a.y_vtx(i));
    vtx.push_back(a.z_vtx(i) + m);
  }
  a.change_state_obj(1, 0, 0, 0, 0, 0, m);
  for (unsigned int i = 0; i < a.count_vtx(); i++) {
    EXPECT_FLOAT_EQ(vtx[i * 3], a.x_vtx(i));
    EXPECT_FLOAT_EQ(vtx[i * 3 + 1], a.y_vtx(i));
    EXPECT_FLOAT_EQ(vtx[i * 3 + 2], a.z_vtx(i));
  }
}
TEST(Viewer, Rotate_X) {
  s21::Model a;
  EXPECT_FALSE(a.read_file("data/1.txt"));
  a.reset_vtx();
  std::vector<double> vtx;
  double angle = 45;
  double r = 45 * M_PI / 180.0;
  for (unsigned int i = 0; i < a.count_vtx(); i++) {
    vtx.push_back(a.x_vtx(i));
    vtx.push_back(cos(r) * a.y_vtx(i) - sin(r) * a.z_vtx(i));
    vtx.push_back(sin(r) * a.y_vtx(i) + cos(r) * a.z_vtx(i));
  }
  a.change_state_obj(1, angle, 0, 0, 0, 0, 0);
  for (unsigned int i = 0; i < a.count_vtx(); i++) {
    EXPECT_FLOAT_EQ(vtx[i * 3], a.x_vtx(i));
    EXPECT_FLOAT_EQ(vtx[i * 3 + 1], a.y_vtx(i));
    EXPECT_FLOAT_EQ(vtx[i * 3 + 2], a.z_vtx(i));
  }
}
TEST(Viewer, Rotate_Y) {
  s21::Model a;
  EXPECT_FALSE(a.read_file("data/1.txt"));
  a.reset_vtx();
  std::vector<double> vtx;
  double angle = 45;
  double r = 45 * M_PI / 180.0;
  for (unsigned int i = 0; i < a.count_vtx(); i++) {
    vtx.push_back(cos(r) * a.x_vtx(i) + sin(r) * a.z_vtx(i));
    vtx.push_back(a.y_vtx(i));
    vtx.push_back(-sin(r) * a.x_vtx(i) + cos(r) * a.z_vtx(i));
  }
  a.change_state_obj(1, 0, angle, 0, 0, 0, 0);
  for (unsigned int i = 0; i < a.count_vtx(); i++) {
    EXPECT_FLOAT_EQ(vtx[i * 3], a.x_vtx(i));
    EXPECT_FLOAT_EQ(vtx[i * 3 + 1], a.y_vtx(i));
    EXPECT_FLOAT_EQ(vtx[i * 3 + 2], a.z_vtx(i));
  }
}
TEST(Viewer, Rotate_Z) {
  s21::Model a;
  EXPECT_FALSE(a.read_file("data/1.txt"));
  a.reset_vtx();
  std::vector<double> vtx;
  double angle = 45;
  double r = 45 * M_PI / 180.0;
  for (unsigned int i = 0; i < a.count_vtx(); i++) {
    vtx.push_back(cos(r) * a.x_vtx(i) - sin(r) * a.y_vtx(i));
    vtx.push_back(sin(r) * a.x_vtx(i) + cos(r) * a.y_vtx(i));
    vtx.push_back(a.z_vtx(i));
  }
  a.change_state_obj(1, 0, 0, angle, 0, 0, 0);
  for (unsigned int i = 0; i < a.count_vtx(); i++) {
    EXPECT_FLOAT_EQ(vtx[i * 3], a.x_vtx(i));
    EXPECT_FLOAT_EQ(vtx[i * 3 + 1], a.y_vtx(i));
    EXPECT_FLOAT_EQ(vtx[i * 3 + 2], a.z_vtx(i));
  }
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}