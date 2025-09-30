#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <string>
#include "../Players/Player.hpp"

class Node {
    public :

    Node* parent;
    Node** child;
    GameState state;
    int visitCount;
    float winScore;
    int childArraySize;
    Color playerNo;
    Piece* pieceMoved;
    Action action;


    Node();
    Node(State state);
    Node(State state, Color playerNo);
    ~Node();
    Node* getRandomChildNode();
    Node* getChildWithMaxScore();
    void incrementVisit();
    void addScore(float score);
    void setState(State state);
    State getState();
    Player getCurrentPlayer();
    void setParent(Node* parent);
    void setPieceMoved(Piece* piece);
    Piece* getPieceMoved();
    Action getAction();
    void setAction(Action action);
    void setChildArraySize(int size);
    int getChildArraySize();
    int getVisitCount();
    float getWinScore();
    bool isLeaf() const;
    bool isFullyExpanded() const;
    double getUCB1Value(double c = 1.41) const;
    Node* selectBestChild() const;
    void expand(const std::vector<Action>& possibleActions);
    void backpropagate(float result);
    bool isTerminal() const;
    Node* addChild(const Action& action, const State& newState);
    void removeChild(Node* child);
    std::vector<Node*> getChildren() const;
    void printTree(int depth = 0) const;
    std::string toString() const;
    
};


#endif