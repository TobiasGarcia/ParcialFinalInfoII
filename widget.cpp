#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget) {
    ui->setupUi(this);

    layout()->setMargin(0);
    setFixedSize(702, 702);

    gsimulation = new GSimulation(this);
}

Widget::~Widget() {
    delete ui;
    delete gsimulation;
}

