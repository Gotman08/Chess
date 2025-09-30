#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "Piece.hpp"
#include "../Utils/Constants.hpp"
#include <memory>


class Knight : public Piece {
    public:

    Knight(const Position& position, Color color) 
        : Piece(position, color, PieceType::KNIGHT) {}
    

    /**
     * @brief Determines if the knight can move to the specified target position.
     * 
     * A knight moves in an L-shape: either 2 squares horizontally and 1 square vertically,
     * or 1 square horizontally and 2 squares vertically. This method validates that the
     * target position follows this movement pattern.
     * 
     * @param target The target position to move to
     * @return true if the knight can legally move to the target position, false otherwise
     * @note Returns false if the target position is the same as the current position
     */
    bool canMoveTo(const Position& target) const override {
        if (position_ == target) {
            return false;
        }
        
        int deltaX = abs(target.getX() - position_.getX());
        int deltaY = abs(target.getY() - position_.getY());
        
        return (deltaX == 2 && deltaY == 1) || (deltaX == 1 && deltaY == 2);
    }
    

    /**
     * @brief Gets the material value of the knight piece.
     * 
     * @return The standard chess point value for a knight piece as defined in ChessConstants.
     */
    int getValue() const override {
        return ChessConstants::PieceValues::KNIGHT;
    }
    
    /**
     * @brief Creates a deep copy of the Knight piece.
     * 
     * This method implements the clone pattern to create an exact copy of the current
     * Knight instance, preserving its position and color properties.
     * 
     * @return std::unique_ptr<Piece> A unique pointer to a new Knight object that is
     *         an exact copy of this instance.
     * 
     * @note This method overrides the pure virtual clone method from the base Piece class.
     */
    std::unique_ptr<Piece> clone() const override {
        return std::make_unique<Knight>(position_, color_);
    }
};

#endif // KNIGHT_HPP