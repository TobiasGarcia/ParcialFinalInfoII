#ifndef BALL_H
#define BALL_H

#include <QBrush>
#include <QPen>
#include <QRandomGenerator>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QObject>

class Ball: public QObject, public QGraphicsEllipseItem {

    Q_OBJECT

private:
    short radio;
    QTimer *move_timer;
    float time, aceleration, restitution;
    double initial_vy, initial_y, energy;

    void bounce();

public:
    Ball();
    ~Ball();
public slots:
    void move();
};

#endif // BALL_H
