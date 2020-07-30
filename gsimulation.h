#ifndef GSIMULATION_H
#define GSIMULATION_H

#include <math.h>

#include <QTimer>
#include <QKeyEvent>
#include <QGraphicsView>

#include "astro.h"
#include "ball.h"

class GSimulation: public QGraphicsView {

    Q_OBJECT

private:
    Ball *ball;

    QList<Astro*> astros;
    QGraphicsScene *scene;

    float dt = 12;
    double G = 1, a_aux, cube_dist;

    //Contiene: ax, ay, vx, vy, x, y, mass de cada planeta.
    std::vector<std::array<double, 7>> data;

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
