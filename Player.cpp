#include "Player.h"
#include "Side.h"
#include "Board.h"

#include <limits.h>
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

// Player Functions
Player::Player(string name) // Create a Player with the indicated name.
{
    m_name = name;
}
string Player::name() const // Return the name of the player.
{
    return m_name;
}
bool Player::isInteractive() const // Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.
{
    return false;
}
Player::~Player() // Since this class is designed as a base class, it should have a virtual destructor.
{}



//////////////////////////////////////////////////////////////////////////////////////////////////////////// PLAYER FUNCTIONS //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



// HumanPlayer Functions
HumanPlayer::HumanPlayer(string name) : Player(name)
{}
bool HumanPlayer::isInteractive() const
{
    return true;
}
int HumanPlayer::chooseMove(const Board& b, Side s) const
{
    // A HumanPlayer chooses its move by prompting a person running the program for a move (reprompting if necessary until the person enters a valid hole number), and returning that choice.
    // If no move is possible, return −1.
    
    bool chosenMove = false;
    int moveChoice = -1;
    
    // do this forever until it returns
    while(chosenMove == false)
    {
        cout << "Please choose a hole, " << name() << ": ";
        cin >> moveChoice;
        
        // if the # of beans at that location is 0...
        if (b.beans(s, moveChoice) == 0)
            cout << "No beans in this hole" << endl;
        // if the beans function for that location returns -1 (this means that they chose an invalid hole) or if the hole is 0 (which is valid but the pot)
        else if (b.beans(s, moveChoice) == -1 || moveChoice == 0)
            cout << "Invalid hole number!" << endl;
        else
            chosenMove = true;
    }
    return moveChoice;
}
HumanPlayer::~HumanPlayer()
{}



//////////////////////////////////////////////////////////////////////////////////////////////////////////// HUMANPLAYER FUNCTIONS //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



// BadPlayer Functions
BadPlayer::BadPlayer(string name) : Player(name)
{}
int BadPlayer::chooseMove(const Board& b, Side s) const
{
    // A BadPlayer is a computer player that chooses an arbitrary valid move and returns that choice.
    // "Arbitrary" can be what you like: leftmost, nearest to pot, fewest beans, random, etc.. The point of this class is to have an easy-to-implement class that at least plays legally.
    
    // If no move is possible, return −1.
    if (b.beansInPlay(s) == 0)
        return -1;

    // iterate through the board and returns the first one
    for (int i = 1; i <= b.holes(); i++)
    {
        int currentBeans = b.beans(s, i);
        if (currentBeans > 0)
        {
            return i;
        }
    }
    // technically we don't need the first condition?
    return -1;
}
BadPlayer::~BadPlayer()
{}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// BADPLAYER FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



