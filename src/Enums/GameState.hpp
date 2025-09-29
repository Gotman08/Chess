#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

/**
 * Enumération représentant les états possibles d'une partie d'échecs
 */
enum class GameState {
    PLAYING,
    CHECK,
    CHECKMATE,
    STALEMATE,
    DRAW
};

#endif // GAME_STATE_HPP