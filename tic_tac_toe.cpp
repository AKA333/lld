#include <bits/stdc++.h>

using namespace std;

// design tic tac toe:
// Req:
// - can play x o 3x3 grid
// - wins if completed row column or diagonal
// - can get board status at any isntance
// - invalid moves should be rejected

enum class Piece {
   X,
   O,
   Empty
};

class Player {
   string name;
   string id;
   Piece piece;
public:
   Player(string name, string id, Piece piece): name(name), id(id), piece(piece){}
   string getName() { return name; }
   Piece getPiece() { return piece; }
};

class Move {
public:
   int row, column;
   Move(int i, int j): row(i), column(j) {}
};

class Board {
   int size;
   vector<vector<Piece>> grid;
   int movesCount; 
public:
   Board(int n=3): size(n), movesCount(0) {
      grid.assign(size, vector<Piece>(size, Piece::Empty));
   }

   bool isValidMove(Move m){
      int r= m.row;
      int c= m.column;

      if(r<0||r>=size||c<0||c>=size)
         return false;
      return grid[r][c] == Piece::Empty;
   }

   void makeMove(Move &m, Piece piece){
      if (isValidMove(m)){
         grid[m.row][m.column] = piece;
         movesCount++;
      }
      else{
         cout<<"Invalid move, retry\n";
      }
   }

   bool isFull(){
      return movesCount == size*size;
   }

   void printBoard(){
      for(int i=0; i<size; i++){
         for(int j=0; j<size; j++){
            if(grid[i][j] == Piece::X)
               cout<<"X ";
            else if (grid[i][j]== Piece::O)
               cout<<"O ";
            else
               cout<<". ";
         }
         cout<<"\n";
      }
   }
   
   bool checkWinner(Piece piece) {
      for(int i=0; i<size; i++){
         bool rowWin = true, colWin = true;
         for(int j=0; j<size; j++){
            if(grid[i][j] != piece)
               rowWin = false;
            if(grid[j][i] != piece)
               colWin = false;
         }
         if(rowWin || colWin)
            return true;
      }

      bool diag1= true, diag2= true;
      for(int i=0; i<size; i++){
          for(int j=0; j<size; j++){
              if(grid[i][i]!= piece)
                diag1 = false;
             if(grid[i][size-j-1]!= piece)
                diag2 = false;
          }
      }
      return diag1 || diag2;
   }

};

class Game {
   Board board;
   vector<Player> players;
   int currentPlayerIndex;
public:
   Game(Player p1, Player p2): board(3), currentPlayerIndex(0){
      players.push_back(p1);
      players.push_back(p2);
   }

   void play(){
      bool gameEnded = false;

      while(!gameEnded){
         Player& curr = players[currentPlayerIndex];
         board.printBoard();

         cout<< curr.getName()<<" ("<< (curr.getPiece() == Piece::X ? "X":"O") << "), enter row and col (0-2):\n";

         int r, c;
         cin>>r>>c;

         Move move(r, c);

         if(!board.isValidMove(move)){
            cout<< "Invalid move, try again\n";
            continue;
         }

         board.makeMove(move, curr.getPiece());

         if(board.checkWinner(curr.getPiece())){
            board.printBoard();
            cout<<curr.getName()<<" wins\n";
            gameEnded = true;
         }
         else if(board.isFull()){
            board.printBoard();
            cout<<"Its a draw\n";
            gameEnded = true;
         }
         else{
            currentPlayerIndex = (currentPlayerIndex+1) % players.size();
         }
      }
   }
};


int main(){
   Player p1("A", "1", Piece::X);
   Player p2("B", "2", Piece::O);

   Game game(p1, p2);
   game.play();

   return 0;
}


// Sample output:

// . . . 
// . . . 
// . . . 
// A (X), enter row and col (0-2):
// 0 0
// X . . 
// . . . 
// . . . 
// B (O), enter row and col (0-2):
// 1 1 
// X . . 
// . O . 
// . . . 
// A (X), enter row and col (0-2):
// 3 3 
// Invalid move, try again
// X . . 
// . O . 
// . . . 
// A (X), enter row and col (0-2):
// 2 2 
// X . . 
// . O . 
// . . X 
// B (O), enter row and col (0-2):
// 0 2
// X . O 
// . O . 
// . . X 
// A (X), enter row and col (0-2):
// 3 0
// Invalid move, try again
// X . O 
// . O . 
// . . X 
// A (X), enter row and col (0-2):
// 2 0
// X . O 
// . O . 
// X . X 
// B (O), enter row and col (0-2):
// 1 0
// X . O 
// O O . 
// X . X 
// A (X), enter row and col (0-2):
// 2 1
// X . O 
// O O . 
// X X X 
// A wins