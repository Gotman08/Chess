#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

/**
 * Constantes utilisées dans le jeu d'échecs
 */
namespace ChessConstants {
    constexpr int BOARD_SIZE = 8;
    constexpr int MIN_COORDINATE = 0;
    constexpr int MAX_COORDINATE = 7;
    
    // Valeurs des pièces pour le calcul du score
    namespace PieceValues {
        constexpr int PAWN = 1;
        constexpr int KNIGHT = 3;
        constexpr int BISHOP = 3;
        constexpr int ROOK = 5;
        constexpr int QUEEN = 9;
        constexpr int KING = 0; // Le roi n'a pas de valeur car il est indispensable
    }
}

#endif // CONSTANTS_HPP