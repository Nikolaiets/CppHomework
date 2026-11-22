#include <array>
#include <iostream>
#include <limits>
#include <string>

class TicTacToe {
public:
    enum class CellState {
        Empty = ' ',
        X = 'X',
        O = 'O'
    };

    enum class GameResult {
        InProgress,
        XWins,
        OWins,
        Draw,
        Quit
    };

    TicTacToe() {
        reset();
    }

    void reset() {
        for (auto& row : board_) {
            row.fill(CellState::Empty);
        }
        current_player_ = CellState::X;
        quit_requested_ = false;
    }

    void drawInitialBoard() const {
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                const char cell_num = static_cast<char>('1' + r * 3 + c);
                std::cout << cell_num;
                if (c < 2) {
                    std::cout << '|';
                }
            }
            std::cout << '\n';
        }
    }

    void drawBoard() const {
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                if (board_[r][c] == CellState::Empty) {
                    std::cout << static_cast<char>('1' + r * 3 + c);
                } else {
                    std::cout << static_cast<char>(board_[r][c]);
                }
                if (c < 2) {
                    std::cout << '|';
                }
            }
            std::cout << '\n';
        }
    }

    bool inputMove() {
        const char player_char = static_cast<char>(current_player_);

        while (true) {
            std::cout << "\nPlayer " << player_char
                      << ", enter cell (1-9) or 'q' to quit: ";

            std::string token;
            if (!(std::cin >> token)) {
                if (std::cin.eof()) {
                    quit_requested_ = true;
                    return false;
                }
                clearInputLine();
                std::cout << "Invalid input. Please enter a number from 1 to 9 or 'q'.\n";
                continue;
            }

            clearInputLine();

            if (token.size() == 1 && (token[0] == 'q' || token[0] == 'Q')) {
                quit_requested_ = true;
                return false;
            }

            if (token.size() != 1 || token[0] < '1' || token[0] > '9') {
                std::cout << "Invalid move! Choose a cell number between 1 and 9.\n";
                continue;
            }

            const int pos = token[0] - '0';
            const int row = (pos - 1) / 3;
            const int col = (pos - 1) % 3;

            if (board_[row][col] != CellState::Empty) {
                std::cout << "Cell " << pos << " is already occupied! Pick an empty cell.\n";
                continue;
            }

            board_[row][col] = current_player_;
            return true;
        }
    }

    bool setCell(int row, int col, CellState state) {
        if (row < 0 || row >= 3 || col < 0 || col >= 3) {
            return false;
        }
        board_[row][col] = state;
        return true;
    }

    void switchPlayer() {
        current_player_ = (current_player_ == CellState::X) ? CellState::O : CellState::X;
    }

    CellState getCurrentPlayer() const {
        return current_player_;
    }

    GameResult checkGameResult() const {
        if (quit_requested_) {
            return GameResult::Quit;
        }

        for (int i = 0; i < 3; ++i) {
            if (board_[i][0] != CellState::Empty &&
                board_[i][0] == board_[i][1] &&
                board_[i][1] == board_[i][2]) {
                return (board_[i][0] == CellState::X) ? GameResult::XWins : GameResult::OWins;
            }
            if (board_[0][i] != CellState::Empty &&
                board_[0][i] == board_[1][i] &&
                board_[1][i] == board_[2][i]) {
                return (board_[0][i] == CellState::X) ? GameResult::XWins : GameResult::OWins;
            }
        }

        if (board_[0][0] != CellState::Empty &&
            board_[0][0] == board_[1][1] &&
            board_[1][1] == board_[2][2]) {
            return (board_[0][0] == CellState::X) ? GameResult::XWins : GameResult::OWins;
        }
        if (board_[0][2] != CellState::Empty &&
            board_[0][2] == board_[1][1] &&
            board_[1][1] == board_[2][0]) {
            return (board_[0][2] == CellState::X) ? GameResult::XWins : GameResult::OWins;
        }

        for (const auto& row : board_) {
            for (CellState cell : row) {
                if (cell == CellState::Empty) {
                    return GameResult::InProgress;
                }
            }
        }

        return GameResult::Draw;
    }

    static void printResultMessage(GameResult result) {
        switch (result) {
            case GameResult::XWins:
                std::cout << "\nGame Over: Player X wins!\n";
                break;
            case GameResult::OWins:
                std::cout << "\nGame Over: Player O wins!\n";
                break;
            case GameResult::Draw:
                std::cout << "\nGame Over: It's a draw!\n";
                break;
            case GameResult::Quit:
                std::cout << "\nGame exited by player.\n";
                break;
            case GameResult::InProgress:
                std::cout << "\nGame is still in progress.\n";
                break;
        }
    }

private:
    std::array<std::array<CellState, 3>, 3> board_{};
    CellState current_player_ = CellState::X;
    bool quit_requested_ = false;

    static void clearInputLine() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
};

int main() {
    TicTacToe game;

    std::cout << "=== Initial Board ===\n";
    game.drawInitialBoard();

    TicTacToe::GameResult status = TicTacToe::GameResult::InProgress;

    while (status == TicTacToe::GameResult::InProgress) {
        if (!game.inputMove()) {
            status = game.checkGameResult();
            break;
        }

        game.drawBoard();
        status = game.checkGameResult();

        if (status == TicTacToe::GameResult::InProgress) {
            game.switchPlayer();
        }
    }

    TicTacToe::printResultMessage(status);
    return 0;
}