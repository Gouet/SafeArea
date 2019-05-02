#include <QPainter>
#include <math.h>
#include <QDebug>
#include <QTimer>
#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent),
    m_img(200, 200, QImage::Format::Format_RGB32), m_layout(this)
{
    m_img.fill(QColor("#000000"));
    m_label.setPixmap(QPixmap::fromImage(m_img));
    m_layout.addWidget(&m_label);
    heading = 0;
    xPlane = 0;
    QTimer *timer = new QTimer();

    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timerOut()));
    timer->setInterval(20);
    timer->start();
}

void Widget::timerOut() {
    drawPolygon(heading, xPlane, 100);
    if (heading > 359)
        heading = 0;
    xPlane++;
    heading++;
}

void Widget::renderImg() {
    m_label.setPixmap(QPixmap::fromImage(m_img));
}

void Widget::computeXY(double heading, int x, int y, double angle, double distance,
               int &xPos, int &yPos) {
    double newAngle = -heading + 90 + angle;
    //qDebug() << newAngle;
    if (newAngle < 0) {
        newAngle = 360 + newAngle;
    }
    if (newAngle > 359) {
        newAngle = newAngle - 360;
    }
    qDebug() << "newAngle: " << newAngle;

    xPos = (int)(distance * cos(newAngle * M_PI / 180));
    yPos = (int)(distance * sin(newAngle * M_PI / 180));

    xPos = xPos + x;
    yPos = -yPos + y;

}

void Widget::drawPolygon(double heading, int x, int y) {
    m_img.fill(QColor("#000000"));
    double distance = 20;
    QPointF points[3] = {
        QPointF(10.0, 80.0),
        QPointF(20.0, 10.0),
        QPointF(80.0, 30.0)
    };

    int xPos = 0;
    int yPos = 0;
    computeXY(heading, x, y, 30, distance + 5, xPos, yPos);
    points[0].setX(xPos);
    points[0].setY(yPos);
    computeXY(heading, x, y, 150, distance + 5, xPos, yPos);
    points[1].setX(xPos);
    points[1].setY(yPos);
    points[2].setX(x);
    points[2].setY(y);

    QPainter painter(&m_img);
    painter.setPen(QPen(QColor(Qt::white)));
    painter.setBrush(QBrush(QColor(Qt::white)));
    painter.drawPolygon(points, 3);

    computeXY(heading, x, y, 210, distance + 5, xPos, yPos);
    points[0].setX(xPos);
    points[0].setY(yPos);
    computeXY(heading, x, y, 330, distance + 5, xPos, yPos);
    points[1].setX(xPos);
    points[1].setY(yPos);
    points[2].setX(x);
    points[2].setY(y);
    painter.drawPolygon(points, 3);

    painter.setPen(QPen(QColor(Qt::blue)));
    painter.setBrush(QBrush(QColor(Qt::blue)));
    computeXY(heading, x, y, 150, distance, xPos, yPos);
    points[0].setX(xPos);
    points[0].setY(yPos);
    computeXY(heading, x, y, 210, distance, xPos, yPos);
    points[1].setX(xPos);
    points[1].setY(yPos);
    points[2].setX(x);
    points[2].setY(y);
    painter.drawPolygon(points, 3);



    m_img.setPixelColor(x, y, QColor("#00FF00"));

    renderImg();
}

void Widget::drawPie() {
    m_img.setPixelColor(10, 10, QColor("#FFFFFF"));

    QRectF rectangle(10.0, 20.0, 80.0, 60.0);
    int startAngle = 90 * 16;
    int spanAngle = 120 * 16;

    QPainter painter(&m_img);
    painter.setPen(QPen(QColor(Qt::color0)));
    painter.setBrush(QBrush(QColor(Qt::color0), Qt::NoBrush));
    painter.drawPie(rectangle, startAngle, spanAngle);



    renderImg();
}

Widget::~Widget()
{

}
