#ifndef GSIMULATION_H
#define GSIMULATION_H

#include <QGraphicsView>
#include <QTimer>
#include <QKeyEvent>
#include <math.h>
#include "astro.h"
#include "ball.h"

void str2double(QString str, double &dec, short &ten_pow);

class GSimulation: public QGraphicsView {

    Q_OBJECT

private:

    float dt = 12;
    QList<Astro*> astros;
    QGraphicsScene *scene;
    Ball *ball;

    double G = 1, a_aux, cube_dist;

    std::vector<std::array<double, 7>> data; //ax, ay, vx, vy, x, y, m
    QList<Ball*> balls;

public:
    QTimer *update_timer;

    void add_astro(double x0, double y0, double vx, double vy, double mass, short radio);
    void keyPressEvent(QKeyEvent *event);

    GSimulation(QWidget *parent);
    ~GSimulation();

public slots:
    void move();

};

#endif // GSIMULATION_H
