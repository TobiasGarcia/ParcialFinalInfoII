#ifndef ASTRO_H
#define ASTRO_H

#include <QPen>
#include <QBrush>
#include <QRandomGenerator>
#include <QGraphicsPixmapItem>

//Esta clase casi no posee código, pero resulta muy útil para poder cambiar el color
//a los astros, además de facilitar la detección de la colisión.

class Astro: public QGraphicsEllipseItem {
public:
    Astro(short radio);
    void change_color();
};

#endif // ASTRO_H
