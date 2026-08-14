// Exercise 5 task 2. Print the board as text after every move.
// Builds on task 1. New is short_type() on Piece, print() on ChessBoard, and
// a print() call at the end of a successful move.

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class ChessBoard {
public:
  enum class Color { WHITE,
                     BLACK };

  class Piece {
  public:
    Piece(Color color) : color(color) {}
    virtual ~Piece() {}

    Color color;
    std::string color_string() const {
      if (color == Color::WHITE)
        return "white";
      else
        return "black";
    }

    virtual std::string type() const = 0;

    /// One character for the board print.
    virtual char short_type() const = 0;

    virtual bool valid_move(int from_x, int from_y, int to_x, int to_y) const = 0;

  protected:
    static bool on_board(int x, int y) {
      return x >= 0 && x < 8 && y >= 0 && y < 8;
    }

    /// Upper case for white, lower case for black, as in normal notation.
    char colored(char letter) const {
      if (color == Color::WHITE)
        return letter;
      return static_cast<char>(letter - 'A' + 'a');
    }
  };

  class King : public Piece {
  public:
    King(Color color) : Piece(color) {}

    std::string type() const override {
      return color_string() + " king";
    }

    char short_type() const override {
      return colored('K');
    }

    bool valid_move(int from_x, int from_y, int to_x, int to_y) const override {
      if (!on_board(to_x, to_y))
        return false;
      const int dx = abs(to_x - from_x);
      const int dy = abs(to_y - from_y);
      return dx <= 1 && dy <= 1 && (dx + dy) > 0;
    }
  };

  class Knight : public Piece {
  public:
    Knight(Color color) : Piece(color) {}

    std::string type() const override {
      return color_string() + " knight";
    }

    char short_type() const override {
      return colored('N'); // N, since K is taken by the king
    }

    bool valid_move(int from_x, int from_y, int to_x, int to_y) const override {
      if (!on_board(to_x, to_y))
        return false;
      const int dx = abs(to_x - from_x);
      const int dy = abs(to_y - from_y);
      return (dx == 1 && dy == 2) || (dx == 2 && dy == 1);
    }
  };

  ChessBoard() {
    squares.resize(8);
    for (auto &square_column : squares)
      square_column.resize(8);
  }

  vector<vector<unique_ptr<Piece>>> squares;

  /// Row 8 on top, the way a board is normally shown.
  void print() const {
    for (int y = 7; y >= 0; y--) {
      cout << (y + 1) << " ";
      for (int x = 0; x < 8; x++) {
        const auto &piece = squares[x][y];
        if (piece)
          cout << piece->short_type() << " ";
        else
          cout << ". ";
      }
      cout << endl;
    }
    cout << "  a b c d e f g h" << endl
         << endl;
  }

  bool move_piece(const std::string &from, const std::string &to) {
    int from_x = from[0] - 'a';
    int from_y = stoi(string() + from[1]) - 1;
    int to_x = to[0] - 'a';
    int to_y = stoi(string() + to[1]) - 1;

    auto &piece_from = squares[from_x][from_y];
    if (piece_from) {
      if (piece_from->valid_move(from_x, from_y, to_x, to_y)) {
        cout << piece_from->type() << " is moving from " << from << " to " << to << endl;
        auto &piece_to = squares[to_x][to_y];
        if (piece_to) {
          if (piece_from->color != piece_to->color) {
            cout << piece_to->type() << " is being removed from " << to << endl;
            if (auto king = dynamic_cast<King *>(piece_to.get()))
              cout << king->color_string() << " lost the game" << endl;
          } else {
            cout << "can not move " << piece_from->type() << " from " << from << " to " << to << endl;
            return false;
          }
        }
        piece_to = std::move(piece_from);
        print();
        return true;
      } else {
        cout << "can not move " << piece_from->type() << " from " << from << " to " << to << endl;
        return false;
      }
    } else {
      cout << "no piece at " << from << endl;
      return false;
    }
  }
};

int main() {
  ChessBoard board;

  board.squares[4][0] = make_unique<ChessBoard::King>(ChessBoard::Color::WHITE);
  board.squares[1][0] = make_unique<ChessBoard::Knight>(ChessBoard::Color::WHITE);
  board.squares[6][0] = make_unique<ChessBoard::Knight>(ChessBoard::Color::WHITE);

  board.squares[4][7] = make_unique<ChessBoard::King>(ChessBoard::Color::BLACK);
  board.squares[1][7] = make_unique<ChessBoard::Knight>(ChessBoard::Color::BLACK);
  board.squares[6][7] = make_unique<ChessBoard::Knight>(ChessBoard::Color::BLACK);

  cout << "Start position:" << endl;
  board.print();

  board.move_piece("e1", "e2");
  board.move_piece("g8", "h6");
  board.move_piece("b1", "c3");
  board.move_piece("h6", "g8");
  board.move_piece("c3", "d5");
  board.move_piece("g8", "h6");
  board.move_piece("d5", "f6");
  board.move_piece("h6", "g8");
  board.move_piece("f6", "e8");
}
