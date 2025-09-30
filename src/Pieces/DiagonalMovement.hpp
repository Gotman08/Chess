#ifndef DIAGONAL_MOVEMENT_HPP
#define DIAGONAL_MOVEMENT_HPP

#include "../Utils/Position.hpp"
#include <cmath>


class DiagonalMovement {
public:
    virtual ~DiagonalMovement() = default;
    
    /**
     * Vérifie si un mouvement diagonal est valide
     * @param from Position de départ
     * @param to Position d'arrivée
     * @return true si le mouvement est diagonal valide
     */
    static bool isValidDiagonalMove(const Position& from, const Position& to) {
        if (from == to) {
            return false;
        }
        
        int deltaX = abs(to.getX() - from.getX());
        int deltaY = abs(to.getY() - from.getY());
        

        return deltaX == deltaY && deltaX > 0;
    }
    
protected:

    /**
     * @brief Checks if a piece can move diagonally from one position to another.
     * 
     * This method validates whether a diagonal movement between two positions is legal
     * for the current piece. It performs the basic diagonal movement validation by
     * delegating to the internal validation logic.
     * 
     * @param from The starting position of the piece
     * @param to The target position for the move
     * @return true if the diagonal move is valid, false otherwise
     */
    bool canMoveDiagonally(const Position& from, const Position& to) const {
        return isValidDiagonalMove(from, to);
    }
};

#endif // DIAGONAL_MOVEMENT_HPP