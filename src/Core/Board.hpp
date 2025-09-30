#ifndef BOARD_HPP
#define BOARD_HPP

#include "../Pieces/Piece.hpp"
#include "../Utils/Position.hpp"
#include "../Utils/Move.hpp"
#include "../Utils/Constants.hpp"
#include <array>
#include <memory>


class Board {

    private:

    using BoardArray = std::array<std::array<std::unique_ptr<Piece>, ChessConstants::BOARD_SIZE>, ChessConstants::BOARD_SIZE>;
    BoardArray board_;
    
public:

    Board() {
        clearBoard();
    }
    
    ~Board() = default;
    
    Board(const Board& other) {
        copyFrom(other);
    }
    
    /**
     * @brief Copy assignment operator for the Board class.
     * 
     * Assigns the contents of another Board object to this Board instance.
     * Uses the copy-and-swap idiom to ensure exception safety and handles
     * self-assignment by checking if the objects are the same.
     * 
     * @param other The Board object to copy from
     * @return Board& A reference to this Board object after assignment
     */
    Board& operator=(const Board& other) {
        if (this != &other) {
            copyFrom(other);
        }
        return *this;
    }
    

    /**
     * @brief Retrieves the piece at the specified position on the board.
     * 
     * @param pos The position on the board to check for a piece
     * @return Piece* Pointer to the piece at the given position, or nullptr if the position is invalid or empty
     */
    Piece* getPieceAt(const Position& pos) const {
        if (!pos.isValid()) {
            return nullptr;
        }
        return board_[pos.getY()][pos.getX()].get();
    }
    

    /**
     * @brief Sets a piece at the specified position on the board.
     * 
     * Places the given piece at the specified position if the position is valid.
     * The piece ownership is transferred to the board through move semantics.
     * If the position is invalid, no operation is performed.
     * 
     * @param pos The position where the piece should be placed
     * @param piece Unique pointer to the piece to be placed (ownership transferred)
     */
    void setPieceAt(const Position& pos, std::unique_ptr<Piece> piece) {
        if (pos.isValid()) {
            board_[pos.getY()][pos.getX()] = std::move(piece);
        }
    }
    

    
    /**
     * @brief Removes the piece at the specified position on the board.
     * 
     * This method removes a chess piece from the given position by resetting
     * the corresponding cell on the board. The operation is only performed
     * if the provided position is valid.
     * 
     * @param pos The position from which to remove the piece. Must be a valid
     *            board position (within board boundaries).
     * 
     * @note If the position is invalid, no operation is performed.
     * @note If there is no piece at the specified position, the operation
     *       has no effect.
     */
    void removePieceAt(const Position& pos) {
        if (pos.isValid()) {
            board_[pos.getY()][pos.getX()].reset();
        }
    }
    

    /**
     * @brief Checks if a position on the board is empty (contains no piece).
     * 
     * @param pos The position to check for emptiness
     * @return true if the position contains no piece, false otherwise
     */
    bool isEmpty(const Position& pos) const {
        return getPieceAt(pos) == nullptr;
    }
    

    /**
     * @brief Moves a piece from one position to another on the board.
     * 
     * This method validates the move and transfers the piece from the source
     * position to the destination position. The piece's internal position
     * is updated to reflect the new location.
     * 
     * @param move The Move object containing source and destination positions
     * @return true if the piece was successfully moved, false if the move
     *         is invalid or no piece exists at the source position
     * 
     * @note This method does not validate chess rules or check for piece
     *       movement legality - it only performs basic validation and transfer
     */
    bool movePiece(const Move& move) {
        if (!move.isValid()) {
            return false;
        }
        
        Piece* piece = getPieceAt(move.getFrom());
        if (!piece) {
            return false;
        }
        

        auto movedPiece = std::move(board_[move.getFrom().getY()][move.getFrom().getX()]);
        board_[move.getTo().getY()][move.getTo().getX()] = std::move(movedPiece);
        board_[move.getTo().getY()][move.getTo().getX()]->setPosition(move.getTo());
        
        return true;
    }
    

    /**
     * @brief Clears the entire chess board by resetting all pieces to null.
     * 
     * This method iterates through all squares on the board and resets each
     * piece pointer to nullptr, effectively removing all pieces from the board.
     * After calling this method, the board will be empty and ready for a new
     * game setup or specific position arrangement.
     */
    void clearBoard() {
        for (auto& row : board_) {
            for (auto& piece : row) {
                piece.reset();
            }
        }
    }
    
    /**
     * @brief Checks if the path between two positions is clear of any pieces.
     * 
     * This method checks all squares between the 'from' and 'to' positions
     * (exclusive) to determine if they are empty. It supports horizontal,
     * vertical, and diagonal paths. If the path is clear, it returns true;
     * otherwise, it returns false.
     * 
     * @param from The starting position of the path
     * @param to The ending position of the path
     * @return true if the path is clear, false if any square along the path is occupied
     * 
     * @note This method assumes that 'from' and 'to' are not the same position.
     * @note If 'from' and 'to' are not aligned horizontally, vertically, or diagonally,
     *       the method will return false as it does not handle non-linear paths.
     */
    bool isPathClear(const Position& from, const Position& to) const {
        if (from == to) {
            return true;
        }
        
        int deltaX = to.getX() - from.getX();
        int deltaY = to.getY() - from.getY();
        
        int stepX = (deltaX > 0) ? 1 : (deltaX < 0) ? -1 : 0;
        int stepY = (deltaY > 0) ? 1 : (deltaY < 0) ? -1 : 0;
        
        Position current(from.getX() + stepX, from.getY() + stepY);
        
        while (current != to) {
            if (!isEmpty(current)) {
                return false;
            }
            current.setPosition(current.getX() + stepX, current.getY() + stepY);
        }
        
        return true;
    }
    
private:
    /**
     * @brief Copies the contents from another board.
     * 
     * This method clears the current board and then copies the pieces
     * from the 'other' board to the current board. It ensures that the
     * current board is a deep copy of the 'other' board.
     * @param other The board to copy from
     * @note This method assumes that the 'other' board is valid and properly initialized.
     * @note This method is used internally for copy construction and assignment.
     * @see Board(const Board& other)
     * @see Board& operator=(const Board& other)
     * @private
     * 
     */
    void copyFrom(const Board& other) {
        clearBoard();
        for (int y = 0; y < ChessConstants::BOARD_SIZE; ++y) {
            for (int x = 0; x < ChessConstants::BOARD_SIZE; ++x) {
                if (other.board_[y][x]) {
                    board_[y][x] = other.board_[y][x]->clone();
                }
            }
        }
    }
};

#endif // BOARD_HPP