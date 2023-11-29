#include "Board.h"
#include "Side.h"

#include <vector>

Board::Board(int nHoles, int nInitialBeansPerHole) // Construct a Board with the indicated number of holes per side (not counting the pot) and initial number of beans per hole. If nHoles is not positive, act as if it were 1; if nInitialBeansPerHole is negative, act as if it were 0.
{
    m_holes = nHoles;
    m_beans = nInitialBeansPerHole;
    if (nHoles <= 0)
        m_holes = 1;
    if (nInitialBeansPerHole < 0)
        m_beans = 0;
    
    // put 0 each of the pots
    m_North.push_back(0);
    m_South.push_back(0);
    
    // put beans into each hole
    for (int i = 1; i <= m_holes; i++)
    {
        m_North.push_back(m_beans);
        m_South.push_back(m_beans);
    }
}


Board::Board(const Board &other) // copy constructor
{
    m_holes = other.m_holes;
    m_beans = other.m_beans;
    m_North = other.m_North;
    m_South = other.m_South;
}


int Board::holes() const // Return the number of holes on a side (not counting the pot).
{
    return m_holes;
}


int Board::beans(Side s, int hole) const // Return the number of beans in the indicated hole or pot, or −1 if the hole number is invalid.
{
    // invalid hole: negative hole, hole is bigger than number of holes in game
    if (hole < 0 || hole > m_holes)
        return -1;
    if (s == 0)
        return m_North.at(hole);
    if (s == 1)
        return m_South.at(hole);
    else // side other than north or south
        return -1;
}


int Board::beansInPlay(Side s) const // Return the total number of beans in all the holes on the indicated side, not counting the beans in the pot.
{
    int count = 0;
    if (s == 0) // for north
    {
        for (int i = 1; i <= m_holes; i++)
            count += m_North.at(i);
    }
    if (s == 1) // for south
    {
        for (int i = 1; i <= m_holes; i++)
            count += m_South.at(i);
    }
    return count;
}


int Board::totalBeans() const // Return the total number of beans in the game, including any in the pots.
{
    int totalCount = 0;
    for (int i = 0; i < m_North.size(); i++)
        totalCount += beans(NORTH, i);
    for (int i = 0; i < m_South.size(); i++)
        totalCount += beans(SOUTH, i);
    return totalCount;
}


