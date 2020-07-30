#ifndef BALL_H
#define BALL_H

#include <QPen>
#include <QBrush>
#include <QTimer>
#include <QRandomGenerator>
#include <QGraphicsEllipseItem>

#include "astro.h"

class Ball: public QObject, public QGraphicsEllipseItem {

    Q_OBJECT

private:
    QTimer *move_timer;
    QList<QGraphicsItem*> collisions;

    double initial_vy, initial_y;
    float time, aceleration;
    short radio;

    void bounce();
    void collisions_handler(QList<QGraphicsItem*> collisions);

public:
    Ball();
    ~Ball();

public slots:
    void move();

};

#endif // BALL_H
