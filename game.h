// define your classes here...

class player{
public:
    player(double set_x, double set_y, player *set_next_player);
    void move(double t);
    double get_x();
    double get_y();
    player *get_next();
    void set_next(player *set_next_player);

private:
    double x;
    double y;
    player *next_player;
};

class game{
public:
    game();
    ~game();

    void spawn( double new_x, double new_y);
    void time(double t);
    void lunch();
    void num();
    void prt(double d);
    void over();
private:
    int num_players{0};
    player *player_head;  
};
