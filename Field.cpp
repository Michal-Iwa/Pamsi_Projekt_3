
#include "Field.h"

//inicialization of the field
Field::Field() {
    size=0;
    row=0;
    col=0;
    length=0;
    do{
    cout<<"Choose size of the field (length of one side of the field): "<<endl;
    cin>>size;
    cout<<"How many circles or crosses in a row to win?"<<endl;
    cin>>length;
    if(size<length){
        cout<<"Amount of signs in a row can't be bigger than length of one side of the field.Try again."<<endl;
    }
    if(!cin.good()){
        cout<<"Error: This is not a number maybe try again later."<<endl;
        size=0;
        length=0;
    }
    }while(size<length);
    game = new char*[size];
    for(auto i=0; i < size; i++){
        game[i]= new char[size];
    }
    for(auto i=0; i < size; i++){
        for(auto j=0; j < size; j++){
            game[i][j]=' ';
        }
    }
    Draw();
    cout<<"You are going to play with circles against AI's crosses"<<endl;
    cout<<"Do you want to have the first move(y-yes, n-no):"<<endl;
    cin>>first;
    if(first=='y'){
        Player_move();
    }
    else
        AI_move();
}

void Field::Draw()const {
    char tmp='A';
    for(int i=0;i<=size;i++){
        for(int j=0;j<=size;j++){
            if(i==0 && j==0) cout<<"    ";
            else if(i==0){
                cout<<"| "<<tmp<<" ";
                tmp++;
            }
            else{
                if(j!=0) cout << "| " << game[i - 1][j - 1]<<" ";
                else {
                cout << " " << i<<" ";
                    if(i<10) cout<<" ";
                }
            }
            }
        cout<<endl;
        if(i!=size){
            for(int k=0;k<size;k++){
                if(k==0) cout<<"-";
                cout<<"---|";
            }
            cout<<"---"<<endl;
        }
    }
}

void Field::Player_move() {
    int count=0;
    do {
        if(count>0){
            cout<<"This spot is taken try another one"<<endl;
        }
        cout << "what row do you what to put your circle in( for example 1 or 2 or 3 ...)";
        cin >> row;
        row -= 1;
        cout << "what column do you what to put your circle in"<<endl
             <<"( for example A or B or C ...)";
        cin >> colchar;
        col = int(colchar) - 65;
        count++;
    }while(game[row][col]!=' ');
            game[row][col] = 'O';
            Draw();
            int x=Win();
    if(x==0){
        cout<<"tie";
        End();
    }
    if(x==-10){
        cout<<"human wins";
        End();
    }
    AI_move();
}

void Field::AI_move() {
    Best_move();
    Draw();
    int x=Win();
    if(x==0){
        cout<<"tie";
        End();
    }
    if(x==10){
        cout<<"ai wins";
        End();
    }
    Player_move();
}

int Field::Win() {
    int amount=0;
    //horizontal check
    for(int i=0; i<size;i++){
        who=game[i][0];
        for(int j=0;j<size;j++){
            if(who!=' '){
                if(who==game[i][j]) amount++;
                else amount=0;
                if(amount==length ) {
                    if (who == 'X')return 10;
                    return -10;
                }
            }
            else amount=0;
            who=game[i][j];
        }
        amount=0;
    }
    //vertical check
    amount=0;
    for(int i=0; i<size;i++){
        who=game[0][i];
        for(int j=0;j<size;j++){
            if(who!=' '){
                if(who==game[j][i]) amount++;
                else amount=0;
                if(amount==length) {
                    if (who == 'X')return 10;
                    return -10;
                }
            }
            else amount=0;
            who=game[j][i];
        }
        amount=0;
    }
    //slant check
    int x=size-length;
    int y=x;
    int y2;
    amount=0;
    int amount2=0;
    char who2;
    while(y>-1){
        who=game[0][y];
        who2=game[y][0];
        y2=y;
        for(int i=0;i<size-y;i++){
            if(who!=' '){
                if(who==game[i][y2]) amount++;
                else amount=0;
                if(amount==length)  {
                    if (who == 'X')return 10;
                    return -10;
                }
            }
            if(who2!=' '){
                if(who2==game[y2][i]) amount2++;
                else amount2=0;
                if(amount2==length)  {
                    if (who2 == 'X')return 10;
                    return -10;
                }
            }
            who=game[i][y2];
            who2=game[y2][i];
            y2++;
        }
        y--;
    }
    y=x;
    amount = 0;
    amount2 =0;
    while(y>-1){
        who=game[0][size-y-1];
        who2=game[y][size-1];
        y2=size-y-1;
        for(int i=0;i<size-y;i++){
            if(who!=' '){
                if(who==game[i][y2]) amount++;
                else amount=0;
                if(amount==length)  {
                    if (who == 'X')return 10;
                    return -10;
                }
            }
            if(who2!=' '){
                if(who2==game[i+y][size-i-1]) amount2++;
                else amount2=0;
                if(amount2==length)
                {
                    if (who2 == 'X')return 10;
                    return -10;
                }
            }
            who=game[i][y2];
            who2=game[i+y][size-i-1];
            y2--;
        }
        y--;
    }
    bool tie=true;
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(game[i][j]==' ') tie=false;
        }
    }
    if(tie)
        return 0;
    return 1;
}

void Field::End() {
    for(auto i =0; i <size; i--){
        delete [] game[i];
    }
    delete []game;
    exit(0);
}

void Field::Best_move() {
    int best_score = -10;
    int move[2];
    for(int i =0;i<size;i++){
        for(int j =0;j<size;j++){
            if(game[i][j]==' '){
                game[i][j]='X';
                int score= minimax(0, false,-10,10);
                game[i][j]=' ';
                if(score > best_score){
                    best_score=score;
                    move[0]=i;
                    move[1]=j;
                }
            }
        }
    }
    game[move[0]][move[1]]='X';
}

int Field::minimax(int depth, bool maximizingPlayer, int alpha, int beta) {
    int x=Win();
    if(x==10 || x==-10 || x==0){
        return x;
    }
    if (maximizingPlayer){
        int best = -10;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (game[i][j] == ' ') {
                    game[i][j]='X';
                    int val = minimax(depth + 1, false, alpha, beta);
                    game[i][j]=' ';
                    best = std::max(best, val);
                    alpha = std::max(alpha, best);

                    // Alpha Beta Pruning
                    if (beta <= alpha)
                      break;
                    }
                }
            }
            return best;
        }
        int best = 10;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                   if (game[i][j] == ' ') {
                       game[i][j]='O';
                        int val = minimax(depth + 1, true, alpha, beta);
                        game[i][j]=' ';
                        best = std::min(best, val);
                        alpha = std::min(alpha, best);

                        // Alpha Beta Pruning
                        if (beta <= alpha)
                            break;
                   }
            }
        }
        return best;
    }

Field::~Field(){
    for(auto i =0; i <size; i--){
        delete [] game[i];
    }
    delete []game;
}



