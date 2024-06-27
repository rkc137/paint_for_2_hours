#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);
    scene.set_rect(QRect(0, 0, 1000, 800));

    connect(ui->save, &QAction::triggered, this, &MainWindow::save_scene);
    connect(ui->open, &QAction::triggered, this, &MainWindow::add_image_to_scene);

    connect(ui->clr_butt, &QPushButton::clicked, this, [&](){
        QColorDialog dlg;
        if(dlg.exec() == QDialog::Accepted)
            scene.set_color(dlg.currentColor());
    });
    connect(ui->brush_size_horizontalSlider, &QSlider::valueChanged, this, [&](){
        scene.set_pen_size(ui->brush_size_horizontalSlider->value());
        ui->brush_size_spinBox->setValue(ui->brush_size_horizontalSlider->value());
    });
    connect(ui->brush_size_spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [&](int change) {
        ui->brush_size_horizontalSlider->setValue(change);
    });ui->brush_size_horizontalSlider->setValue(ui->brush_size_horizontalSlider->value());

    connect(ui->pen, &QRadioButton::toggled, this, [&](){
        if(ui->pen->isChecked())
            scene.instrument = Scene::instruments::pen;
    });
    connect(ui->elps, &QRadioButton::toggled, this, [&](){
        if(ui->elps->isChecked())
            scene.instrument = Scene::instruments::elps;
    });
    connect(ui->rect, &QRadioButton::toggled, this, [&](){
        if(ui->rect->isChecked())
            scene.instrument = Scene::instruments::rect;
    });
}

void MainWindow::add_image_to_scene()
{
    QString file_path = QFileDialog::getOpenFileName(this, tr("открыть файл"), "://имя файла.png", tr("*.png", "*.jpeg"));
    scene.open_file(QFile(file_path));
}

void MainWindow::save_scene()
{
    QString file_path = QFileDialog::getSaveFileName(this, tr("сохранить файл"), "://имя файла.png", tr("*.png", "*.jpeg"));
    scene.save_file(QFile(file_path));
}

MainWindow::~MainWindow()
{
    delete ui;
}


