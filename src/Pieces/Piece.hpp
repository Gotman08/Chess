#ifndef PIECE_HPP
#define PIECE_HPP

#include "../Enums/Color.hpp"
#include "../Enums/PieceType.hpp"
#include "../Utils/Position.hpp"
#include "../Utils/Move.hpp"
#include <memory>

/**
 * Classe abstraite représentant une pièce d'échecs
 * Respecte le principe d'encapsulation et fournit une interface commune
 */
class Piece {
protected:
    Position position_;
    Color color_;
    PieceType type_;
    bool hasMoved_; // Pour les règles spéciales (roque, en passant, etc.)

public:
    /**
     * Constructeur
     */
    Piece(const Position& position, Color color, PieceType type) 
        : position_(position), color_(color), type_(type), hasMoved_(false) {}
    
    /**
     * Destructeur virtuel pour le polymorphisme
     */
    virtual ~Piece() = default;
    
    // Getters
    const Position& getPosition() const { return position_; }
    Color getColor() const { return color_; }
    PieceType getType() const { return type_; }
    bool hasMovedBefore() const { return hasMoved_; }
    
    /**
     * Met à jour la position de la pièce
     */
    virtual void setPosition(const Position& newPosition) {
        position_ = newPosition;
        hasMoved_ = true;
    }
    
    /**
     * Vérifie si la pièce peut se déplacer vers une position donnée
     * Méthode virtuelle pure - doit être implémentée par chaque pièce
     */
    virtual bool canMoveTo(const Position& target) const = 0;
    
    /**
     * Retourne la valeur de la pièce pour le calcul du score
     */
    virtual int getValue() const = 0;
    
    /**
     * Méthodes utilitaires pour les couleurs
     */
    bool isWhite() const { return color_ == Color::WHITE; }
    bool isBlack() const { return color_ == Color::BLACK; }
    
    /**
     * Vérifie si cette pièce est de la même couleur qu'une autre
     */
    bool isSameColor(const Piece& other) const {
        return color_ == other.color_;
    }
    
    /**
     * Clone la pièce (pattern Prototype pour la copie)
     */
    virtual std::unique_ptr<Piece> clone() const = 0;
};

#endif // PIECE_HPP