#ifndef KING_HPP
#define KING_HPP

#include "Piece.hpp"
#include "../Utils/Constants.hpp"
#include <memory>

class King : public Piece {

    public:

    King(const Position& position, Color color) 
        : Piece(position, color, PieceType::KING) {}
    

    /**
     * @brief Determines if the king can move to the specified target position.
     * 
     * A king can move one square in any direction: horizontally, vertically, or diagonally.
     * This method checks if the target position is within one square of the king's current position
     * and ensures the king is not attempting to move to its current position.
     * 
     * @param target The position to check if the king can move to
     * @return true if the king can legally move to the target position, false otherwise
     * 
     * @note This method only validates the basic movement rules for a king and does not
     *       check for obstacles, check conditions, or other game state constraints.
     */
    bool canMoveTo(const Position& target) const override {
        if (position_ == target) {
            return false;
        }
        
        int deltaX = abs(target.getX() - position_.getX());
        int deltaY = abs(target.getY() - position_.getY());
        
        return deltaX <= 1 && deltaY <= 1;
    }
    
    /**
     * @brief Gets the value of the King piece.
     * 
     * Returns the numerical value assigned to the King piece as defined in the
     * chess constants. This value is typically used for piece evaluation in
     * chess algorithms and game analysis.
     * 
     * @return The constant value representing the King piece from ChessConstants::PieceValues::KING
     * @override This method overrides the base class getValue() method
     */
    int getValue() const override {
        return ChessConstants::PieceValues::KING;
    }
    

    /**
     * @brief Creates a deep copy of this King piece.
     * 
     * This method implements the clone pattern to create an exact copy of the current
     * King instance with the same position and color properties.
     * 
     * @return std::unique_ptr<Piece> A unique pointer to the newly created King copy
     * @override Implements the pure virtual clone method from the Piece base class
     */
    std::unique_ptr<Piece> clone() const override {
        return std::make_unique<King>(position_, color_);
    }
    
    /**
     * Vérifie si le roi peut effectuer un roque
     * @param board Le plateau de jeu pour vérifier les conditions
     * @param isKingSide True pour le petit roque, false pour le grand roque
     */
    bool canCastle(const Board& board, bool isKingSide) const {
        if (hasMoved_) {
            return false;
        }
        
        if (board.isInCheck(color_)) {
            return false;
        }
        
        int rookX = isKingSide ? 7 : 0;
        auto rook = board.getPieceAt(Position(rookX, position_.getY()));
        if (!rook || rook->getType() != PieceType::ROOK || rook->hasMoved()) {
            return false;
        }
        
        int startX = isKingSide ? position_.getX() + 1 : 1;
        int endX = isKingSide ? 7 : position_.getX();
        
        for (int x = startX; x < endX; ++x) {
            if (board.getPieceAt(Position(x, position_.getY()))) {
                return false;
            }
            
            if (x == position_.getX() + (isKingSide ? 1 : -1) || 
                x == position_.getX() + (isKingSide ? 2 : -2)) {
                if (board.isSquareAttacked(Position(x, position_.getY()), color_)) {
                    return false;
                }
            }
        }
        
        return true;
    }
};

#endif // KING_HPP