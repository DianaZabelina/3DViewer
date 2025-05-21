#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  load_settings();
  connect(ui->pushButton_choiseFile, SIGNAL(clicked()), this,
          SLOT(read_file()));

  connect(ui->trans_x_box, SIGNAL(valueChanged(double)), this,
          SLOT(change_state()));
  connect(ui->trans_y_box, SIGNAL(valueChanged(double)), this,
          SLOT(change_state()));
  connect(ui->trans_z_box, SIGNAL(valueChanged(double)), this,
          SLOT(change_state()));

  connect(ui->rot_x_slider, SIGNAL(valueChanged(int)), this,
          SLOT(change_state()));
  connect(ui->rot_y_slider, SIGNAL(valueChanged(int)), this,
          SLOT(change_state()));
  connect(ui->rot_z_slider, SIGNAL(valueChanged(int)), this,
          SLOT(change_state()));

  connect(ui->scale_slider, SIGNAL(valueChanged(int)), this,
          SLOT(change_state()));

  connect(ui->pushButton_colorBackground, SIGNAL(clicked()), this,
          SLOT(change_back()));
  connect(ui->pushButton_colorEdges, SIGNAL(clicked()), this,
          SLOT(change_line()));
  connect(ui->pushButton_colorVerticies, SIGNAL(clicked()), this,
          SLOT(change_point()));

  connect(ui->solid_radioButton, SIGNAL(clicked()), this, SLOT(types_width()));
  connect(ui->dashed_radioButton, SIGNAL(clicked()), this, SLOT(types_width()));

  connect(ui->disable_radioButton, SIGNAL(clicked()), this,
          SLOT(types_width()));
  connect(ui->circle_radioButton, SIGNAL(clicked()), this, SLOT(types_width()));
  connect(ui->square_radioButton, SIGNAL(clicked()), this, SLOT(types_width()));

  connect(ui->parallel_radioButton, SIGNAL(clicked()), this,
          SLOT(types_width()));
  connect(ui->central_radioButton, SIGNAL(clicked()), this,
          SLOT(types_width()));

  connect(ui->edg_thickness_slider, SIGNAL(valueChanged(int)), this,
          SLOT(types_width()));
  connect(ui->ver_size_slider, SIGNAL(valueChanged(int)), this,
          SLOT(types_width()));

  connect(ui->pushButton_makeBMP, SIGNAL(clicked()), this, SLOT(make_bmp()));
  connect(ui->pushButton_makeJPEG, SIGNAL(clicked()), this, SLOT(make_jpeg()));
  connect(ui->pushButton_reset, SIGNAL(clicked()), this, SLOT(reset_vtx()));
}

MainWindow::~MainWindow() {
  save_settings();
  delete ui;
}

void MainWindow::read_file() {
  ui->filename_input_label->setText("");
  ui->ver_num_label->setText("");
  ui->edg_num_label->setText("");
  QString file = QFileDialog::getOpenFileName(this, tr("Open file"), ".",
                                              tr("Object files (*.obj)"));
  std::string str = file.toStdString();
  bool flag = ui->openGLWidget->read_file(str);
  if (!flag) {
    ui->openGLWidget->reset_vtx();
    ui->filename_input_label->setText(file);
    ui->ver_num_label->setText(QString::number(ui->openGLWidget->count_vtx()));
    ui->edg_num_label->setText(QString::number(ui->openGLWidget->count_pol()));
  }
}

void MainWindow::change_state() {
  double scale = ui->scale_slider->value();
  ui->scale_lineEdit->setText(QString::number(scale / 10));
  double rotate_x = ui->rot_x_slider->value();
  ui->rot_x_lineEdit->setText(QString::number(rotate_x));
  double rotate_y = ui->rot_y_slider->value();
  ui->rot_y_lineEdit->setText(QString::number(rotate_y));
  double rotate_z = ui->rot_z_slider->value();
  ui->rot_z_lineEdit->setText(QString::number(rotate_z));
  double move_x = ui->trans_x_box->value();
  double move_y = ui->trans_y_box->value();
  double move_z = ui->trans_z_box->value();
  ui->openGLWidget->change_state_obj(scale, rotate_x, rotate_y, rotate_z,
                                     move_x, move_y, move_z);
}

void MainWindow::change_color(int type, const QColor &color) {
  if (color.isValid()) {
    double r = color.redF();
    double g = color.greenF();
    double b = color.blueF();
    ui->openGLWidget->rgb(r, g, b, type);
    update_frame_color(type, color);
  }
}

