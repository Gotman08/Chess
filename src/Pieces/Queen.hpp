#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "Piece.hpp"
#include "DiagonalMovement.hpp"
#include "StraightLineMovement.hpp"
#include "../Utils/Constants.hpp"
#include <memory>

/**
 * Classe représentant une dame
 * Hérite de Piece et combine DiagonalMovement et StraightLineMovement
 */
class Queen : public Piece, public DiagonalMovement, public StraightLineMovement {
public:

    Queen(const Position& position, Color color) 
        : Piece(position, color, PieceType::QUEEN) {}
    

    /**
     * Implémente les règles de mouvement de la dame
     * Combine les mouvements diagonal (fou) et en ligne droite (tour)
     */
    bool canMoveTo(const Position& target) const override {
        return canMoveDiagonally(position_, target) || canMoveStraight(position_, target);
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