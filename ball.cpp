#include "ball.h"
#include <QDebug>

Ball::Ball() {
    radio = 15;
    setRect(-radio, -radio, 2*radio, 2*radio);
    QColor color = QColor::fromRgb(QRandomGenerator::global()->generate());
    setBrush(color);
    setPen(color);
    setPos(rand()%(700 - 2*radio) + radio - 350, radio - 350);

    time = 0;
    aceleration = rand()%601;
    initial_vy = 0;
    initial_y = -350 + radio;
    restitution = 1;

    move_timer = new QTimer;
    connect(move_timer, &QTimer::timeout, this, &Ball::move);
    move_timer->start(50);
}

Ball::~Ball() {
    delete move_timer;
}

void Ball::move() {
    time += 0.06;
    setY(initial_y + initial_vy*time + 0.5*aceleration*time*time);

    energy = 0.5*(initial_vy + aceleration*time)*(initial_vy + aceleration*time) - aceleration*y();

    //Un pixel antes
    if ((698 - radio - 350) < y()) bounce();
}

void Ball::bounce() {
    setY(699 - radio - 350);
    initial_vy = -restitution*sqrt(2*aceleration*(y() - initial_y) + initial_vy*initial_vy);
    initial_y = y();
    time = 0;
}

