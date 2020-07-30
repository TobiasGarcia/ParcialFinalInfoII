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

    //Comenzamos el movimiento de los astros.

    update_timer->start(20);
}

GSimulation::~GSimulation() {
    delete update_timer;
    delete scene;
}

void GSimulation::add_astro(double x0, double y0, double vx, double vy, double mass, short radio) {

    Astro *astro = new Astro(radio);

    //Escalamos los 700 x 700 pixels de la escena para manejar dimensiones de 16000 x 16000 metros en lo
    //que respecta a los astros, los objetos que caen tienen una escala diferente.

    astro->setPos(x0*(700./16000.), -y0*(700./16000.));
    scene->addItem(astro);

    astros.push_back(astro);

    std::array<double, 7> astro_data = {0, 0, vx, vy, x0, y0, mass};
    data.push_back(astro_data);
}

void GSimulation::keyPressEvent(QKeyEvent *event) {

    //Utilizamos la tecla Enter, cercana a las flechas del teclado, para colorcar los objetos que caen.

    //NOTA: Qt::Key_Enter es el Enter del Numeric Keypad.

    if (!event->isAutoRepeat() and  (event->key() == Qt::Key_Return))  {
        ball = new Ball();
        scene->addItem(ball);
    }
}

void GSimulation::move() {

    for (unsigned short cur = 0; cur < data.size(); cur++) {
        for (unsigned short other = (cur + 1); other < data.size(); other++) {

            cube_dist = pow(pow(data[cur][4] - data[other][4], 2) + pow(data[cur][5] - data[other][5], 2), 1.5);

            //Calculamos la aceleración aceleración auxiliar (la aceleración que siente el astro pero dividida
            //sobre su masa) de los dos astros, pues esta es la misma para ambos.

            a_aux = (data[other][4] - data[cur][4])/cube_dist;

            //Calculamos la aceleración multiplicando por la masa de cada uno la aceleración auxiliar.

            data[cur][0] += a_aux*data[other][6];
            data[other][0] += -a_aux*data[cur][6];

            //El mismo proceso para la aceleración en Y.

            a_aux = (data[other][5] - data[cur][5])/cube_dist;

            data[cur][1] += a_aux*data[other][6];
            data[other][1] += -a_aux*data[cur][6];
        }

        //Actulizamos las componentes en X e Y de la velocidad del astro actual (cur).

        data[cur][2] = data[cur][2] + dt*G*data[cur][0];
        data[cur][3] = data[cur][3] + dt*G*data[cur][1];

        //Actulizamos las componentes en X e Y de la posición del astro actual (cur).

        data[cur][4] = data[cur][4] + dt*data[cur][2];
        data[cur][5] = data[cur][5] + dt*data[cur][3];

        astros[cur]->setPos(data[cur][4]*(700./16000.), -data[cur][5]*(700./16000.));

        //Reiniciamos las componentes en X e Y de la aceleración  del astro actual (cur).

        data[cur][0] = 0;
        data[cur][1] = 0;
    }
}
