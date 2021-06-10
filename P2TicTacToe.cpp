#include <iostream>
#include <limits>

enum Status {
    Empty = 0,
    AI = 1,
    Player = 2
};

struct Game {
    Status table[3][3] = {
            {Empty, Empty, Empty},
            {Empty, Empty, Empty},
            {Empty, Empty, Empty}
    };

    int empty_slots = 9;
    int next_x, next_y;

    Status check_status();

    int dfs_minimax(Status turn = AI, bool toplevel = true, int depth = 0);

    char get(int i, int j);

    void print();

    bool valid(int x);

    void handle_input();

    void loop();
};


Status Game::check_status() {
    // consider the binary layout of 1 and 2
    // the bitwise and operation automatically tells all the information we want.
    int sum_column = 0;
    int sum_row = 0;
    int empty_line = 0;
    for (int i=0; i<3; i++) {
        if (table[i][0]==table[i][1] && table[i][0]==table[i][2] && table[i][0]==AI) {
            return AI;
        }
        else if (table[i][0]==table[i][1] && table[i][0]==table[i][2] && table[i][0]==Player) {
            return Player;
        }
        else if (table[i][0]==Empty || table[i][1]==Empty || table[i][2]==Empty) {
            empty_line = empty_line+1;
        }
        if (table[0][i]==table[1][i] && table[0][i]==table[2][i] && table[0][i]==AI) {
            return AI;
        }
        else if (table[0][i]==table[1][i] && table[0][i]==table[2][i] && table[0][i]==Player) {
            return Player;
        }
        else if (table[0][i]==Empty || table[1][i]==Empty || table[2][i]==Empty) {
            empty_line = empty_line+1;
        }
    }
    if (table[0][0]==table[1][1] && table[1][1]==table[2][2] && table[0][0]!=Empty) {
        return table[0][0];
    }
    else if (table[0][0]==Empty || table[1][1]==Empty || table[2][2]==Empty) {
        empty_line = empty_line+1;
    }
    if (table[0][2]==table[1][1] && table[1][1]==table[2][0] && table[1][1]!=Empty) {
        return table[1][1];
    }
    else if (table[0][2]==Empty || table[1][1]==Empty || table[2][0]==Empty) {
        empty_line = empty_line+1;
    }
    if (empty_line==0) {
        return Empty;
    }
    else {
        return Empty;
    }
    //TODO
}

int Game::dfs_minimax(Status turn, bool toplevel, int depth) {
    Status status = check_status();
    if (status==AI || depth==9) return 0;
    else if (status==Player) return 1;
    else {
        int best_val=99999;
        if (turn == Player) {
            best_val = -99999;
            int play_value;
            for (int i=0; i<3; i++) {
                for (int j=0; j<3; j++) {
                    if (table[i][j] == Empty) {
                        table[i][j]=Player;
                        play_value=dfs_minimax(AI, false, depth+1);
                        if (play_value>best_val) {
                            best_val=play_value;
                        }
                        table[i][j]=Empty;
                    }
                }
            }
        }
        else if (turn == AI) {
            best_val = 99999;
            int ai_value;
            for (int i=0; i<3; i++) {
                for (int j=0; j<3; j++) {
                    if (table[i][j] == Empty) {
                        table[i][j]=AI;
                        ai_value=dfs_minimax(Player, false, depth+1);
                        if (ai_value<best_val) {
                            best_val=ai_value;
                        }
                        table[i][j]=Empty;
                    }
                }
            }
        }
        return best_val;
    }
    //TODO
}

void Game::print() {
    std::cout << "-------------" << std::endl;
    std::cout << "| " << get(0, 0) << " | " << get(0, 1) << " | " << get(0, 2) << " |\n";
    std::cout << "-------------" << std::endl;
    std::cout << "| " << get(1, 0) << " | " << get(1, 1) << " | " << get(1, 2) << " |\n";
    std::cout << "-------------" << std::endl;
    std::cout << "| " << get(2, 0) << " | " << get(2, 1) << " | " << get(2, 2) << " |\n";
    std::cout << "-------------" << std::endl;
}

