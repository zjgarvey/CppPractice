#include<iostream>
#include<vector>
#include<string>

using namespace std;

struct CLinkListNode { 
    //Used to iterate through the player turn order;

    char data = '1';
    CLinkListNode* next = nullptr;

    public : void makeCircle() { 
        //call this function when done making the list to loop it back
        CLinkListNode* temp = this;
        while (temp->next != nullptr){
            temp = temp->next;
        }
        temp->next = this;
    }

    CLinkListNode(char c){data = c;}
    CLinkListNode(CLinkListNode* prev, char c) {data = c; prev->next = this;}
};

class game {

    protected:

    int boardSize;
    vector<vector<char>> board;
    CLinkListNode* turnOrder = new CLinkListNode ('1');

    public:

    void base_initialize(int bs) {
        //determine turn order before calling this function
        //builds a board and loops turn order into a circle
        boardSize = bs;
        turnOrder->makeCircle();
        vector<char> row (boardSize, ' ');
        for (int i = 0; i < boardSize ; i++){
            board.push_back(row);
        }
    }

    void progressTurn() {
        //updates turn order
        turnOrder = turnOrder->next;
    }

    virtual void move(int i, int j) {
        //checks availability of board spot
        //plays player token there
        //progresses turn order
        if (isAvailable(i,j)){
            board[i][j] = turnOrder->data;
            progressTurn();
        }
        else { throw invalid_argument("Move unavailable, try again! \n");}
    }

    virtual bool isAvailable(int i, int j) {
        //checks if a board space is whitespace (empty)
        if (i >= boardSize || j >= boardSize || i < 0 || j < 0){
            return false;
        }
        if (board[i][j] == ' ') {
            return true;
        }
        return false;
    }

    virtual bool isWon(int i, int j) {
        //there are no winners for an undefined game :(
        return false;
    }

    void printBoard() {
        //prints a representation of the current board state
        cout << "Current board state: \n";
        for (int j = 0; j < 4*boardSize + 2; j++){
            cout << "-";
        }
        cout << "-\n";
        for (int i = 0; i < boardSize; i++){
            for (int j = 0; j < boardSize; j++){
                cout << " | " << board[i][j];
            }
            cout << " |\n";
            for (int j = 0; j < 4*boardSize + 2; j++){
                cout << "-";
            }
            cout << "-\n";
        }
    }
};

class tictactoe : public game {
    //win condition specified from tictactoe rules
    public :

    void initialize(int bs){ 
        turnOrder->data = 'O';
        turnOrder->next = new CLinkListNode(turnOrder, 'X');
        base_initialize(bs);
    }

    bool isWon(int i, int j, char winner) {
        //checks if placing winner on (i,j) is a win

        int counter = 0;
        //check for row win
        for (char c : board[i]) {
            if (c != winner) {break;}
            counter++;
        }
        if (counter == boardSize) {return true;}

        counter = 0;
        //check for column win
        for (int i2 = 0; i2 < boardSize; i2++){
            if (board[i2][j] != winner) {break;}
            counter++;
        }
        if (counter == boardSize){return true;}

        if (i == j){
            counter = 0;
            //check for normal diag win
            for (int i2 = 0; i2 < boardSize; i2++){
                if (board[i2][i2] != winner) {break;}
                counter++;
            }
            if (counter == boardSize){return true;}
        }

        if (i == boardSize - j - 1){
            counter = 0;
            //check for anti-diag win
            for (int i2 = 0; i2 < boardSize; i2++){
                if (board[i2][boardSize - i2 - 1] != winner) {break;}
                counter++;
            }
            if (counter == boardSize){return true;}
        }

        return false;
    }

    public : void play() {
        //initiates a game loop
        int i, j, counter;
        char winner;
        counter = 0;
        cout << "Welcome to tictactoe!\n" ;
        cout << "TODO: include rules \n";
        //begin game loop
        while (counter < boardSize*boardSize) {
            cout << "player " << turnOrder->data << "\'s move: type rownum followed by colnum \n";
            i = -1;
            j = -1;
            cin >> i >> j;
            if (i == -1 || j == -1){ 
                cout << "Error: try again\n";
            }
            else {
                winner = turnOrder->data;
                try{ 
                    move(i,j);
                    printBoard();
                    counter++;
                } catch (invalid_argument& e) {
                    cerr << e.what();
                }
                if (isWon(i,j,winner)){
                    cout << "Game won by player " << winner <<"!\n";
                    cout << "Please play again soon!\n";
                    return;
                }
            }
        }
        cout << "A tie! It looks like you'll have to play again!\n";
    }
};

int main() {
    tictactoe G;
    int bs = 3;
    cout << "How big of a board? ";
    cin >> bs;
    if (bs > 20) {
        cout << "Wow, that bored, huh? The Max size is 20, sicko!\n"; 
        bs = 20;
    }
    G.initialize(bs);
    G.play();
    return 0;
}