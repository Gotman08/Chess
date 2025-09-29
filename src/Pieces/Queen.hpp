#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "Piece.hpp"
#include "../Utils/Constants.hpp"
#include <memory>

/**
 * Classe représentant une dame
 * Hérite de Piece et implémente les règles spécifiques de la dame
 */
class Queen : public Piece {
public:
    /**
     * Constructeur
     */
    Queen(const Position& position, Color color) 
        : Piece(position, color, PieceType::QUEEN) {}
    
    /**
     * Implémente les règles de mouvement de la dame
     */
    bool canMoveTo(const Position& target) const override {
        if (position_ == target) {
            return false;
        }
        
        int deltaX = abs(target.getX() - position_.getX());
        int deltaY = abs(target.getY() - position_.getY());
        
        // La dame combine les mouvements de la tour et du fou
        // Mouvement horizontal/vertical (comme la tour)
        bool isRookMove = (deltaX == 0 && deltaY > 0) || (deltaX > 0 && deltaY == 0);
        
        // Mouvement diagonal (comme le fou)
        bool isBishopMove = (deltaX == deltaY && deltaX > 0);
        
        return isRookMove || isBishopMove;
    }
    
    /**
     * Retourne la valeur de la dame
     */
    int getValue() const override {
        return ChessConstants::PieceValues::QUEEN;
    }
    
    /**
     * Clone la dame
     */
    std::unique_ptr<Piece> clone() const override {
        return std::make_unique<Queen>(position_, color_);
    }
};

#endif // QUEEN_HPP