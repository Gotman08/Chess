#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "Piece.hpp"
#include "DiagonalMovement.hpp"
#include "../Utils/Constants.hpp"
#include <memory>


class Bishop : public Piece, public DiagonalMovement {
public:

    Bishop(const Position& position, Color color) 
        : Piece(position, color, PieceType::BISHOP) {}
    

    /**
     * @brief Determines if the bishop can move to the specified target position.
     * 
     * A bishop can only move diagonally on the chess board. This method checks
     * if the target position is reachable by moving diagonally from the current
     * position.
     * 
     * @param target The position to check if the bishop can move to
     * @return true if the bishop can move to the target position, false otherwise
     */
    bool canMoveTo(const Position& target) const override {
        return canMoveDiagonally(position_, target);
    }
    

    /**
     * @brief Gets the point value of the bishop piece.
     * 
     * Returns the standard chess point value for a bishop piece as defined
     * in the ChessConstants. This value is typically used for position
     * evaluation and material counting in chess engines.
     * 
     * @return The integer point value of the bishop piece
     * @override Overrides the base Piece class getValue method
     */
    int getValue() const override {
        return ChessConstants::PieceValues::BISHOP;
    }
    

    /**
     * @brief Creates a deep copy of the Bishop piece.
     * 
     * This method creates a new Bishop instance with the same position and color
     * as the current Bishop object. Used for implementing the prototype pattern
     * and creating independent copies of the piece.
     * 
     * @return std::unique_ptr<Piece> A unique pointer to a new Bishop instance
     *         that is a copy of this Bishop
     */
    std::unique_ptr<Piece> clone() const override {
        return std::make_unique<Bishop>(position_, color_);
    }
};

#endif // BISHOP_HPP