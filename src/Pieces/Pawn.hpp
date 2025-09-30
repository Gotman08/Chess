#ifndef PAWN_HPP
#define PAWN_HPP

#include "Piece.hpp"
#include "../Utils/Constants.hpp"
#include <memory>
#include <cstdlib>

class Pawn : public Piece {

    public:

    Pawn(const Position& position, Color color) 
        : Piece(position, color, PieceType::PAWN) {}
    

    /**
     * @brief Determines if the pawn can move to the specified target position.
     * 
     * This method validates pawn movement according to chess rules:
     * - Forward movement: one square forward, or two squares on first move
     * - Diagonal capture: one square diagonally forward (assumed valid if target occupied)
     * - Direction depends on piece color (white moves up, black moves down)
     * 
     * @param target The target position to move to
     * @return true if the move is valid according to pawn movement rules, false otherwise
     * 
     * @note This method only validates movement patterns, not board state (obstacles, captures)
     * @note White pawns move in positive Y direction, black pawns in negative Y direction
     */
    bool canMoveTo(const Position& target) const override {
        if (position_ == target) {
            return false;
        }
        
        int deltaX = target.getX() - position_.getX();
        int deltaY = target.getY() - position_.getY();
        
        int direction = (color_ == Color::WHITE) ? 1 : -1;
        
        
        if (abs(deltaX) == 1 && deltaY == direction) {
            return true;
        }
        
        if (deltaX == 0) {
            if (deltaY == direction) {
                return true;
            }
            
            if (!hasMoved_ && deltaY == 2 * direction) {
                int initialRow = (color_ == Color::WHITE) ? 1 : 6;
                return position_.getY() == initialRow;
            }
        }
        
        return false;
    }
    

    /**
     * @brief Gets the point value of the pawn piece.
     * 
     * Returns the standard chess piece value for a pawn as defined in the
     * ChessConstants::PieceValues enumeration. This value is typically used
     * for chess engine evaluation and scoring purposes.
     * 
     * @return The integer point value of a pawn piece
     * @override This method overrides the base class getValue() method
     */
    int getValue() const override {
        return ChessConstants::PieceValues::PAWN;
    }
    
    /**
     * @brief Creates a deep copy of the Pawn object.
     * 
     * This method implements the Prototype design pattern by creating a new Pawn
     * instance with the same position and color as the current object.
     * 
     * @return std::unique_ptr<Piece> A smart pointer to a newly created Pawn object
     *         that is an exact copy of this instance.
     */
    std::unique_ptr<Piece> clone() const override {
        return std::make_unique<Pawn>(position_, color_);
    }
    

    /**
     * @brief Determines if the pawn can capture a piece at the target position.
     * 
     * A pawn can capture diagonally one square forward in its movement direction.
     * White pawns move upward (positive Y direction) and black pawns move downward
     * (negative Y direction).
     * 
     * @param target The position to check for a potential capture
     * @return true if the pawn can capture at the target position, false otherwise
     */
    bool canCapture(const Position& target) const {
        int deltaX = abs(target.getX() - position_.getX());
        int deltaY = target.getY() - position_.getY();
        int direction = (color_ == Color::WHITE) ? 1 : -1;
        
        return deltaX == 1 && deltaY == direction;
    }
    
    /**
     * @brief Determines if the pawn can perform an en passant capture.
     * 
     * En passant allows a pawn to capture an opponent's pawn that has just moved
     * two squares forward from its starting position, landing beside the capturing
     * pawn. The capturing pawn moves diagonally to the square behind the opponent's
     * pawn, which is then removed from the board.
     * 
     * @param target The position to which the pawn would move to capture en passant
     * @param enPassantTarget The position of the opponent's pawn that can be captured
     * @return true if the en passant capture is valid, false otherwise
     */
    bool canCaptureEnPassant(const Position& target, const Position& enPassantTarget) const {

        if (!canCapture(target)) {
            return false;
        }
        
        int direction = (color_ == Color::WHITE) ? 1 : -1;
        Position expectedEnemyPos(target.getX(), position_.getY());
        
        return expectedEnemyPos == enPassantTarget;
    }
    
    /**
     * @brief Checks if the pawn has just moved two squares forward.
     * 
     * This method is used to determine if the pawn is eligible for en passant
     * capture by an opposing pawn. It checks if the pawn has moved from its
     * initial position to two squares ahead in a single move.
     * 
     * @param previousPosition The position of the pawn before its last move
     * @return true if the pawn has just moved two squares forward, false otherwise
     */
    bool justMovedTwoSquares(const Position& previousPosition) const {
        if (!hasMoved_) {
            return false;
        }
        
        int deltaY = abs(position_.getY() - previousPosition.getY());
        int deltaX = position_.getX() - previousPosition.getX();
        
        return deltaX == 0 && deltaY == 2;
    }
};

#endif // PAWN_HPP