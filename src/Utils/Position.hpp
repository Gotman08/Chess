#ifndef POSITION_HPP
#define POSITION_HPP

#include "Constants.hpp"
#include <stdexcept>

/**
 * Classe représentant une position sur l'échiquier
 * Encapsule les coordonnées et fournit une validation
 */
class Position {
private:
    int x_;
    int y_;
    
    void validateCoordinates(int x, int y) const {
        if (x < ChessConstants::MIN_COORDINATE || x > ChessConstants::MAX_COORDINATE ||
            y < ChessConstants::MIN_COORDINATE || y > ChessConstants::MAX_COORDINATE) {
            throw std::invalid_argument("Coordonnées invalides");
        }
    }

public:
    /**
     * Constructeur avec validation des coordonnées
     */
    Position(int x, int y) : x_(x), y_(y) {
        validateCoordinates(x, y);
    }
    
    // Getters
    int getX() const { return x_; }
    int getY() const { return y_; }
    
    // Setters avec validation
    void setX(int x) {
        validateCoordinates(x, y_);
        x_ = x;
    }
    
    void setY(int y) {
        validateCoordinates(x_, y);
        y_ = y;
    }
    
    void setPosition(int x, int y) {
        validateCoordinates(x, y);
        x_ = x;
        y_ = y;
    }
    
    // Opérateurs de comparaison
    bool operator==(const Position& other) const {
        return x_ == other.x_ && y_ == other.y_;
    }
    
    bool operator!=(const Position& other) const {
        return !(*this == other);
    }
    
    /**
     * Vérifie si la position est valide sur l'échiquier
     */
    bool isValid() const {
        return x_ >= ChessConstants::MIN_COORDINATE && x_ <= ChessConstants::MAX_COORDINATE &&
               y_ >= ChessConstants::MIN_COORDINATE && y_ <= ChessConstants::MAX_COORDINATE;
    }
    
    /**
     * Calcule la distance entre deux positions
     */
    int manhattanDistance(const Position& other) const {
        return abs(x_ - other.x_) + abs(y_ - other.y_);
    }
};

#endif // POSITION_HPP