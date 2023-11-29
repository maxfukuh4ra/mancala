#include "Board.h"
#include "Player.h"
#include "Side.h"
#include "Game.h"

#include <string>
#include <iostream>

using namespace std;


Game::Game(const Board& b, Player* south, Player* north) : m_board(b) // Construct a Game to be played with the indicated players on a copy of the board b. The player on the south side always moves first.
{
    m_south = south;
    m_north = north;
    m_side = SOUTH; // always start on south
}

void Game::display() const // Display the game's board in a manner of your choosing, provided you show the names of the players and a reasonable representation of the state of the board.
{
    cout << "North Player: " << m_north->name() << endl;
   
    for (int i = 1; i <= m_board.holes(); i++)
        cout << "  " << m_board.beans(NORTH, i) << " ";
    cout << endl;
    
    cout << m_board.beans(NORTH, 0);
    for (int i = 1; i <= m_board.holes() * 3.9; i++)
        cout << " ";
    cout << m_board.beans(SOUTH, 0);
    cout << endl;
    
    for (int i = 1; i <= m_board.holes(); i++)
        cout << "  " << m_board.beans(SOUTH, i) << " ";
    cout << endl;
    cout << "South Player: " << m_south->name() << endl;
}

void Game::status(bool& over, bool& hasWinner, Side& winner) const // If the game is over (i.e., the move member function has been called and returned false), set over to true; otherwise, set over to false and do not change anything else. If the game is over, set hasWinner to true if the game has a winner, or false if it resulted in a tie. If hasWinner is set to false, leave winner unchanged; otherwise, set it to the winning side.
{
    // If the game is not over, do not change anything else
    for (int i = 1; i <= m_board.holes(); i++)
    {
        if (m_board.beans(NORTH, i) > 0 || m_board.beans(SOUTH, i) > 0)
        {
            over = false;
            return;
        }
            
    }
    over = true;
    // if south pot has more beans than north pot
    if (m_board.beans(SOUTH, 0) > m_board.beans(NORTH, 0))
    {
        // set winner
        hasWinner = true;
        winner = SOUTH;
    }
    // if north pot has more beans than south pot
    else if (m_board.beans(NORTH, 0) > m_board.beans(SOUTH, 0))
    {
        // set winner
        hasWinner = true;
        winner = NORTH;
    }
    // if the pots have the same amount of beans it is a tie
    else if (m_board.beans(NORTH, 0) == m_board.beans(SOUTH, 0))
        hasWinner = false;
}

bool Game::move(Side s) // Attempt to make a complete move for the player playing side s. "Complete" means that the player sows the seeds from a hole and takes any additional turns required or completes a capture. Whenever the player gets an additional turn, you should display the board so someone looking at the screen can follow what's happening. If the move can be completed, return true; if not, because the move is not yet completed but side s has no holes with beans to pick up and sow, sweep any beans in s's opponent's holes into that opponent's pot and return false.
{
    if (s == NORTH && m_board.beansInPlay(NORTH) == 0)
    {
        for (int i = 1; i <= m_board.holes(); i++)
            m_board.moveToPot(SOUTH, i, SOUTH);
        display(); // display the board for purposes of visualizing the status with pot #'s
        return false;
    }
    // if there are beans only in the north
    else if (s == SOUTH && m_board.beansInPlay(SOUTH) == 0)
    {
        for (int i = 1; i <= m_board.holes(); i++)
            m_board.moveToPot(NORTH, i, NORTH);
        display(); // display the board for purposes of visualizing the status with pot #'s
        return false;
    }

    Side endSide;
    int endHole;
        
    int selectedHole = -1;
    if (s == NORTH)
        selectedHole = m_north->chooseMove(m_board, s);
    if (s == SOUTH)
        selectedHole = m_south->chooseMove(m_board, s);
    
    // if we can sow
    if (m_board.sow(s, selectedHole, endSide, endHole) == true)
    {
        // capture (* make sure it is not the pot since we don't want to capture the other side's pot!)
        if (endHole != 0 && endSide == s && m_board.beans(s, endHole) == 1 && m_board.beans(opponent(s), endHole) > 0)
        {
            m_board.moveToPot(SOUTH, endHole, s);
            m_board.moveToPot(NORTH, endHole, s);
            return true;
        }
        // additional move: if it ends in our own pot...
        else if (endSide == s && endHole == 0)
        {
            display();
            return move(s); // recursively try another move
        }
    return true; // otherwise returns true if it can sow
    }
    else
        return false;
}

void Game::play() // Play the game. Display the progress of the game in a manner of your choosing, provided that someone looking at the screen can follow what's happening. If neither player is interactive, then to keep the display from quickly scrolling through the whole game, it would be reasonable periodically to prompt the viewer to press ENTER to continue and not proceed until ENTER is pressed. (The ignore function for input streams is useful here.) Announce the winner at the end of the game. You can apportion to your liking the responsibility for displaying the board between this function and the move function.
{
    // display the starting screen
    display();
    // bool endMove = true;
    bool over;
    bool hasWinner;
    Side winner;
    
    // while the game is not over
    do
    {
        move(m_side); // make a move (*starting with south)
        m_side = opponent(m_side); // swap the side to the other side
        display(); // display what it looks like after the move
        // if neither player is interative, pause and show the progress
        if (m_south->isInteractive() == false && m_north->isInteractive() == false)
        {
            cout << "Press ENTER to continue." << endl;
            cin.ignore(10000, '\n');
        }
        status(over, hasWinner, winner); // update the status
    } while (!over);
    
    // when the game is over...
    display(); // display the final game map
    // announce the winners if any
    if (hasWinner == false)
        cout << "The game is a tie." << endl;
    if (winner == SOUTH && hasWinner == true)
        cout << "The winner is " << m_south->name() << "!" << endl;
    else if (winner == NORTH && hasWinner == true)
        cout << "The winner is " << m_north->name() << "!" << endl;
}

int Game::beans(Side s, int hole) const // Return the number of beans in the indicated hole or pot of the game's board, or −1 if the hole number is invalid. This function exists so that we and you can more easily test your program.
{
    return m_board.beans(s, hole);
}
