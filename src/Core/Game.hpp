#ifndef GAME_HPP
#define GAME_HPP

#include "Board.hpp"
#include "MoveValidator.hpp"
#include "../Players/Player.hpp"
#include "../Pieces/Pawn.hpp"
#include "../Pieces/Rook.hpp"
#include "../Pieces/Knight.hpp"
#include "../Pieces/Bishop.hpp"
#include "../Pieces/Queen.hpp"
#include "../Pieces/King.hpp"
#include "../UI/BoardRenderer.hpp"
#include "../Enums/GameState.hpp"
#include "../Utils/Move.hpp"
#include <memory>

/**
 * Classe principale du jeu d'échecs
 * Coordonne toutes les autres classes et gère le flux du jeu
 */
class Game {
private:
    Board board_;
    std::unique_ptr<Player> whitePlayer_;
    std::unique_ptr<Player> blackPlayer_;
    Player* currentPlayer_;
    GameState gameState_;
    
    // Variables pour l'en passant
    Position enPassantTarget_;  // Position où l'en passant est possible
    bool enPassantAvailable_;   // Si une capture en passant est disponible
    Move lastMove_;             // Dernier mouvement effectué
    
public:
    /**
     * Constructeur
     */
    Game() : gameState_(GameState::PLAYING), 
             enPassantTarget_(Position(0, 0)), 
             enPassantAvailable_(false),
             lastMove_(Position(0, 0), Position(0, 0)) {
        whitePlayer_ = std::make_unique<Player>(Color::WHITE);
        blackPlayer_ = std::make_unique<Player>(Color::BLACK);
        currentPlayer_ = whitePlayer_.get(); // Les blancs commencent
        initializeBoard();
    }
    
    /**
     * Initialise le plateau avec la position de départ
     */
    void initializeBoard() {
        board_.clearBoard();
        
        // Pièces blanches (rangée 0)
        board_.setPieceAt(Position(0, 0), std::make_unique<Rook>(Position(0, 0), Color::WHITE));
        board_.setPieceAt(Position(1, 0), std::make_unique<Knight>(Position(1, 0), Color::WHITE));
        board_.setPieceAt(Position(2, 0), std::make_unique<Bishop>(Position(2, 0), Color::WHITE));
        board_.setPieceAt(Position(3, 0), std::make_unique<Queen>(Position(3, 0), Color::WHITE));
        board_.setPieceAt(Position(4, 0), std::make_unique<King>(Position(4, 0), Color::WHITE));
        board_.setPieceAt(Position(5, 0), std::make_unique<Bishop>(Position(5, 0), Color::WHITE));
        board_.setPieceAt(Position(6, 0), std::make_unique<Knight>(Position(6, 0), Color::WHITE));
        board_.setPieceAt(Position(7, 0), std::make_unique<Rook>(Position(7, 0), Color::WHITE));
        
        // Pions blancs (rangée 1)
        for (int x = 0; x < ChessConstants::BOARD_SIZE; ++x) {
            board_.setPieceAt(Position(x, 1), std::make_unique<Pawn>(Position(x, 1), Color::WHITE));
        }
        
        // Pions noirs (rangée 6)
        for (int x = 0; x < ChessConstants::BOARD_SIZE; ++x) {
            board_.setPieceAt(Position(x, 6), std::make_unique<Pawn>(Position(x, 6), Color::BLACK));
        }
        
        // Pièces noires (rangée 7)
        board_.setPieceAt(Position(0, 7), std::make_unique<Rook>(Position(0, 7), Color::BLACK));
        board_.setPieceAt(Position(1, 7), std::make_unique<Knight>(Position(1, 7), Color::BLACK));
        board_.setPieceAt(Position(2, 7), std::make_unique<Bishop>(Position(2, 7), Color::BLACK));
        board_.setPieceAt(Position(3, 7), std::make_unique<Queen>(Position(3, 7), Color::BLACK));
        board_.setPieceAt(Position(4, 7), std::make_unique<King>(Position(4, 7), Color::BLACK));
        board_.setPieceAt(Position(5, 7), std::make_unique<Bishop>(Position(5, 7), Color::BLACK));
        board_.setPieceAt(Position(6, 7), std::make_unique<Knight>(Position(6, 7), Color::BLACK));
        board_.setPieceAt(Position(7, 7), std::make_unique<Rook>(Position(7, 7), Color::BLACK));
    }
    
