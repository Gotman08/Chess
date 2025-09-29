#ifndef ROOK_HPP
#define ROOK_HPP

#include "Piece.hpp"
#include "../Utils/Constants.hpp"
#include <memory>

/**
 * Classe représentant une tour
 * Hérite de Piece et implémente les règles spécifiques de la tour
 */
class Rook : public Piece {
public:
    /**
     * Constructeur
     */
    Rook(const Position& position, Color color) 
        : Piece(position, color, PieceType::ROOK) {}
    
    /**
     * Implémente les règles de mouvement de la tour
     */
    bool canMoveTo(const Position& target) const override {
        if (position_ == target) {
            return false;
        }
        
        int deltaX = target.getX() - position_.getX();
        int deltaY = target.getY() - position_.getY();
        
        // La tour se déplace uniquement horizontalement ou verticalement
        return (deltaX == 0 && deltaY != 0) || (deltaX != 0 && deltaY == 0);
    }
    
    /**
     * Retourne la valeur de la tour
     */
    int getValue() const override {
        return ChessConstants::PieceValues::ROOK;
    }
    
    /**
     * Clone la tour
     */
    std::unique_ptr<Piece> clone() const override {
        return std::make_unique<Rook>(position_, color_);
    }
};

#endif // ROOK_HPP