#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QImage>
#include <QHBoxLayout>
#include <QLabel>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    void computeXY(double heading, int x, int y, double angle, double distance,
                   int &xPos, int &yPos);
    void renderImg();
    void drawPie();
    void drawPolygon(double heading, int x, int y);

public slots:
    void timerOut();

private:
    QImage m_img;
    QHBoxLayout m_layout;
    QLabel m_label;
    double heading;
    int xPlane;
};

#endif // WIDGET_H