SmartPlayer::SmartPlayer(string name) : Player(name)
{}
SmartPlayer::~SmartPlayer()
{}
bool SmartPlayer::chooseMoveOptimize(const Board& b, Side s, int& hole) const
{
    for (int i = 1; i < b.holes(); i++)
    {
        // if we can sow can be done
        Board duplicate(b);
        Side endSideCopy;
        int endHoleCopy;
        if (duplicate.sow(s, i, endSideCopy, endHoleCopy) == true)
        {
            // if we can make an additional move additional move
            if (endSideCopy == s && endHoleCopy == 0)
            {
                hole = i;
                return true;
            }
            
        }
    }
    return false;
}
int SmartPlayer::evaluate(const Board& b) const // given a position, returns a number that measures how good that position is for the player (returns a high number if good for south, returns low number if good for north)
{
    // TODO: "The greater the difference between the number of beans in my pot and my opponenent's the better"
    // TODO: "Measures how good a position is for one player and how bad it is for the other" aka (returning high number for south = south tries to find high numbers, north tries to find low number)
    
    // returns the # of beans difference between south and north side
    int value = (b.beansInPlay(SOUTH) + b.beans(SOUTH, POT) - b.beansInPlay(NORTH) + b.beans(NORTH, POT));
    // if north has more than south by at least 10, mark as -infinity
    if (value < -10)
        return INT_MIN;
    // if south has more than north by at least 10, mark as +infinity
    if (value > -10)
        return INT_MAX;
    // otherwise, just return the difference between south and north
    else
        return value;
}
bool SmartPlayer::completedMove(Board& b, Side s, int hole, Side& endSide, int& endHole) const // this returns if we have completed a move or not for  SmartPlayer
{
    // if we can sow for that position
    if (b.sow(s, hole, endSide, endHole) == true)
    {
        // case: additional turn
        if (s == endSide && endHole == POT)
            return false;
        // case: capture
        if (endHole != 0 && s == endSide && b.beans(s, endHole) == 1 && b.beans(opponent(s), endHole) > 0)
        {
            b.moveToPot(s, endHole, s);
            b.moveToPot(opponent(s), endHole, s);
        }
        return true;
    }
    // if we cannot sow for that position, we did not complete the move...
    else
        return false;
}
void SmartPlayer::minimax(const Board& b, Side s, int& evaluatedValue, int& bestHole, int depth, double timeLimit, JumpyTimer & j) const // find what is considered to be the best play available
{
    // TODO: FOLLOW PSEUDOCODE GIVEN
    int firstLegalMove = 1;
    
    // if no move for player exists (if there is no beans in play for that side)
    if (b.beansInPlay(s) == 0)
    {
        bestHole = -1;
        evaluatedValue = evaluate(b);
        return;
    }
    
    if (timeLimit <= 0 || depth >= 5)
    {
        bestHole = -1;
        evaluatedValue = (b.beans(SOUTH, POT) - b.beans(NORTH, POT)); // we could call evaluate but since this is the last recursive call (we are not checking below this node), we should just compares the pots
        return;
    }
    
    // for every hole h the player can choose...
    for (int i = 1; i <= b.holes(); i++)
    {
        double thisBranchTimeLimit = timeLimit / (b.holes() - i + 1);
        double startTime = j.elapsed();
        
        // case of an invalid move (there are no beans) increase the counter
        // the counter stops at the first legal move (even if it is not the best)
        if (b.beans(s, i) == 0)
        {
            firstLegalMove += 1;
            continue;
        }
        
        Side endSide;
        int endHole;
        int bestHole2;
        int evaluatedValue2;
        Board duplicate(b); // make a copy of board (since we don't want to manipulate the original board)
        
        // "make the move"
        if (completedMove(duplicate, s, i, endSide, endHole) == true) // if we can complete the move...
            minimax(duplicate, opponent(s), evaluatedValue2, bestHole2, depth + 1, thisBranchTimeLimit, j); // recursively choose the move with the other side and deeper depth (go down the tree)
        else // if we cannot complete the move...
            minimax(duplicate, s, evaluatedValue2, bestHole2, depth, thisBranchTimeLimit, j); // recursively choose the move with the same side and same depth (aka other pathways on the other side of the tree)
        
        // since we made a copy of the board, we do not have the unmake the move (or we can minimax(b, s, ..., ... depth - 1)
        
        // set's value & bestHole of the first legal move being made so that later when we compare we are comparing with a legal move
        if (i == firstLegalMove)
        {
            bestHole = i;
            evaluatedValue = evaluatedValue2;
        }
        
        // evaluating the best but MAKE SURE TO ACCOUNT FOR NORTH AND SOUTH
        // when it is south...
        if (s == SOUTH)
        {
            if (evaluatedValue2 > evaluatedValue) // if the value returned by evaluate is higher (higher means good for south) than what is seen, update the hole and original evaluatedvalue
            {
                bestHole = i;
                evaluatedValue = evaluatedValue2;
            }
        }
        // when it is north...
        if (s == NORTH)
        {
            if (evaluatedValue2 < evaluatedValue) // if the value returned by evaluate is lower (lower means good for north) than what is seen, update the hole and original evaluatedvalue
            {
                bestHole = i;
                evaluatedValue = evaluatedValue2;
            }
        }
        timeLimit -= (j.elapsed() - startTime);
    }
    return;
}
int SmartPlayer::chooseMove(const Board& b, Side s) const   // A SmartPlayer chooses a valid move and returns it.
{
    // TODO: prioritize getting more turns
    int hole;
    if (chooseMoveOptimize(b, s, hole) == true)
        return hole;
    else
    {
        // TODO: use minimax function! (this calls the eval function)
        // NOTES: evaluate takes in board and returns the measure
        // NOTES: minimax takes in (const Board& b, Side s, int evaluatedValue, int& bestHole, int depth) and returns it in the bestHole value with side S
        // NOTES: completedMove takes in (Board& b, Side s, int hole, Side& endSide, int& endHole) and returns a bool whether it did the move or not
        int depth = 0; // initialize depth to begin with 0
        int evaluatedValue, bestHole;
        double timeLimit = 4990;
        JumpyTimer j(1000);
        minimax(b, s, evaluatedValue, bestHole, depth, timeLimit, j);
        return bestHole;
    }
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// SMARTPLAYER FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

