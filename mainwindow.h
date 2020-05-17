#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "cell.h"
#include "player.h"
#include "battleship.h"
#include "battleship_factory.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <vector>
#include <tuple>
#include <set>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


//    void placeBattleShip(int x, int y); // x and y coordinate refers to the orientation

    void disguise_ships();

    void fire_displayed();

    bool check_winning(player * p);

    battleship* findTargetShip(player*, int x, int y);




private slots:

    void on_start_clicked();

    void cellSelectedSlot(cell* c);

    void layerSelectedSlot(cell* c);

    void layerClickedSlot(cell* c);

    void shipSelectedSlot(battleship* b);

private:
    Ui::MainWindow *ui;

    QGraphicsView *view_;
    QGraphicsScene* scene_;

    QGraphicsView *view_2;
    QGraphicsScene* scene_2;

    // Need to create second view for the second player

/*    std::vector<battleship *> ship_storage_; *///saves all the ships that needs to be placed on the board and keep track of their status
//    std::vector<std::tuple<int,int>> fired_spots_;


   std::vector<player *> players_;// creates two players where they will take turn in playing the game

//   player *p1;
//   player *p2;

//    int total_ship_num_ = 3;

//    int  current_ship_id_ = 0;

   int current_turn_ = 0;

    int x_size_ = 20;

    int y_size_ = 20;

    bool game_ended = false;
};
#endif // MAINWINDOW_H
