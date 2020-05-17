#include "battleship.h"

#include <QDebug>
#include <QPainter>


battleship::battleship() {
    x_ = 0;
    y_ = 0;
    damage_endurance_ = 0;
}


// constructor for battleship
battleship::battleship(int x, int y, int strength)
{
    x_ = x; // orietation of x
    y_ = y; // orientation of y
    damage_endurance_ = strength; // try to make it const int
    length_ = strength;
    QColor c(0 , 0, 0);
    color_ = c;

}

// constructor for battleship for test case
battleship::battleship(int strength) {
    x_ = 0;
    y_ = 0;
    damage_endurance_ = strength;
    length_ = strength;
    QColor c(0, 0, 0);
    color_ = c;
}

// Qobject recognition process
QRectF battleship::boundingRect() const {
    return QRectF(x_, y_, width_, width_ * length_);
}

QPainterPath battleship::shape() const {
    QPainterPath path;
    path.addRect(x_, y_, width_, width_ * length_);
    return path;
}

void battleship::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget)

    QBrush b = painter -> brush();

    painter->setBrush(QBrush(this -> color_));
    painter -> drawRect(QRect(this->x_, this-> y_, this-> width_, this-> width_ * length_));

    painter -> setBrush(b);
}

void battleship::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "battleship is clicked";
    emit shipSelected(this);
}

