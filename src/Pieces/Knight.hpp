#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "Piece.hpp"
#include "../Utils/Constants.hpp"
#include <memory>

/**
 * Classe représentant un cavalier
 * Hérite de Piece et implémente les règles spécifiques du cavalier
 */
class Knight : public Piece {
public:
    /**
     * Constructeur
     */
    Knight(const Position& position, Color color) 
        : Piece(position, color, PieceType::KNIGHT) {}
    
    /**
     * Implémente les règles de mouvement du cavalier
     */
    bool canMoveTo(const Position& target) const override {
        if (position_ == target) {
            return false;
        }
        
        int deltaX = abs(target.getX() - position_.getX());
        int deltaY = abs(target.getY() - position_.getY());
        
        // Le cavalier se déplace en L : 2 cases dans une direction, 1 dans l'autre
        return (deltaX == 2 && deltaY == 1) || (deltaX == 1 && deltaY == 2);
    }
    
    /**
     * Retourne la valeur du cavalier
     */
    int getValue() const override {
        return ChessConstants::PieceValues::KNIGHT;
    }
    
    /**
     * Clone le cavalier
     */
    std::unique_ptr<Piece> clone() const override {
        return std::make_unique<Knight>(position_, color_);
    }
};

#endif // KNIGHT_HPP