void MainWindow::update_frame_color(int type, const QColor &color) {
  if (type == 0)
    ui->frame_colorBackground->setStyleSheet(
        QString("background-color: %1;").arg(color.name()));
  if (type == 1)
    ui->frame_colorEdges->setStyleSheet(
        QString("background-color: %1;").arg(color.name()));
  if (type == 2)
    ui->frame_colorVerticies->setStyleSheet(
        QString("background-color: %1;").arg(color.name()));
}

void MainWindow::change_back() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
  change_color(0, color);
}
void MainWindow::change_line() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
  change_color(1, color);
}
void MainWindow::change_point() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
  change_color(2, color);
}

void MainWindow::types_width() {
  int p = 0;
  if (ui->square_radioButton->isChecked()) p = 1;
  if (ui->circle_radioButton->isChecked()) p = 2;
  bool l = 0;
  if (ui->dashed_radioButton->isChecked()) l = 1;
  bool pr = 0;
  if (ui->central_radioButton->isChecked()) pr = 1;
  float p_size = ui->ver_size_slider->value();
  ui->ver_size_lineEdit->setText(QString::number(p_size));
  float l_width = ui->edg_thickness_slider->value();
  ui->edg_thickness_lineEdit->setText(QString::number(l_width));
  ui->openGLWidget->types_width(p, l, pr, p_size, l_width);
}

void MainWindow::load_settings() {
  QSettings settings("test4_settings", "set");

  ui->parallel_radioButton->setChecked(settings.value("ortho", "1").toBool());
  ui->central_radioButton->setChecked(settings.value("frustum", "0").toBool());

  ui->solid_radioButton->setChecked(settings.value("solid_line", "1").toBool());
  ui->dashed_radioButton->setChecked(
      settings.value("dashed_line", "0").toBool());

  ui->edg_thickness_slider->setValue(
      settings.value("line_width", "1").toDouble());

  ui->disable_radioButton->setChecked(settings.value("rb1", "1").toBool());
  ui->square_radioButton->setChecked(settings.value("rb2", "0").toBool());
  ui->circle_radioButton->setChecked(settings.value("rb3", "0").toBool());

  ui->ver_size_slider->setValue(settings.value("p_size", "1").toDouble());

  types_width();

  QColor line = settings.value("color_line", QColor(0, 100, 0)).value<QColor>();
  change_color(1, line);

  QColor point =
      settings.value("color_point", QColor(100, 0, 0)).value<QColor>();
  change_color(2, point);

  QColor back = settings.value("color_back", QColor(0, 0, 0)).value<QColor>();
  change_color(0, back);
}

QColor MainWindow::get_frame_color(QFrame *frame) {
  QString styleSheet = frame->styleSheet();
  QString colorString = styleSheet.mid(styleSheet.indexOf("#") + 1, 6);
  return QColor("#" + colorString);
}

void MainWindow::save_settings() {
  QSettings settings("test4_settings", "set");

  settings.setValue("ortho", ui->parallel_radioButton->isChecked());
  settings.setValue("frustum", ui->central_radioButton->isChecked());

  settings.setValue("solid_line", ui->solid_radioButton->isChecked());
  settings.setValue("dashed_line", ui->dashed_radioButton->isChecked());

  settings.setValue("line_width", ui->edg_thickness_slider->value());

  settings.setValue("rb1", ui->disable_radioButton->isChecked());
  settings.setValue("rb3", ui->circle_radioButton->isChecked());
  settings.setValue("rb2", ui->square_radioButton->isChecked());

  settings.setValue("p_size", ui->ver_size_slider->value());

  settings.setValue("color_back", get_frame_color(ui->frame_colorBackground));
  settings.setValue("color_line", get_frame_color(ui->frame_colorEdges));
  settings.setValue("color_point", get_frame_color(ui->frame_colorVerticies));
}

void MainWindow::make_screenshot(int type) {
  QImage screen = ui->openGLWidget->grabFramebuffer();
  if (type == 0) {
    QString path = QFileDialog::getSaveFileName(this, tr("Save screenshot"),
                                                "/Users/", "Image (*.bmp)");
    screen.save(path, "BMP");
  }
  if (type == 1) {
    QString path = QFileDialog::getSaveFileName(this, tr("Save screenshot"),
                                                "/Users/", "Image (*.jpeg)");
    screen.save(path, "JPEG");
  }
}

void MainWindow::make_bmp() { make_screenshot(0); }

void MainWindow::make_jpeg() { make_screenshot(1); }

void MainWindow::reset_vtx() {
  ui->openGLWidget->reset_vtx();
  ui->scale_slider->setValue(10);
  ui->trans_x_box->setValue(0);
  ui->trans_y_box->setValue(0);
  ui->trans_z_box->setValue(0);
  ui->rot_x_slider->setValue(0);
  ui->rot_y_slider->setValue(0);
  ui->rot_z_slider->setValue(0);
}
