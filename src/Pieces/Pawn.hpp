#ifndef PAWN_HPP
#define PAWN_HPP

#include "Piece.hpp"
#include "../Utils/Constants.hpp"
#include <memory>
#include <cstdlib>

/**
 * Classe représentant un pion
 * Hérite de Piece et implémente les règles spécifiques du pion
 */
class Pawn : public Piece {
public:
    /**
     * Constructeur
     */
    Pawn(const Position& position, Color color) 
        : Piece(position, color, PieceType::PAWN) {}
    
    /**
     * Implémente les règles de mouvement du pion
     */
    bool canMoveTo(const Position& target) const override {
        if (position_ == target) {
            return false;
        }
        
        int deltaX = target.getX() - position_.getX();
        int deltaY = target.getY() - position_.getY();
        
        // Direction du mouvement selon la couleur
        int direction = (color_ == Color::WHITE) ? 1 : -1;
        
        // Mouvement diagonal d'une case (pour capture)
        if (abs(deltaX) == 1 && deltaY == direction) {
            return true; // Capture diagonale autorisée
        }
        
        // Mouvement vertical uniquement (pas de capture)
        if (deltaX == 0) {
            // Mouvement d'une case vers l'avant
            if (deltaY == direction) {
                return true;
            }
            
            // Mouvement de deux cases depuis la position initiale
            if (!hasMoved_ && deltaY == 2 * direction) {
                int initialRow = (color_ == Color::WHITE) ? 1 : 6;
                return position_.getY() == initialRow;
            }
        }
        
        return false;
    }
    
    /**
     * Retourne la valeur du pion
     */
    int getValue() const override {
        return ChessConstants::PieceValues::PAWN;
    }
    
    /**
     * Clone le pion
     */
    std::unique_ptr<Piece> clone() const override {
        return std::make_unique<Pawn>(position_, color_);
    }
    
    /**
     * Vérifie si le pion peut capturer en diagonale (capture normale)
     */
    bool canCapture(const Position& target) const {
        int deltaX = abs(target.getX() - position_.getX());
        int deltaY = target.getY() - position_.getY();
        int direction = (color_ == Color::WHITE) ? 1 : -1;
        
        return deltaX == 1 && deltaY == direction;
    }
    
    /**
     * Vérifie si le pion peut effectuer une capture en passant
     */
    bool canCaptureEnPassant(const Position& target, const Position& enPassantTarget) const {
        // Vérification du mouvement diagonal d'une case
        if (!canCapture(target)) {
            return false;
        }
        
        // La position de la pièce capturée doit être sur la même rangée que le pion
        int direction = (color_ == Color::WHITE) ? 1 : -1;
        Position expectedEnemyPos(target.getX(), position_.getY());
        
        return expectedEnemyPos == enPassantTarget;
    }
    
    /**
     * Vérifie si ce pion vient de faire un mouvement de deux cases (pour l'en passant adverse)
     */
    bool justMovedTwoSquares(const Position& previousPosition) const {
        if (!hasMoved_) {
            return false;
        }
        
        int deltaY = abs(position_.getY() - previousPosition.getY());
        int deltaX = position_.getX() - previousPosition.getX();
        
        // Mouvement vertical de 2 cases exactement
        return deltaX == 0 && deltaY == 2;
    }
};

#endif // PAWN_HPP