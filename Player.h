#ifndef Player_h
#define Player_h

#include "Side.h"
#include "Board.h"
#include <limits.h>

#include <string>


class Player
{
public:
    Player(std::string name); // Create a Player with the indicated name.
    std::string name() const; // Return the name of the player.
    virtual bool isInteractive() const; //Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.
    virtual int chooseMove(const Board& b, Side s) const = 0; // Every concrete class derived from this class must implement this function so that if the player were to be playing side s and had to make a move given board b, the function returns the move the player would choose. If no move is possible, return −1.
    virtual ~Player(); // Since this class is designed as a base class, it should have a virtual destructor.
private:
    std::string m_name;
};

class HumanPlayer : public Player
{
public:
    HumanPlayer(std::string name);
    virtual bool isInteractive() const;
    virtual int chooseMove(const Board& b, Side s) const;
    virtual ~HumanPlayer();
};

class BadPlayer : public Player
{
public:
    BadPlayer(std::string name);
    virtual int chooseMove(const Board& b, Side s) const;
    virtual ~BadPlayer();
};

class SmartPlayer : public Player
{
public:
    SmartPlayer(std::string name);
    virtual int chooseMove(const Board& b, Side s) const;
    virtual ~SmartPlayer();
private:
    bool chooseMoveOptimize(const Board& b, Side s, int& hole) const; // returns whether we can make additional move or not (since this is highest precedence)
    int evaluate(const Board& b) const; // given a position, returns a number that measures how good that position is for the player
    bool completedMove(Board& b, Side s, int hole, Side& endSide, int& endHole) const; // this returns if we can make a move or not for the SmartPlayer
    void minimax(const Board& b, Side s, int& evaluatedValue, int& bestHole, int depth, double timeLimit, JumpyTimer & j) const; // find what is considered to be the best play available
};

#endif /* Player_h */


