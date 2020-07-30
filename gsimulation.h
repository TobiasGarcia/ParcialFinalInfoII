#ifndef GSIMULATION_H
#define GSIMULATION_H

#include <QGraphicsView>
#include <QTimer>
#include <math.h>
#include "astro.h"

void str2double(QString str, double &dec, short &ten_pow);

class GSimulation: public QGraphicsView {

    Q_OBJECT

private:

    float dt = 12;
    QList<Astro*> astros;
    QGraphicsScene *scene;

    double G = 1, a_aux, cube_dist;

    std::vector<std::array<double, 7>> data; //ax, ay, vx, vy, x, y, m

public:
    QTimer *update_timer;

    void add_astro(double x0, double y0, double vx, double vy, double mass, short radio);
    GSimulation(QWidget *parent);
    ~GSimulation();

public slots:
    void move();

};

#endif // GSIMULATION_H
