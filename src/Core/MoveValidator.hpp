#ifndef MOVE_VALIDATOR_HPP
#define MOVE_VALIDATOR_HPP

#include "../Core/Board.hpp"
#include "../Utils/Move.hpp"
#include "../Pieces/Piece.hpp"
#include "../Pieces/Pawn.hpp"

/**
 * Classe responsable de la validation des mouvements
 * Respecte le Single Responsibility Principle
 */
class MoveValidator {
public:
    /**
     * Valide un mouvement sur le plateau
     */
    static bool isValidMove(const Board& board, const Move& move, Color playerColor) {
        // Vérifications de base
        if (!move.isValid()) {
            return false;
        }
        
        Piece* piece = board.getPieceAt(move.getFrom());
        if (!piece) {
            return false; // Pas de pièce à déplacer
        }
        
        // SÉCURITÉ CRITIQUE: Le joueur ne peut déplacer que ses propres pièces
        if (piece->getColor() != playerColor) {
            return false; // Ce n'est pas la pièce du joueur - TENTATIVE DE TRICHE DÉTECTÉE
        }
        
        // Vérifie si la pièce peut faire ce mouvement selon ses règles
        if (!piece->canMoveTo(move.getTo())) {
            return false;
        }
        
        // Vérifie la destination
        Piece* targetPiece = board.getPieceAt(move.getTo());
        if (targetPiece && targetPiece->getColor() == playerColor) {
            return false; // Ne peut pas capturer ses propres pièces
        }
        
        // Vérifie si le chemin est libre (sauf pour le cavalier)
        if (piece->getType() != PieceType::KNIGHT) {
            if (!board.isPathClear(move.getFrom(), move.getTo())) {
                return false;
            }
        }
        
        // Règles spéciales pour le pion
        if (piece->getType() == PieceType::PAWN) {
            return validatePawnMove(board, move, *static_cast<Pawn*>(piece));
        }
        
        return true;
    }
    
private:
    /**
     * Valide spécifiquement les mouvements de pion
     */
    static bool validatePawnMove(const Board& board, const Move& move, const Pawn& pawn) {
        Piece* targetPiece = board.getPieceAt(move.getTo());
        
        // Si c'est un mouvement de capture en diagonale
        if (abs(move.getDeltaX()) == 1) {
            return pawn.canCapture(move.getTo()) && targetPiece != nullptr;
        }
        
        // Si c'est un mouvement vers l'avant
        if (move.getDeltaX() == 0) {
            // La case de destination doit être vide
            if (targetPiece != nullptr) {
                return false;
            }
            
            // Si c'est un mouvement de deux cases, la case intermédiaire doit être vide
            if (abs(move.getDeltaY()) == 2) {
                Position intermediate(move.getFrom().getX(), 
                                    move.getFrom().getY() + (move.getDeltaY() > 0 ? 1 : -1));
                return board.isEmpty(intermediate);
            }
            
            return true;
        }
        
        return false;
    }
};

#endif // MOVE_VALIDATOR_HPP