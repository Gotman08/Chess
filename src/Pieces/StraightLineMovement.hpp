#ifndef STRAIGHT_LINE_MOVEMENT_HPP
#define STRAIGHT_LINE_MOVEMENT_HPP

#include "../Utils/Position.hpp"

/**
 * Interface pour les pièces qui se déplacent en ligne droite (horizontal/vertical)
 * Comme la tour et une partie des mouvements de la dame
 */
class StraightLineMovement {
public:
    virtual ~StraightLineMovement() = default;
    
    /**
     * Vérifie si un mouvement en ligne droite est valide
     * @param from Position de départ
     * @param to Position d'arrivée
     * @return true si le mouvement est en ligne droite valide
     */
    static bool isValidStraightLineMove(const Position& from, const Position& to) {
        if (from == to) {
            return false;
        }
        
        int deltaX = to.getX() - from.getX();
        int deltaY = to.getY() - from.getY();
        
        // Mouvement en ligne droite : soit horizontal soit vertical
        return (deltaX == 0 && deltaY != 0) || (deltaX != 0 && deltaY == 0);
    }
    
protected:
    /**
     * Implémentation du mouvement en ligne droite pour les classes dérivées
     */
    bool canMoveStraight(const Position& from, const Position& to) const {
        return isValidStraightLineMove(from, to);
    }
};

#endif // STRAIGHT_LINE_MOVEMENT_HPP