    /**
     * Tente de faire un mouvement
     */
    bool makeMove(const Move& move) {
        if (gameState_ != GameState::PLAYING) {
            return false;
        }
        
        // Vérification de sécurité supplémentaire : le joueur ne peut déplacer que ses propres pièces
        Piece* pieceToMove = board_.getPieceAt(move.getFrom());
        if (!pieceToMove) {
            return false; // Aucune pièce à déplacer
        }
        
        if (pieceToMove->getColor() != currentPlayer_->getColor()) {
            return false; // Le joueur essaie de déplacer une pièce adverse !
        }
        
        // Vérification spéciale pour l'en passant
        bool isEnPassantMove = false;
        Position enPassantCapturePos(0, 0);
        
        if (pieceToMove->getType() == PieceType::PAWN && enPassantAvailable_) {
            Pawn* pawn = static_cast<Pawn*>(pieceToMove);
            if (pawn->canCaptureEnPassant(move.getTo(), enPassantTarget_)) {
                isEnPassantMove = true;
                enPassantCapturePos = enPassantTarget_;
            }
        }
        
        if (!isEnPassantMove && !MoveValidator::isValidMove(board_, move, currentPlayer_->getColor())) {
            return false;
        }
        
        // Gestion de la capture
        Piece* capturedPiece = nullptr;
        
        if (isEnPassantMove) {
            // Capture en passant : la pièce capturée n'est pas sur la case de destination
            capturedPiece = board_.getPieceAt(enPassantCapturePos);
            if (capturedPiece) {
                currentPlayer_->addCapturedPiece(capturedPiece->clone());
                board_.removePieceAt(enPassantCapturePos);
            }
        } else {
            // Capture normale
            capturedPiece = board_.getPieceAt(move.getTo());
            if (capturedPiece) {
                currentPlayer_->addCapturedPiece(capturedPiece->clone());
            }
        }
        
        // Effectue le mouvement
        board_.movePiece(move);
        
        // Mise à jour de l'état de l'en passant pour le prochain tour
        updateEnPassantState(move, pieceToMove);
        
        // Sauvegarde du dernier mouvement
        lastMove_ = move;
        
        // Change de joueur
        switchPlayer();
        
        return true;
    }
    
    /**
     * Affiche le plateau
     */
    void displayBoard() const {
        BoardRenderer::renderUnicode(board_);
    }
    
    /**
     * Retourne le joueur actuel
     */
    const Player* getCurrentPlayer() const {
        return currentPlayer_;
    }
    
    /**
     * Retourne l'état du jeu
     */
    GameState getGameState() const {
        return gameState_;
    }
    
    /**
     * Affiche les scores des joueurs
     */
    void displayScores() const {
        std::cout << "Score Blanc: " << whitePlayer_->getScore() << std::endl;
        std::cout << "Score Noir: " << blackPlayer_->getScore() << std::endl;
        
        if (enPassantAvailable_) {
            char file = 'a' + enPassantTarget_.getX();
            int rank = enPassantTarget_.getY() + 1;
            std::cout << "En passant disponible en: " << file << rank << std::endl;
        }
    }
    
    /**
     * Vérifie si un mouvement est valide et retourne un message d'erreur détaillé
     */
    std::string validateMoveWithMessage(const Move& move) const {
        if (gameState_ != GameState::PLAYING) {
            return "La partie n'est pas en cours";
        }
        
        if (!move.isValid()) {
            return "Mouvement invalide (positions incorrectes)";
        }
        
        Piece* pieceToMove = board_.getPieceAt(move.getFrom());
        if (!pieceToMove) {
            return "Aucune pièce à cette position";
        }
        
        if (pieceToMove->getColor() != currentPlayer_->getColor()) {
            std::string playerColor = (currentPlayer_->getColor() == Color::WHITE) ? "blancs" : "noirs";
            std::string pieceColor = (pieceToMove->getColor() == Color::WHITE) ? "blanche" : "noire";
            return "Erreur: Les " + playerColor + " ne peuvent pas déplacer une pièce " + pieceColor + "!";
        }
        
        // Vérification spéciale pour l'en passant
        if (pieceToMove->getType() == PieceType::PAWN && enPassantAvailable_) {
            Pawn* pawn = static_cast<Pawn*>(pieceToMove);
            if (pawn->canCaptureEnPassant(move.getTo(), enPassantTarget_)) {
                return ""; // Mouvement d'en passant valide
            }
        }
        
        if (!MoveValidator::isValidMove(board_, move, currentPlayer_->getColor())) {
            return "Mouvement invalide selon les règles de cette pièce";
        }
        
        return ""; // Mouvement valide
    }
    
private:
    /**
     * Change le joueur actuel
     */
    void switchPlayer() {
        currentPlayer_ = (currentPlayer_ == whitePlayer_.get()) ? blackPlayer_.get() : whitePlayer_.get();
    }
    
    /**
     * Met à jour l'état de l'en passant après un mouvement
     */
    void updateEnPassantState(const Move& move, Piece* movedPiece) {
        // Reset de l'en passant précédent
        enPassantAvailable_ = false;
        
        // Vérifier si c'est un pion qui vient de bouger de 2 cases
        if (movedPiece->getType() == PieceType::PAWN) {
            int deltaY = abs(move.getTo().getY() - move.getFrom().getY());
            
            if (deltaY == 2) {
                // Un pion vient de faire un mouvement de 2 cases
                // L'en passant est disponible sur la case "traversée"
                int enPassantY = (move.getFrom().getY() + move.getTo().getY()) / 2;
                enPassantTarget_ = Position(move.getTo().getX(), enPassantY);
                enPassantAvailable_ = true;
            }
        }
    }
};

#endif // GAME_HPP