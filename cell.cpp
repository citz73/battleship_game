#include "cell.h"
#include "battleship.h"

#include <QPainter>
#include <QDebug>
#include <QtWidgets>
#include <QGraphicsScene>
//#include <QTest>


cell::cell(int x, int y)
{
    x_ = x;
    y_ = y;

    QColor color1(0,0,255);
    color_ = color1;
    setup_spot = false;
}

QRectF cell::boundingRect() const {
    return QRectF(x_, y_, width_, width_);
}

QPainterPath cell::shape() const {
    QPainterPath path;
    path.addRect(x_, y_, width_, width_);
    return path;
}

void cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget)

    QBrush b = painter -> brush();

    painter->setBrush(QBrush(this -> color_));
    painter -> drawRect(QRect(this->x_, this-> y_, this-> width_, this-> width_));

    painter -> setBrush(b);
}

// built so that mainwindow instance knows which cell is clicked by the user
void cell::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "cell is clicked";
//    qDebug() << event -> pos();
    if(!game_started) {
        if(event -> button() == Qt::LeftButton) {
          qDebug() << "setup_spot";
            setup_spot = true;
            emit cellSelected(this);
        }
    } else {
        if(event -> button() == Qt::LeftButton) {
//            qDebug() << "cell properly emited";
            emit layerSelected(this);
//            emit layerclickedSignal(this);

//            emit shipSelected(this);
        }
    }
//    if(event -> button() == Qt::rightButton) {
//        // change orientation
//    }
}


