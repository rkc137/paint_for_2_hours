#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);
    scene.set_rect(QRect(0, 0, 1000, 800));

    connect(ui->clr_butt, &QPushButton::clicked, this, [&](){
        QColorDialog dlg;
        if(dlg.exec() == QDialog::Accepted)
            scene.set_color(dlg.currentColor());
    });
    connect(ui->horizontalSlider, &QSlider::valueChanged, this, [&](){
        scene.set_pen_size(ui->horizontalSlider->value());
    });

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

MainWindow::~MainWindow()
{
    delete ui;
}

