#ifndef BOARD_RENDERER_HPP
#define BOARD_RENDERER_HPP

#include "../Core/Board.hpp"
#include "../Enums/Color.hpp"
#include "../Enums/PieceType.hpp"
#include "../Utils/Constants.hpp"
#include <iostream>
#include <string>

/**
 * Classe responsable de l'affichage du plateau
 * Respecte le Single Responsibility Principle
 */
class BoardRenderer {
public:
    /**
     * Affiche le plateau dans la console
     */
    static void render(const Board& board) {
        std::cout << "  ";
        for (int x = 0; x < ChessConstants::BOARD_SIZE; ++x) {
            std::cout << static_cast<char>('a' + x) << " ";
        }
        std::cout << std::endl;
        
        for (int y = ChessConstants::BOARD_SIZE - 1; y >= 0; --y) {
            std::cout << (y + 1) << " ";
            
            for (int x = 0; x < ChessConstants::BOARD_SIZE; ++x) {
                Position pos(x, y);
                Piece* piece = board.getPieceAt(pos);
                
                if (piece) {
                    std::cout << getPieceSymbol(*piece) << " ";
                } else {
                    // Affiche un point pour les cases vides
                    std::cout << ". ";
                }
            }
            
            std::cout << (y + 1) << std::endl;
        }
        
        std::cout << "  ";
        for (int x = 0; x < ChessConstants::BOARD_SIZE; ++x) {
            std::cout << static_cast<char>('a' + x) << " ";
        }
        std::cout << std::endl << std::endl;
    }
    
    /**
     * Affiche le plateau avec des symboles Unicode
     */
    static void renderUnicode(const Board& board) {
        std::cout << "  ";
        for (int x = 0; x < ChessConstants::BOARD_SIZE; ++x) {
            std::cout << static_cast<char>('a' + x) << " ";
        }
        std::cout << std::endl;
        
        for (int y = ChessConstants::BOARD_SIZE - 1; y >= 0; --y) {
            std::cout << (y + 1) << " ";
            
            for (int x = 0; x < ChessConstants::BOARD_SIZE; ++x) {
                Position pos(x, y);
                Piece* piece = board.getPieceAt(pos);
                
                if (piece) {
                    std::cout << getUnicodePieceSymbol(*piece) << " ";
                } else {
                    // Affiche un point pour les cases vides
                    std::cout << ". ";
                }
            }
            
            std::cout << (y + 1) << std::endl;
        }
        
        std::cout << "  ";
        for (int x = 0; x < ChessConstants::BOARD_SIZE; ++x) {
            std::cout << static_cast<char>('a' + x) << " ";
        }
        std::cout << std::endl << std::endl;
    }
    
private:
    /**
     * Retourne le symbole ASCII d'une pièce
     */
    static char getPieceSymbol(const Piece& piece) {
        char symbol;
        
        switch (piece.getType()) {
            case PieceType::PAWN:   symbol = 'P'; break;
            case PieceType::ROOK:   symbol = 'R'; break;
            case PieceType::KNIGHT: symbol = 'N'; break;
            case PieceType::BISHOP: symbol = 'B'; break;
            case PieceType::QUEEN:  symbol = 'Q'; break;
            case PieceType::KING:   symbol = 'K'; break;
            default:                symbol = '?'; break;
        }
        
        // Minuscule pour les pièces noires, majuscule pour les blanches
        return piece.isWhite() ? symbol : static_cast<char>(std::tolower(symbol));
    }
    
    /**
     * Retourne le symbole Unicode d'une pièce
     */
    static std::string getUnicodePieceSymbol(const Piece& piece) {
        bool isWhite = piece.isWhite();
        
        switch (piece.getType()) {
            case PieceType::PAWN:   return isWhite ? "♟" : "♙";
            case PieceType::ROOK:   return isWhite ? "♜" : "♖";
            case PieceType::KNIGHT: return isWhite ? "♞" : "♘";
            case PieceType::BISHOP: return isWhite ? "♝" : "♗";
            case PieceType::QUEEN:  return isWhite ? "♛" : "♕";
            case PieceType::KING:   return isWhite ? "♚" : "♔";
            default:                return "?";
        }
    }
};

#endif // BOARD_RENDERER_HPP