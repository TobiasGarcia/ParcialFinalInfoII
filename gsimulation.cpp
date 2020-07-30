#include "gsimulation.h"

GSimulation::GSimulation(QWidget *parent) : QGraphicsView(parent) {

    //La variable parent es utilizada para poder colocar el QGraphicsView dentro
    //del Widget.

    srand(time(nullptr));

    //Establecemos las dimensiones del QGraphicsView en 702 x 702 pixeles para poder
    //colcoar una escena de 700 x 700 pixeles.

    setGeometry(0, 0, 702, 702);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene = new QGraphicsScene;
    scene->setSceneRect(-350, -350, (width() - 2), (height() - 2));
    setScene(scene);

    update_timer = new QTimer;
    connect(update_timer, &QTimer::timeout, this, &GSimulation::move);

    //Añadimos los astros de la simulación

    add_astro(0, 0, 0, 0, 50000, 200);
    add_astro(-5000, 0, 0, -2, 70, 70);
    add_astro(5000, 0, 0, 2, 70, 70);
    add_astro(0, -5000, 2, 0, 70, 70);
    add_astro(0, 5000, -2, 0, 70, 70);
    update_timer->start(20);
}

GSimulation::~GSimulation() {
    delete update_timer;
    delete scene;
}

void GSimulation::add_astro(double x0, double y0, double vx, double vy, double mass, short radio) {

    Astro *astro = new Astro(radio);

    astro->setPos(x0*(700./16000.), -y0*(700./16000.));
    scene->addItem(astro);

    astros.push_back(astro);

    std::array<double, 7> astro_data = {0, 0, vx, vy, x0, y0, mass};
    data.push_back(astro_data);
}

void GSimulation::keyPressEvent(QKeyEvent *event) {

    if (!event->isAutoRepeat() and  (event->key() == Qt::Key_Return))  {
        ball = new Ball();
        scene->addItem(ball);
        balls.append(ball);
    }
}

void GSimulation::move() {

    for (unsigned short i = 0; i < data.size(); i++) {
        for (unsigned short j = (i + 1); j < data.size(); j++) {

            cube_dist = pow(pow(data[i][4] - data[j][4], 2) + pow(data[i][5] - data[j][5], 2), 1.5);

            a_aux = (data[j][4] - data[i][4])/cube_dist;

            data[i][0] += a_aux*data[j][6];

            data[j][0] += -a_aux*data[i][6];

            a_aux = (data[j][5] - data[i][5])/cube_dist;

            data[i][1] += a_aux*data[j][6];
            data[j][1] += -a_aux*data[i][6];
        }

        data[i][2] = data[i][2] + dt*G*data[i][0];
        data[i][3] = data[i][3] + dt*G*data[i][1];

        data[i][4] = data[i][4] + dt*data[i][2];
        data[i][5] = data[i][5] + dt*data[i][3];

        astros[i]->setPos(data[i][4]*(700./16000.), -data[i][5]*(700./16000.));

        data[i][0] = 0;
        data[i][1] = 0;
    }
}
