#include "submarine.h"
//#include "battleship.h"

#include <QDebug>
#include <QPainter>

submarine::submarine()
{
    x_ = 0;
    y_ = 0;
    damage_endurance_ = 3;
    length_ = 3;
}

void submarine::set_x(int x){x_ = x;}

void submarine::set_y(int y){y_ = y;}

int submarine::get_strength(){return damage_endurance_;}

int submarine::get_length() {return length_;}

void submarine:: damage_strength(){damage_endurance_ -= 1;}

int submarine::get_x() {return x_;}

int submarine::get_y() {return y_;}


QRectF submarine::boundingRect() const {
    return QRectF(x_, y_, width_, width_ * length_);
}

QPainterPath submarine::shape() const {
    QPainterPath path;
    path.addRect(x_, y_, width_, width_ * length_);
    return path;
}

void submarine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget)

    QBrush b = painter -> brush();

    painter->setBrush(QBrush(this -> color_));
    painter -> drawRect(QRect(this->x_, this-> y_, this-> width_, this-> width_ * length_));

    painter -> setBrush(b);
}


