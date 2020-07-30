#include "ball.h"

Ball::Ball() {

    radio = 15;
    setRect(-radio, -radio, 2*radio, 2*radio);
    setPos(rand()%(700 - 2*radio) + radio - 350, radio - 350);

    QColor color = QColor::fromRgb(QRandomGenerator::global()->generate());
    setBrush(color);
    setPen(color);

    time = 0;

    initial_vy = 0;
    initial_y = -350 + radio;
    aceleration = rand()%601;

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

    collisions_handler(collidingItems());

    //698 - radio - 350 corresponde a un pixel antes de la posición más baja.
    if ((698 - radio - 350) < y()) bounce();
}

void Ball::bounce() {
    setY(699 - radio - 350);

    initial_vy = -sqrt(2*aceleration*(y() - initial_y) + initial_vy*initial_vy);
    initial_y = y();

    time = 0;
}

void Ball::collisions_handler(QList<QGraphicsItem*> collisions) {

    QGraphicsItem *item;
    for (short i = 0; i < collisions.size(); i++) {

        item = collisions[i];
        if (typeid(*item) == typeid(Astro)) {

            Astro *astro = dynamic_cast<Astro*>(item);
            astro->change_color();
            delete this;
        }
    }
}

