#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}

/*double input = 0.0;
double out_n1 = 0.0;
double output = 0.0;
//double alpha = 0.95;

double kp = 0.01;
double ki = 0.001;
double kd = 0.1;

double integrator = 0.0;

for(int step = 0; step <= 500; step++)
{
    if(step == 100) input = 1.0;
    if(step == 300) input = 0.0;

    out_n1 = output;
    double error = input - output;
    output = (kp * error) + (ki * error);

    //alpha * output + (1 - alpha) * input;


    qreal y = output;
    //output = input;

     //qSin((M_PI / 50) * step) * qExp((step / 100.f) * (1.f))
    series->append((qreal)step, y);

}*/