bool Board::sow(Side s, int hole, Side& endSide, int& endHole) // If the hole indicated by (s,hole) is empty or invalid or a pot, this function returns false without changing anything. Otherwise, it will return true after sowing the beans: the beans are removed from hole (s,hole) and sown counterclockwise, including s's pot if encountered, but skipping s's opponent's pot. The function sets the parameters endSide and endHole to the side and hole where the last bean was placed. (This function does not make captures or multiple turns; different Kalah variants have different rules about these issues, so dealing with them should not be the responsibility of the Board class.)
{
    // if hole is empty, invalid, or a pot then return false
    if (beans(s, hole) == 0 || beans(s, hole) == -1 || hole == 0)
        return false;
    
    // store # of beans in that hole in hand
    int currentBeans = beans(s, hole);
    
    // take all beans out of that hole
    if (s == 0)
        m_North.at(hole) = 0;
    if (s == 1)
        m_South.at(hole) = 0;
    
    
    // if it is north
    if (s == 0)
    {
        Side sideatm = NORTH;
        int holeatm = hole - 1; // must begin at the hole to the left of the start
        
        // sowing action until we run out of beans
        while (currentBeans > 0)
        {
            // when we hit north's pot (we must check this first since it includes the same conditions as it just normal north)
            if (sideatm == NORTH && holeatm == 0)
            {
                m_North.at(0) += 1; // add 1 to north pot
                currentBeans--; // subtract a bean
                sideatm = SOUTH; // switch sides
                holeatm = 1; // begin at south's 1 hole
            }
            // when at a north hole
            else if (sideatm == NORTH)
            {
                m_North.at(holeatm) += 1; // drop 1 into the hole
                currentBeans--; // subtract a bean
                holeatm--; // move to the next hole
            }
            // when we switch sides and we hit their hole we must skip it (we must check this first since it includes the same conditions as it just normal south) (*make sure to check ending, if we end with north and m_holes then we technically ended at south's pot)
            else if (sideatm == SOUTH && holeatm > m_holes)
            {
                sideatm = NORTH; // switch sides
                holeatm = m_holes; // begin at the other side's last hole
            }
            // when we switch sides
            else if (sideatm == SOUTH)
            {
                m_South.at(holeatm) += 1; // drop 1 to the hole
                currentBeans--; // subtract a bean
                holeatm++; // update the hole to the next one
            }
        }
        
        // if we end on the south side's first hole, that means it was supposed to end at north's pot (since it updates before)
        if (sideatm == SOUTH && holeatm == 1)
        {
            endSide = NORTH;
            endHole = 0;
        }
        // otherwise, we should end where we end
        else if (sideatm == NORTH)
        {
            endSide = NORTH;
            endHole = holeatm + 1; // we must go back one spot since the while loop will update currentHole before terminating
        }
        else if (sideatm == SOUTH)
        {
            endSide = SOUTH;
            endHole = holeatm - 1; // we must go back one spot since the while loop will update currentHole before terminating
        }
        return true;
    }
            
    // if it is south
    if (s == 1)
    {
        Side sideatm = SOUTH;
        int holeatm = hole + 1;
        
        // sowing action
        while (currentBeans > 0)
        {
            // when we hit south's pot (we must check this first since it includes the same conditions as it just normal south)
            if (sideatm == SOUTH && holeatm > m_holes)
            {
                m_South.at(0) += 1; // add 1 to south's pot
                currentBeans--; // subtract a bean
                sideatm = NORTH; // switch sides
                holeatm = m_holes; // begin at north's last hole
            }
            
            // when at a south hole
            else if (sideatm == SOUTH)
            {
                m_South.at(holeatm) += 1; // drop 1 into the hole
                currentBeans--; // subtract a bean
                holeatm++; // move to the next hole
            }
            
            // when we switch sides and we hit their hole we must skip it (we must check this first since it includes the same conditions as it just normal north)
            else if (sideatm == NORTH && holeatm == 0)
            {
                sideatm = SOUTH; // switch sides
                holeatm = 1; // begin at the other side's first hole
            }
            
            // when we switch sides
            else if (sideatm == NORTH)
            {
                m_North.at(holeatm) += 1; // drop 1 to the hole
                currentBeans--; // subtract a bean
                holeatm--; // update the hole to the next one
            }
        }
        
        // if we end on north's first hole technically we should have ended at south's pot
        if (sideatm == NORTH && holeatm == m_holes)
        {
            endSide = SOUTH;
            endHole = 0;
        }
        // otherwise, we should end where we end
        else if (sideatm == NORTH)
        {
            endSide = NORTH;
            endHole = holeatm + 1; // we must go back one spot since the while loop will update currentHole before terminating
        }
        else if (sideatm == SOUTH)
        {
            endSide = SOUTH;
            endHole = holeatm - 1; // we must go back one spot since the while loop will update currentHole before terminating
        }
        return true;
    }
    return false;
}


bool Board::moveToPot(Side s, int hole, Side potOwner) // If the indicated hole is invalid or a pot, return false without changing anything. Otherwise, move all the beans in hole (s,hole) into the pot belonging to potOwner and return true.
{
    // If the indicated hole is invalid or a pot, return false without changing anything.
    if ((s != 0 && s != 1) || hole < 0 || hole > m_holes)
        return false;
   
    // Otherwise, move all the beans in hole (s,hole) into the pot belonging to potOwner and return true.
    int currentBeans = beans(s, hole);
    
    if (s == 0 && potOwner == 0)
    {
        m_North.at(hole) = 0;
        m_North.at(0) += currentBeans;
    }
    if (s == 0 && potOwner == 1)
    {
        m_North.at(hole) = 0;
        m_South.at(0) += currentBeans;
    }
    if (s == 1 && potOwner == 0)
    {
        m_South.at(hole) = 0;
        m_North.at(0) += currentBeans;
    }
    if (s == 1 && potOwner == 1)
    {
        m_South.at(hole) = 0;
        m_South.at(0) += currentBeans;
    }
    return true;
}


bool Board::setBeans(Side s, int hole, int beans) // If the indicated hole is invalid or beans is negative, this function returns false without changing anything. Otherwise, it will return true after setting the number of beans in the indicated hole or pot to the value of the third parameter. (This could change what beansInPlay and totalBeans return if they are called later.) This function exists solely so that we and you can more easily test your program: None of your code that implements the member functions of any class is allowed to call this function directly or indirectly. (We'll show an example of its use below.)
{
    // If the indicated hole is invalid or beans is negative, this function returns false without changing anything.
    if ((s != 0 && s != 1)|| hole < 0 || hole > m_holes)
        return false;
    
    // Otherwise, it will return true after setting the number of beans in the indicated hole or pot to the value of the third parameter. (This could change what beansInPlay and totalBeans return if they are called later.)
    if (s == 0)
        m_North.at(hole) = beans;
    if (s == 1)
        m_South.at(hole) = beans;

    return true;
}
