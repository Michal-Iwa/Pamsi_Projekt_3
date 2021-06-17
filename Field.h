#ifndef UNTITLED3_FIELD_H
#define UNTITLED3_FIELD_H
#include <iostream>
#include <algorithm>
using std::endl;
using std::cout;
using std::cin;
using std::cerr;


class Field {
private:
    int size;
    int length;
    char** game;
    char first{};
    int row,col;
    char colchar{};
    char who{};
public:
    Field();
    ~Field();
    void Draw()const;
    void Player_move();
    void AI_move();
    void Best_move();
    int Win();
    void End();

    int minimax(int depth,bool maximizingplayer, int alpha,int beta);
};


#endif //UNTITLED3_FIELD_H
