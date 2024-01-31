#include "player.hh"
#include <string>

using namespace std;


Player::Player(const string& name):
    name_(name), points_(0) {

}

string Player::get_name() const {
    return name_;
}

int Player::get_points() const {
    return points_;
}

bool Player::has_won() const {
    return points_ == 50;
}

int Player::add_points(int pts) {
    if ( (points_ + pts) == 0 ) {
        return points_ = pts;
    } else if ( (points_ + pts) > 50 ) {
        return points_ = 25;
    }else {
        return points_ += pts;
    }


}
