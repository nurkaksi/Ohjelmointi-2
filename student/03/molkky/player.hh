#ifndef PLAYER_HH
#define PLAYER_HH
#include <string>

using namespace std;

class Player
{
public:
    Player(const string& name);
    string get_name() const;
    int get_points() const;
    bool has_won() const;
    int add_points(int pts);


private:
    string name_;
    int points_;

};



#endif // PLAYER_HH
