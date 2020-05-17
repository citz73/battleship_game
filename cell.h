#ifndef CELL_H
#define CELL_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QGraphicsScene>
//#include <QTest>


class cell : public QObject, public QGraphicsItem
{
    // emit signals
    Q_OBJECT



public:
    cell(int x, int y);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    static int get_width() {return width_;}

    QColor get_color() {return color_;}

    void set_color(QColor color){color_ = color;}

    int get_x(){ return x_;}
    int get_y(){return y_;}

    bool get_setup_spot() {return setup_spot;}

    void set_setup_spot(bool value) {setup_spot = value;}

    void set_started(bool value) {game_started = value;}

    bool get_fired() {return fired_;}

    void set_fired(bool value) {fired_ = value;}

signals:
    void layerSelected(cell * c);

    void cellSelected(cell *c);

    void layerclickedSignal(cell *c);

protected:
     void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    int x_;
    int y_;
    QColor color_;
    bool setup_spot;
    bool game_started = false;
    bool fired_ = false;
    static const int width_ = 20;

};

#endif // CELL_H