bool Game::valid(int x) {
    return x <= 2 && x >= 0;
}

void Game::handle_input() {
    std::cout<<"Your move."<<std::endl;
    std::cout<<"What square? ";
    int x_pos;
    int y_pos;
    while (1) {
        //std::cout<<"123"<<std::endl;
        int square_pos;
        std::cin>>square_pos;
        switch (square_pos) {
        case 1:
            x_pos=0;
            y_pos=0;
            break;
        case 2:
            x_pos=0;
            y_pos=1;
            break;
        case 3:
            x_pos=0;
            y_pos=2;
            break;
        case 4:
            x_pos=1;
            y_pos=0;
            break;
        case 5:
            x_pos=1;
            y_pos=1;
            break;
        case 6:
            x_pos=1;
            y_pos=2;
            break;
        case 7:
            x_pos=2;
            y_pos=0;
            break;
        case 8:
            x_pos=2;
            y_pos=1;
            break;
        case 9:
            x_pos=2;
            y_pos=2;
            break;
        }
        if (table[x_pos][y_pos]==Empty) {
            table[x_pos][y_pos]=Player;
            break;
        }
        std::cout<<"give a empty position!"<<std::endl;


    }
    std::cout<<"The game now looks like this:"<<std::endl;
    Game::print();
    //TODO
}

char Game::get(int i, int j) {
    switch (table[i][j]) {
        case Empty:
            return ' ';
        case AI:
            return 'O';
        default:
            return 'X';
    }

}

void Game::loop() {
    //TODO
    std::cout<<"Welcome to TicTacYoe, the game of three in a row"<<std::endl;
    std::cout<<"I will be o, and you will be x"<<std::endl;
    std::cout<<"The square will be numbered like this:"<<std::endl;
    std::cout << "-------------" << std::endl;
    std::cout << "| " << "1" << " | " << "2" << " | " << "3" << " |\n";
    std::cout << "-------------" << std::endl;
    std::cout << "| " << "4" << " | " << "5" << " | " << "6" << " |\n";
    std::cout << "-------------" << std::endl;
    std::cout << "| " << "7" << " | " << "8" << " | " << "9" << " |\n";
    std::cout << "-------------" << std::endl;
    int move = 1;
    Status turn = AI;
    while (move<=9) {
        Status mid_win = check_status();
        if (mid_win == AI || mid_win == Player) {
            break;
        }
        //std::cout<<"111"<<std::endl;
        if (turn == Player) {
            //std::cout<<"123"<<std::endl;
            handle_input();
            //std::cout<<"123"<<std::endl;
            turn = AI;
            move = move+1;
        }
        else {
            int best_value = 99999;
            int current_value;
            int x;
            int y;
            for (int i=0; i<3; i++) {
                for (int j=0; j<3; j++) {
                    if (table[i][j] == Empty) {
                        //std::cout<<"123"<<std::endl;
                        table[i][j] = AI;
                        //std::cout<<"123"<<std::endl;
                        current_value = dfs_minimax(Player, true, move);
                        //std::cout<<"123"<<std::endl;
                        if (current_value < best_value) {
                            x=i;
                            y=j;
                            best_value = current_value;
                        }
                        table[i][j] = Empty;
                        //std::cout<<"123"<<std::endl;
                    }
                    //std::cout<<"123"<<std::endl;
                }
            }
            table[x][y] = AI;
            turn = Player;
            move = move+1;
            std::cout<<"The game now looks like this:"<<std::endl;
            Game::print();
        }
    }
    Status status = check_status();
    switch (status) {
        case Empty:
            std::cout << "draw!" << std::endl;
            break;
        case AI:
            std::cout << "I win! lol!" << std::endl;
            break;
        case Player:
            std::cout << "You win ... so what?" << std::endl;
            break;
    }

}

int P2TicTacToe() {
    Game game;
    game.loop();
    return 0;
}
