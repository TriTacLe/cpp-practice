// Øving 6, oppgave 1: skill utskrift ut av ChessBoard.
//
// Etter øving 5 sto alle cout-kallene inne i move_piece(). Det gjør at
// klassen både styrer spillet og bestemmer hvordan det ser ut. Her flyttes
// all utskrift til ChessBoardPrint.
//
// Mekanikken: ChessBoard eier en håndfull std::function-medlemmer og kaller
// dem når noe skjer. Den vet ikke hva som skjer i dem. ChessBoardPrint fyller
// dem med lambdaer i konstruktøren sin. Vil du logge til fil i stedet, lager
// du en ChessBoardLog og rører ikke ChessBoard.
//
// after_piece_move er det egne funksjonsobjektet oppgaven ber om. Det kjøres
// etter at et trekk er utført, og ChessBoardPrint bruker det til å tegne
// brettet på nytt.

#include <cstdlib>
#include <functional>
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
      return "black";
    }

    virtual std::string type() const = 0;
    virtual char short_type() const = 0;
    virtual bool valid_move(int from_x, int from_y, int to_x, int to_y) const = 0;

  protected:
    static bool on_board(int x, int y) {
      return x >= 0 && x < 8 && y >= 0 && y < 8;
    }

    char colored(char letter) const {
      if (color == Color::WHITE)
        return letter;
      return static_cast<char>(letter - 'A' + 'a');
    }
  };

  class King : public Piece {
  public:
    King(Color color) : Piece(color) {}

    std::string type() const override { return color_string() + " king"; }
    char short_type() const override { return colored('K'); }

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

    std::string type() const override { return color_string() + " knight"; }
    char short_type() const override { return colored('N'); }

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

  // Funksjonsobjektene. Alle er tomme til noen setter dem, derfor sjekkes de
  // med if før de kalles. En tom std::function kaster hvis du kaller den.
  function<void(const Piece &piece, const string &from, const string &to)> on_piece_moving;
  function<void(const Piece &piece, const string &from, const string &to)> on_invalid_move;
  function<void(const string &from)> on_empty_square;
  function<void(const Piece &piece, const string &to)> on_piece_removed;
  function<void(const Piece &king)> on_king_lost;
  function<void()> after_piece_move;

  bool move_piece(const std::string &from, const std::string &to) {
    int from_x = from[0] - 'a';
    int from_y = stoi(string() + from[1]) - 1;
    int to_x = to[0] - 'a';
    int to_y = stoi(string() + to[1]) - 1;

    auto &piece_from = squares[from_x][from_y];
    if (!piece_from) {
      if (on_empty_square)
        on_empty_square(from);
      return false;
    }

    if (!piece_from->valid_move(from_x, from_y, to_x, to_y)) {
      if (on_invalid_move)
        on_invalid_move(*piece_from, from, to);
      return false;
    }

    if (on_piece_moving)
      on_piece_moving(*piece_from, from, to);

    auto &piece_to = squares[to_x][to_y];
    if (piece_to) {
      if (piece_from->color == piece_to->color) {
        if (on_invalid_move)
          on_invalid_move(*piece_from, from, to);
        return false;
      }
      if (on_piece_removed)
        on_piece_removed(*piece_to, to);
      if (auto king = dynamic_cast<King *>(piece_to.get())) {
        if (on_king_lost)
          on_king_lost(*king);
      }
    }

    piece_to = std::move(piece_from);

    if (after_piece_move)
      after_piece_move();
    return true;
  }
};

/// Tar seg av all utskrift. ChessBoard kjenner ikke denne klassen.
class ChessBoardPrint {
public:
  ChessBoardPrint(ChessBoard &board) : board(board) {
    // Alle lambdaene fanger this, slik at de kan nå print_board() og board.
    board.on_piece_moving = [](const ChessBoard::Piece &piece, const string &from, const string &to) {
      cout << piece.type() << " is moving from " << from << " to " << to << endl;
    };

    board.on_invalid_move = [](const ChessBoard::Piece &piece, const string &from, const string &to) {
      cout << "can not move " << piece.type() << " from " << from << " to " << to << endl;
    };

    board.on_empty_square = [](const string &from) {
      cout << "no piece at " << from << endl;
    };

    board.on_piece_removed = [](const ChessBoard::Piece &piece, const string &to) {
      cout << piece.type() << " is being removed from " << to << endl;
    };

    board.on_king_lost = [](const ChessBoard::Piece &king) {
      cout << king.color_string() << " lost the game" << endl;
    };

    board.after_piece_move = [this]() {
      print_board();
    };
  }

  void print_board() const {
    for (int y = 7; y >= 0; y--) {
      cout << (y + 1) << " ";
      for (int x = 0; x < 8; x++) {
        const auto &piece = board.squares[x][y];
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

private:
  ChessBoard &board;
};

int main() {
  ChessBoard board;
  ChessBoardPrint print(board);

  board.squares[4][0] = make_unique<ChessBoard::King>(ChessBoard::Color::WHITE);
  board.squares[1][0] = make_unique<ChessBoard::Knight>(ChessBoard::Color::WHITE);
  board.squares[6][0] = make_unique<ChessBoard::Knight>(ChessBoard::Color::WHITE);

  board.squares[4][7] = make_unique<ChessBoard::King>(ChessBoard::Color::BLACK);
  board.squares[1][7] = make_unique<ChessBoard::Knight>(ChessBoard::Color::BLACK);
  board.squares[6][7] = make_unique<ChessBoard::Knight>(ChessBoard::Color::BLACK);

  cout << "Startoppstilling:" << endl;
  print.print_board();

  cout << "Invalid moves:" << endl;
  board.move_piece("e3", "e2");
  board.move_piece("e1", "e3");
  board.move_piece("b1", "b2");
  cout << endl;

  cout << "A simulated game:" << endl;
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
