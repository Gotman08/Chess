#ifndef MOVE_HPP
#define MOVE_HPP

#include "Position.hpp"

/**
 * Classe représentant un mouvement sur l'échiquier
 * Encapsule la position de départ et d'arrivée
 */
class Move {
private:
    Position from_;
    Position to_;
    
public:
    /**
     * Constructeur
     */
    Move(const Position& from, const Position& to) : from_(from), to_(to) {}
    
    // Getters
    const Position& getFrom() const { return from_; }
    const Position& getTo() const { return to_; }
    
    /**
     * Vérifie si le mouvement est valide (positions différentes)
     */
    bool isValid() const {
        return from_ != to_ && from_.isValid() && to_.isValid();
    }
    
    /**
     * Calcule le déplacement en X
     */
    int getDeltaX() const {
        return to_.getX() - from_.getX();
    }
    
    /**
     * Calcule le déplacement en Y
     */
    int getDeltaY() const {
        return to_.getY() - from_.getY();
    }
    
    /**
     * Vérifie si le mouvement est diagonal
     */
    bool isDiagonal() const {
        return abs(getDeltaX()) == abs(getDeltaY()) && getDeltaX() != 0;
    }
    
    /**
     * Vérifie si le mouvement est horizontal
     */
    bool isHorizontal() const {
        return getDeltaY() == 0 && getDeltaX() != 0;
    }
    
    /**
     * Vérifie si le mouvement est vertical
     */
    bool isVertical() const {
        return getDeltaX() == 0 && getDeltaY() != 0;
    }
};

#endif // MOVE_HPP