#include <QDebug>
#include <tuple>
#include <set>

#include "player.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "battleship.h"
#include "battleship_factory.h"
#include "submarine.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    ,ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    scene_ = new QGraphicsScene;
    scene_2 = new QGraphicsScene;

    view_ = ui-> player1_view;
    view_2 = ui-> player2_view;

    view_ ->setScene(scene_);
    view_2 ->setScene(scene_2);


    view_->setSceneRect(0,0,view_->frameSize().width(), view_->frameSize().height());
    view_2->setSceneRect(0,0,view_2->frameSize().width(), view_2->frameSize().height());

    scene_ ->addRect(0,0, view_->frameSize().width(), view_->frameSize().height());
    scene_2 ->addRect(0,0, view_2->frameSize().width(), view_2->frameSize().height());


    player* p1 = new player();
    player* p2 = new player();

    players_.push_back(p1);
    players_.push_back(p2);


    // create the board using cells
    for(int y = 0; y < y_size_; y++) {
        std::vector<cell *> tmp;
        std::vector<cell *> tmp2;
        for(int x = 0; x < x_size_; x++) {
            int x_tuned = (x * cell::get_width());
            int y_tuned = (y * cell::get_width());
            cell *p1 = new cell(x_tuned, y_tuned);
            connect(p1, &cell::cellSelected, this, &MainWindow::cellSelectedSlot);
            cell *p2 = new cell(x_tuned, y_tuned);
            connect(p2, &cell::cellSelected, this, &MainWindow::cellSelectedSlot);

            tmp.push_back(p1);
            tmp2.push_back(p2);

            scene_->addItem(p1);
            scene_2 ->addItem(p2);
        }
        p1 -> set_board(tmp);
        p2 -> set_board(tmp2);
    }
    scene_ -> setBackgroundBrush(Qt::white);
    scene_2 -> setBackgroundBrush(Qt::white);

    for(int i=0; i < players_.size(); i++) {
        players_[i] -> set_storage(battleship_factory::GetCarrier());
        players_[i] -> set_storage(battleship_factory::GetCruiser());
        players_[i] -> set_storage(battleship_factory::GetDestroyer());
        submarine* sub = new submarine();
        players_[i] -> set_storage(sub);
    }
//    qDebug() << "ship total: " << players_[0] -> get_storage().size();
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::disguise_ships() {
    for(int i=0; i<players_.size(); i++) {
        for(int y = 0; y < y_size_; y++) {
            std::vector<cell *> tmp;
            for(int x = 0; x < x_size_; x++) {
                int x_tuned = (x * cell::get_width());
                int y_tuned = (y * cell::get_width());
                cell *c3 = new cell(x_tuned, y_tuned);
                c3 -> set_started(true);
                c3 -> set_color(QColor(0,255,0));
                tmp.push_back(c3);
                if(i == 0) {
                    scene_->addItem(c3);
                } else {
                    scene_2 ->addItem(c3);
                }
                connect(c3, &cell::layerSelected , this, &MainWindow::layerSelectedSlot);
            }
        players_[i] -> set_overlayer(tmp);
        }
    }
}

void MainWindow::on_start_clicked()
{
    qDebug() << "start clicked";
    disguise_ships();
    current_turn_ = 0;
    update();

}


void MainWindow::layerSelectedSlot(cell *c) {
    qDebug() << "over_layer cell clicked";
    qDebug() << c -> get_x() << ":" << c->get_y();
    player* p = players_[current_turn_ % 2];
    player *player_2 = players_[(current_turn_+1 ) % 2];
    int x = c -> get_x();
    int y = c -> get_y();

    if(!(c -> get_fired())) {
        if(current_turn_ % 2 == 0) { // player1's turn
            scene_2 -> removeItem(c);
        } else { // player2's turn
            scene_ -> removeItem(c); // overlayer cell of opponent's grid is removed.
        }
        update();
        c -> set_fired(true);
        battleship* b = findTargetShip(player_2, x, y);
    //    qDebug() << "calculated";
        if(b != nullptr) { //found battleship
            b -> damage_strength();
            qDebug() << "damage of ship: " << b->get_strength();
        } else {
            qDebug() << "This is null pointer";
        }
        if(check_winning(p)) {
            qDebug() << "game has ended"; // need to make stronger statement than this
            game_ended = true;
            std::string s = "Game has ended.";
            QString qs(s.c_str());
            ui->label_2 ->setText(qs);
        }
        current_turn_++;
    } // first remove and update

}

battleship* MainWindow::findTargetShip(player* p, int x, int y) {
    std::vector<battleship *> b =  p -> get_storage();

    for(int i=0; i< b.size(); i++) {
        int length = b[i] -> get_length();
        qDebug() << "length: " << length;
        for(int j=0; j <length; j++) {
            if(x == b[i]->get_x() && (y == b[i] -> get_y() + (j * b[i] -> get_width()))) {
//                qDebug() << "finding target: " << b[i]->get_x() << " : " << b[i] -> get_y() + (j * b[i] -> get_width());
                return b[i];
            }
        }
    }
    return nullptr;
}

bool MainWindow::check_winning(player* p) {
    std::vector<battleship *> b = p -> get_storage();
    for(int i = 0; i < b.size(); i++) {
        if(b[i] -> get_strength() != 0) {
            return false;
        }
    }
    return true;
}

void MainWindow::layerClickedSlot(cell *c) {
    // delete - qobject does not exist so no
}

void MainWindow::shipSelectedSlot(battleship *b) {
    if(b == nullptr) {
        qDebug() << "null";
    } else {
        qDebug() << "trigger ship";
    }
}

// Initial setting do it player1 - player2 repeatedly take turn.
void MainWindow::cellSelectedSlot(cell *c) {
    player *player = players_[current_turn_ % 2];
    if(player -> get_ship_id() < player -> get_storage().size()) {
        battleship* b = players_[current_turn_ % 2] -> get_battleship();
         b -> set_x(c -> get_x());
         b -> set_y(c -> get_y());
         // we need to check orientation
//         player -> set_ship(std::make_tuple(b, c -> get_x() , c-> get_y(), b -> get_strength()));
         connect(b, &battleship::shipSelected , this, &MainWindow::shipSelectedSlot);
         if(current_turn_ % 2 == 0) {
             scene_ -> addItem(b);
         } else {
             scene_2 -> addItem(b);
         }
        player -> set_current_ship_id(); //increment the id of the ship
        current_turn_++;
//        qDebug() << current_turn_%2;
        update();
    } else { // output to the user
        qDebug() << "all the ship has been displayed"; // change error message
    }
}
