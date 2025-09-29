#ifndef KING_HPP
#define KING_HPP

#include "Piece.hpp"
#include "../Utils/Constants.hpp"
#include <memory>

/**
 * Classe représentant un roi
 * Hérite de Piece et implémente les règles spécifiques du roi
 */
class King : public Piece {
public:
    /**
     * Constructeur
     */
    King(const Position& position, Color color) 
        : Piece(position, color, PieceType::KING) {}
    
    /**
     * Implémente les règles de mouvement du roi
     */
    bool canMoveTo(const Position& target) const override {
        if (position_ == target) {
            return false;
        }
        
        int deltaX = abs(target.getX() - position_.getX());
        int deltaY = abs(target.getY() - position_.getY());
        
        // Le roi se déplace d'une seule case dans toutes les directions
        return deltaX <= 1 && deltaY <= 1;
    }
    
    /**
     * Retourne la valeur du roi
     */
    int getValue() const override {
        return ChessConstants::PieceValues::KING;
    }
    
    /**
     * Clone le roi
     */
    std::unique_ptr<Piece> clone() const override {
        return std::make_unique<King>(position_, color_);
    }
    
    /**
     * Vérifie si le roi peut effectuer un roque
     */
    bool canCastle() const {
        return !hasMoved_;
    }
};

#endif // KING_HPP