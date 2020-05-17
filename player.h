#ifndef PLAYER_H
#define PLAYER_H

#include "battleship.h"
#include "cell.h"

#include <vector>
#include <tuple>

class player
{
public:
    player();

/*    void fire(int x, int y); */// fire at the opponent's cell that is clicked by mouse

    std::vector<battleship *>get_storage() {return  ship_storage_;}

    void set_storage(battleship* b) {ship_storage_.push_back(b);}

    void set_board(std::vector<cell*> tmp) {board_.push_back(tmp);}

//    void set_ship(std::tuple<battleship *, int, int, int> tup) {ship_detail_.push_back(tup);}

    void set_overlayer(std::vector<cell *> tmp) {overlayer_.push_back(tmp);}

    std::vector<std::vector<cell*>>get_board() {return board_;}

    battleship* get_battleship() {return ship_storage_[current_ship_id_];}


    int get_ship_total() {return total_ship_num_;}

//    std::vector<std::tuple<battleship*, int, int, int>>get_ship_detail() {return ship_detail_;}

    int get_ship_id() {return current_ship_id_;}

    void set_current_ship_id(){ current_ship_id_ += 1;}

    int get_size_x() {return x_size_;}

    int get_size_y() {return y_size_;}



private:
     std::vector<battleship *> ship_storage_;

     std::vector<std::vector<cell*>> board_;

     std::vector<std::vector<cell*>> overlayer_;

     std::vector<std::tuple<battleship*, int, int, int>>ship_detail_;

//     std::vector<std::vector<cell*>> board_;

     int total_ship_num_ = 4;

     int  current_ship_id_ = 0;

     int x_size_ = 20;

     int y_size_ = 20;

     int missiles_ = 10;

};



// implemented for actions of each player

#endif // PLAYER_H
