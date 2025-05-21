#include "Model.h"
namespace s21 {
/**
 * Чтение файла
 *
 * @param file_name название файла
 *
 * @return ошибка, если не получилось прочитать файл
 */
bool Model::read_file(std::string file_name) {
  clear_obj();
  std::ifstream file;
  bool err = 0;
  file.open(file_name);
  if (file.is_open()) {
    std::string str;
    while (std::getline(file, str)) {
      if (str[0] == 'v' && str[1] == ' ') {
        parse_vertex(str);
      }
      if (str[0] == 'f' && str[1] == ' ') {
        parse_polygons(str);
      }
    }
  } else
    err = 1;
  file.close();
  if (err == 0) calc_centers();
  return err;
}

/**
 * Ввод данных из строки в переменную vtx
 *
 * @param str строка в файле
 */
void Model::parse_vertex(std::string str) {
  char* p = &str[1];
  for (int i = 0; i < 3; i++) vtx.push_back(strtod(p, &p));
}

/**
 * Ввод данных из строки в переменную polygons
 *
 * @param str строка в файле
 */
void Model::parse_polygons(std::string str) {
  char* p = &str[1];
  while (*p != '\0' && *p != '\r' && *p != '\n') {
    polygons.push_back(strtoul(p, &p, 10));
    while (!(*(p - 1) == ' ' || *p == '\0')) p++;
  }
  polygons.push_back(0);
}

/**
 * Вычисление ширины и централизация модели
 */
void Model::calc_centers() {
  double x_width = 0;
  double y_width = 0;
  double z_width = 0;
  find_width(&x_width, &y_width, &z_width);
  for (unsigned int i = 0; i < vtx.size() / 3; i++) {
    vtx[i * 3] = vtx[i * 3] - x_width;
    vtx[i * 3 + 1] = vtx[i * 3 + 1] - y_width;
    vtx[i * 3 + 2] = vtx[i * 3 + 2] - z_width;
  }
}

/**
 * Вычисление ширины модели через максимальные и минимальные значения осей
 *
 * @param x_width ширина модели по оси x
 * @param y_width ширина модели по оси y
 * @param z_width ширина модели по оси z
 */
void Model::find_width(double* x_width, double* y_width, double* z_width) {
  double x_max = vtx[0];
  double y_max = vtx[1];
  double z_max = vtx[2];
  double x_min = vtx[0];
  double y_min = vtx[1];
  double z_min = vtx[2];
  for (unsigned int i = 0; i < vtx.size() / 3; i++) {
    if (x_max < vtx[i]) x_max = vtx[i];
    if (y_max < vtx[i + 1]) y_max = vtx[i + 1];
    if (z_max < vtx[i + 2]) z_max = vtx[i + 2];
    if (x_min > vtx[i]) x_min = vtx[i];
    if (y_min > vtx[i + 1]) y_min = vtx[i + 1];
    if (z_min > vtx[i + 2]) z_min = vtx[i + 2];
  }
  *x_width = fabs(x_max - x_min);
  *y_width = fabs(y_max - y_min);
  *z_width = fabs(z_max - z_min);
  if (x_width >= y_width && x_width >= z_width) width_ = *x_width * 1.5;
  if (y_width >= x_width && y_width >= z_width) width_ = *y_width * 1.5;
  if (z_width >= y_width && z_width >= x_width) width_ = *z_width * 1.5;
  *x_width = (x_max + x_min) / 2;
  *y_width = (y_max + y_min) / 2;
  *z_width = (z_max + z_min) / 2;
}

/**
 * Очищение модели
 */
void Model::clear_obj() {
  vtx.clear();
  changed_vtx.clear();
  polygons.clear();
}

/**
 * Масштабирование модели
 *
 * @param s масштаб
 */
void Model::scale(double s) {
  s = s / 10;
  double a = s / s_;
  for (unsigned int i = 0; i < vtx.size(); i++) {
    changed_vtx[i] *= a;
  }
  s_ = s;
}

/**
 * Поворот модели по оси x
 *
 * @param r угол поворота в градусах
 */
void Model::rotate_x(double r) {
  double a = (r - r_x_) * M_PI / 180.0;
  for (unsigned int i = 0; i < vtx.size() / 3; i++) {
    double y = changed_vtx[i * 3 + 1];
    double z = changed_vtx[i * 3 + 2];
    changed_vtx[i * 3 + 1] = cos(a) * y - sin(a) * z;
    changed_vtx[i * 3 + 2] = sin(a) * y + cos(a) * z;
  }
  r_x_ = r;
}

/**
 * Поворот модели по оси y
 *
 * @param r угол поворота в градусах
 */
void Model::rotate_y(double r) {
  double a = (r - r_y_) * M_PI / 180.0;
  for (unsigned int i = 0; i < vtx.size() / 3; i++) {
    double x = changed_vtx[i * 3];
    double z = changed_vtx[i * 3 + 2];
    changed_vtx[i * 3] = cos(a) * x + sin(a) * z;
    changed_vtx[i * 3 + 2] = -sin(a) * x + cos(a) * z;
  }
  r_y_ = r;
}

/**
 * Поворот модели по оси z
 *
 * @param r угол поворота в градусах
 */
void Model::rotate_z(double r) {
  double a = (r - r_z_) * M_PI / 180.0;
  for (unsigned int i = 0; i < vtx.size() / 3; i++) {
    double x = changed_vtx[i * 3];
    double y = changed_vtx[i * 3 + 1];
    changed_vtx[i * 3] = cos(a) * x - sin(a) * y;
    changed_vtx[i * 3 + 1] = sin(a) * x + cos(a) * y;
  }
  r_z_ = r;
}

/**
 * Перемещение модели по оси x
 *
 * @param m расстояние относительно оси x
 */
void Model::move_x(double m) {
  double a = m - m_x_;
  for (unsigned int i = 0; i < vtx.size() / 3; i++) changed_vtx[i * 3] += a;
  m_x_ = m;
}

/**
 * Перемещение модели по оси y
 *
 * @param m расстояние относительно оси y
 */
void Model::move_y(double m) {
  double a = m - m_y_;
  for (unsigned int i = 0; i < vtx.size() / 3; i++) changed_vtx[i * 3 + 1] += a;
  m_y_ = m;
}

/**
 * Перемещение модели по оси z
 *
 * @param m расстояние относительно оси z
 */
void Model::move_z(double m) {
  double a = m - m_z_;
  for (unsigned int i = 0; i < vtx.size() / 3; i++) changed_vtx[i * 3 + 2] += a;
  m_z_ = m;
}

/**
 * Трансформация (масштабирование, поворот, перемещение) модели через паттерн
 * наблюдателя
 *
 * @param s масштаб
 * @param r_x поворот по оси x
 * @param r_y поворот по оси y
 * @param r_z поворот по оси z
 * @param m_x расстояние относительно оси x
 * @param m_y расстояние относительно оси y
 * @param m_z расстояние относительно оси z
 */
void Model::change_state_obj(double s, double r_x, double r_y, double r_z,
                             double m_x, double m_y, double m_z) {
  if (s != s_) scale(s);
  if (r_x_ != r_x) rotate_x(r_x);
  if (r_y_ != r_y) rotate_y(r_y);
  if (r_z_ != r_z) rotate_z(r_z);
  if (m_x != m_x_) move_x(m_x);
  if (m_y != m_y_) move_y(m_y);
  if (m_z != m_z_) move_z(m_z);
}

/**
 * Сброс модели
 */
void Model::reset_vtx() {
  changed_vtx = vtx;
  r_x_ = 0;
  r_y_ = 0;
  r_z_ = 0;
  m_x_ = 0;
  m_y_ = 0;
  m_z_ = 0;
  s_ = 1;
}

/**
 * Возвращение координаты вершины по оси x
 *
 * @param i вершина
 *
 * @return координата по оси x
 */
double Model::x_vtx(unsigned int i) { return changed_vtx[i * 3]; }

/**
 * Возвращение координаты вершины по оси y
 *
 * @param i вершина
 *
 * @return координата по оси y
 */
double Model::y_vtx(unsigned int i) { return changed_vtx[i * 3 + 1]; }

/**
 * Возвращение координаты вершины по оси z
 *
 * @param i вершина
 *
 * @return координата по оси z
 */
double Model::z_vtx(unsigned int i) { return changed_vtx[i * 3 + 2]; }

/**
 * Возвращение вершины или 0, где 0 - это разделитель полигонов
 *
 * @param i вершина
 *
 * @return вершина или 0
 */
unsigned int Model::polygon(unsigned int i) { return polygons[i]; }

/**
 * Возвращение количества граней модели
 *
 * @return количество граней
 */
size_t Model::count_polygon() { return polygons.size(); }

/**
 * Возвращение количества вершин модели
 *
 * @return количество вершин
 */
size_t Model::count_vtx() { return vtx.size() / 3; }

/**
 * Возвращение ширины
 *
 * @return ширина
 */
double Model::width() { return width_; }
}  // namespace s21