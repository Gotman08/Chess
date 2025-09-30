#ifndef ROOK_HPP
#define ROOK_HPP

#include "Piece.hpp"
#include "StraightLineMovement.hpp"
#include "../Utils/Constants.hpp"
#include <memory>

/**
 * Classe représentant une tour
 * Hérite de Piece et implémente StraightLineMovement
 */
class Rook : public Piece, public StraightLineMovement {
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
        return canMoveStraight(position_, target);
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