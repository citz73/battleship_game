#ifndef SUBMARINE_H
#define SUBMARINE_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsObject>

#include "battleship.h"

class submarine : public battleship
{
public:
    submarine();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

     static int get_width() {return width_;}

    int get_strength() override;

    int get_length() override;
    void damage_strength() override;

    int get_x() override;
    int get_y() override;


    void set_x(int x) override;
    void set_y(int y) override;





private:
    int x_;
    int y_;
    int damage_endurance_ = 3;
    int length_ = 3;
    QColor color_ = QColor(255,165,0); //orange
    bool visible = false;
    static const int width_ = 20;
};

#endif // SUBMARINE_H
