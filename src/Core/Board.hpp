#ifndef BOARD_HPP
#define BOARD_HPP

#include "../Pieces/Piece.hpp"
#include "../Utils/Position.hpp"
#include "../Utils/Move.hpp"
#include "../Utils/Constants.hpp"
#include <array>
#include <memory>

/**
 * Classe représentant le plateau d'échecs
 * Respecte le Single Responsibility Principle - ne gère que la structure du plateau
 */
class Board {
private:
    using BoardArray = std::array<std::array<std::unique_ptr<Piece>, ChessConstants::BOARD_SIZE>, ChessConstants::BOARD_SIZE>;
    BoardArray board_;
    
public:
    /**
     * Constructeur - initialise un plateau vide
     */
    Board() {
        clearBoard();
    }
    
    /**
     * Destructeur - les smart pointers gèrent automatiquement la mémoire
     */
    ~Board() = default;
    
    /**
     * Constructeur de copie
     */
    Board(const Board& other) {
        copyFrom(other);
    }
    
    /**
     * Opérateur d'assignation
     */
    Board& operator=(const Board& other) {
        if (this != &other) {
            copyFrom(other);
        }
        return *this;
    }
    
    /**
     * Obtient la pièce à une position donnée
     */
    Piece* getPieceAt(const Position& pos) const {
        if (!pos.isValid()) {
            return nullptr;
        }
        return board_[pos.getY()][pos.getX()].get();
    }
    
    /**
     * Place une pièce à une position donnée
     */
    void setPieceAt(const Position& pos, std::unique_ptr<Piece> piece) {
        if (pos.isValid()) {
            board_[pos.getY()][pos.getX()] = std::move(piece);
        }
    }
    
    /**
     * Supprime une pièce à une position donnée
     */
    void removePieceAt(const Position& pos) {
        if (pos.isValid()) {
            board_[pos.getY()][pos.getX()].reset();
        }
    }
    
    /**
     * Vérifie si une position est vide
     */
    bool isEmpty(const Position& pos) const {
        return getPieceAt(pos) == nullptr;
    }
    
    /**
     * Déplace une pièce d'une position à une autre
     */
    bool movePiece(const Move& move) {
        if (!move.isValid()) {
            return false;
        }
        
        Piece* piece = getPieceAt(move.getFrom());
        if (!piece) {
            return false;
        }
        
        // Déplace la pièce
        auto movedPiece = std::move(board_[move.getFrom().getY()][move.getFrom().getX()]);
        board_[move.getTo().getY()][move.getTo().getX()] = std::move(movedPiece);
        board_[move.getTo().getY()][move.getTo().getX()]->setPosition(move.getTo());
        
        return true;
    }
    
    /**
     * Vide le plateau
     */
    void clearBoard() {
        for (auto& row : board_) {
            for (auto& piece : row) {
                piece.reset();
            }
        }
    }
    
    /**
     * Vérifie si le chemin entre deux positions est libre
     */
    bool isPathClear(const Position& from, const Position& to) const {
        if (from == to) {
            return true;
        }
        
        int deltaX = to.getX() - from.getX();
        int deltaY = to.getY() - from.getY();
        
        int stepX = (deltaX > 0) ? 1 : (deltaX < 0) ? -1 : 0;
        int stepY = (deltaY > 0) ? 1 : (deltaY < 0) ? -1 : 0;
        
        Position current(from.getX() + stepX, from.getY() + stepY);
        
        while (current != to) {
            if (!isEmpty(current)) {
                return false;
            }
            current.setPosition(current.getX() + stepX, current.getY() + stepY);
        }
        
        return true;
    }
    
private:
    /**
     * Copie le contenu d'un autre plateau
     */
    void copyFrom(const Board& other) {
        clearBoard();
        for (int y = 0; y < ChessConstants::BOARD_SIZE; ++y) {
            for (int x = 0; x < ChessConstants::BOARD_SIZE; ++x) {
                if (other.board_[y][x]) {
                    board_[y][x] = other.board_[y][x]->clone();
                }
            }
        }
    }
};

#endif // BOARD_HPP