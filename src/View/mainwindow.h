#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QFileDialog>
#include <QFrame>
#include <QMainWindow>
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  void update_frame_color(int type, const QColor &color);
  void change_color(int type, const QColor &color);
  QColor get_frame_color(QFrame *frame);
  void make_screenshot(int type);
 private slots:
  void read_file();
  void change_state();
  void change_back();
  void change_line();
  void change_point();
  void types_width();
  void load_settings();
  void save_settings();
  void make_bmp();
  void make_jpeg();
  void reset_vtx();
};
#endif  // MAINWINDOW_H
