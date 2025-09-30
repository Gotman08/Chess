#include "src/Core/Game.hpp"
#include "src/Utils/Position.hpp"
#include "src/Utils/Move.hpp"
#include <iostream>
#include <string>

/**
 * Fonction pour parser une position depuis une notation d'échecs (ex: "e2")
 */
Position parsePosition(const std::string& notation) {
    if (notation.length() != 2) {
        throw std::invalid_argument("Format de position invalide");
    }
    
    char file = notation[0];
    char rank = notation[1];
    
    if (file < 'a' || file > 'h' || rank < '1' || rank > '8') {
        throw std::invalid_argument("Position hors limites");
    }
    
    int x = file - 'a';
    int y = rank - '1';
    
    return Position(x, y);
}

/**
 * Fonction principale
 */
int main() {
    try {
        std::cout << "Initialisation du jeu..." << std::endl;
        Game game;
        std::cout << "Jeu initialisé avec succès!" << std::endl;
        std::string input;
        
        std::cout << "=== JEU D'ÉCHECS ===" << std::endl;
        std::cout << "Entrez vos mouvements au format 'e2 e4' ou 'quit' pour quitter" << std::endl;
        std::cout << "Les blancs commencent!" << std::endl << std::endl;
        
        while (true) {
            game.displayBoard();
            game.displayScores();
            
            const Player* currentPlayer = game.getCurrentPlayer();
            std::cout << "Au tour des " << (currentPlayer->isWhite() ? "Blancs" : "Noirs") << std::endl;
            std::cout << "Votre mouvement: ";
            
            // Vérifier si l'entrée est valide et gérer Ctrl+D (EOF)
            if (!std::getline(std::cin, input)) {
                if (std::cin.eof()) {
                    std::cout << "\nCtrl+D détecté. Au revoir!" << std::endl;
                } else {
                    std::cout << "\nErreur de lecture. Au revoir!" << std::endl;
                }
                break;
            }
            
            if (input == "quit" || input == "q") {
                std::cout << "Merci d'avoir joué!" << std::endl;
                break;
            }
            
            try {
                // Parse le mouvement
                size_t spacePos = input.find(' ');
                if (spacePos == std::string::npos) {
                    std::cout << "Format invalide! Utilisez: e2 e4" << std::endl;
                    continue;
                }
                
                std::string fromStr = input.substr(0, spacePos);
                std::string toStr = input.substr(spacePos + 1);
                
                Position from = parsePosition(fromStr);
                Position to = parsePosition(toStr);
                Move move(from, to);
                
                // Vérification avec message détaillé
                std::string errorMessage = game.validateMoveWithMessage(move);
                if (errorMessage.empty()) {
                    if (game.makeMove(move)) {
                        std::cout << "Mouvement effectué: " << fromStr << " -> " << toStr << std::endl << std::endl;
                    } else {
                        std::cout << "Erreur inattendue lors du mouvement!" << std::endl;
                    }
                } else {
                    std::cout << "Mouvement refusé: " << errorMessage << std::endl;
                }
                
            } catch (const std::exception& e) {
                std::cout << "Erreur: " << e.what() << std::endl;
            }
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Erreur fatale: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}