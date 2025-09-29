#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../Enums/Color.hpp"
#include "../Pieces/Piece.hpp"
#include <vector>
#include <memory>

/**
 * Classe représentant un joueur
 * Respecte le Single Responsibility Principle - ne gère que les informations du joueur
 */
class Player {
private:
    Color color_;
    std::vector<std::unique_ptr<Piece>> capturedPieces_;
    
public:
    /**
     * Constructeur
     */
    explicit Player(Color color) : color_(color) {}
    
    /**
     * Destructeur - les smart pointers gèrent automatiquement la mémoire
     */
    ~Player() = default;
    
    // Supprime le constructeur de copie et l'opérateur d'assignation
    // pour éviter les problèmes de propriété des pièces
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
    
    // Getters
    Color getColor() const { return color_; }
    
    /**
     * Ajoute une pièce capturée
     */
    void addCapturedPiece(std::unique_ptr<Piece> piece) {
        capturedPieces_.push_back(std::move(piece));
    }
    
    /**
     * Calcule le score basé sur les pièces capturées
     */
    int getScore() const {
        int score = 0;
        for (const auto& piece : capturedPieces_) {
            score += piece->getValue();
        }
        return score;
    }
    
    /**
     * Retourne le nombre de pièces capturées
     */
    size_t getCapturedPiecesCount() const {
        return capturedPieces_.size();
    }
    
    /**
     * Vide la liste des pièces capturées
     */
    void clearCapturedPieces() {
        capturedPieces_.clear();
    }
    
    /**
     * Méthodes utilitaires pour les couleurs
     */
    bool isWhite() const { return color_ == Color::WHITE; }
    bool isBlack() const { return color_ == Color::BLACK; }
};

#endif // PLAYER_HPP