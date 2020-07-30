#include "astro.h"

Astro::Astro(short radio) {

    radio *= 0.1;
    setRect(-radio, -radio, 2*radio, 2*radio);

    QColor color = QColor::fromRgb(QRandomGenerator::global()->generate());
    setBrush(color);
    setPen(color);
}
