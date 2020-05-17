#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <QObject>
#include <QGraphicsItem>


class battleship : public QObject, public QGraphicsItem
{

public:
    battleship();
    battleship(int strength);
    battleship(int x , int y, int strength);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    static int get_width() {return width_;}

    virtual int get_strength(){return damage_endurance_;}

    virtual int get_length() {return length_;}
    virtual void damage_strength(){damage_endurance_ -= 1;}

    virtual void set_x(int x){x_ = x;}
    virtual void set_y(int y){y_ = y;}

    virtual int get_x() {return x_;}
    virtual int get_y() {return y_;}

signals:
    void shipSelected(battleship *);

protected:
    Q_OBJECT
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;


private:
    int x_;
    int y_;
    int hits_ = 0;
    int damage_endurance_;
    int length_ = 0;
    QColor color_;
    bool orientation;
    static const int width_ = 20;

};


#endif // BATTLESHIP_H


// I will modify the battleship later so that I can utilize inheritance so that I can create both
// battleship and submarine from the output. This experiement could take some time, so I am implementing
// for now, without such.
