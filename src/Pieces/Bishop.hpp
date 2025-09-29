#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "Piece.hpp"
#include "../Utils/Constants.hpp"
#include <memory>

/**
 * Classe représentant un fou
 * Hérite de Piece et implémente les règles spécifiques du fou
 */
class Bishop : public Piece {
public:
    /**
     * Constructeur
     */
    Bishop(const Position& position, Color color) 
        : Piece(position, color, PieceType::BISHOP) {}
    
    /**
     * Implémente les règles de mouvement du fou
     */
    bool canMoveTo(const Position& target) const override {
        if (position_ == target) {
            return false;
        }
        
        int deltaX = abs(target.getX() - position_.getX());
        int deltaY = abs(target.getY() - position_.getY());
        
        // Le fou se déplace uniquement en diagonale
        return deltaX == deltaY && deltaX > 0;
    }
    
    /**
     * Retourne la valeur du fou
     */
    int getValue() const override {
        return ChessConstants::PieceValues::BISHOP;
    }
    
    /**
     * Clone le fou
     */
    std::unique_ptr<Piece> clone() const override {
        return std::make_unique<Bishop>(position_, color_);
    }
};

#endif // BISHOP_HPP