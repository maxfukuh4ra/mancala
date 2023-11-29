//#include "Board.h"
//#include "Side.h"
//#include "Player.h"
//#include "Board.h"
//#include "Game.h"
//
//
//#include <iostream>
//#include <cassert>
//#include <string>
//#include <vector>
//
//using namespace std;
//
//void doBoardTests()
//{
//    // smallberg's test case
//    Board b(3, 2);
//    assert(b.holes() == 3  &&  b.totalBeans() == 12  && b.beans(SOUTH, POT) == 0  &&  b.beansInPlay(SOUTH) == 6);
//    b.setBeans(SOUTH, 1, 1);
//    b.moveToPot(SOUTH, 2, SOUTH);
//    assert(b.totalBeans() == 11 && b.beans(SOUTH, 1) == 1 && b.beans(SOUTH, 2) == 0 &&  b.beans(SOUTH, POT) == 2 && b.beansInPlay(SOUTH) == 3);
//    Side es;
//    int eh;
//    b.sow(SOUTH, 3, es, eh);
//    assert(es == NORTH  &&  eh == 3  &&  b.beans(SOUTH, 3) == 0  && b.beans(NORTH, 3) == 3  &&  b.beans(SOUTH, POT) == 3  && b.beansInPlay(SOUTH) == 1  &&  b.beansInPlay(NORTH) == 7);
//    b.sow(NORTH, 3, es, eh);
//    assert(es == NORTH  &&  eh == 0  &&  b.beans(NORTH, 3) == 0  && b.beans(NORTH, 2) == 3  &&  b.beans(NORTH, 1) == 3  && b.beans(NORTH, POT) == 1 && b.beansInPlay(SOUTH) == 1  &&  b.beansInPlay(NORTH) == 6);
//
//
//    // additional test case
//    Board a(4, 20);
//    assert(a.holes() == 4 && a.totalBeans() == 160 && a.beans(SOUTH, POT) == 0  &&  a.beansInPlay(SOUTH) == 80);
//
//    Side as;
//    int ah;
//    a.sow(SOUTH, 4, as, ah);
//    assert(as == NORTH  &&  ah == 4  &&  a.beans(NORTH, 4) == 23  && a.beans(NORTH, 3) == 22  && a.beans(NORTH, 2) == 22 && a.beans(NORTH, 1) == 22 && a.beans(NORTH, POT) == 0 && a.beans(SOUTH, 1) == 22 && a.beans(SOUTH, 2) == 22 && a.beans(SOUTH, 3) == 22 && a.beans(SOUTH, 4) == 2 && a.beans(SOUTH, POT) == 3 && a.beansInPlay(SOUTH) == 68 && a.beansInPlay(NORTH) == 89);
//
//    // test moveToPot function
//    a.moveToPot(NORTH, 1, NORTH);
//    assert(a.beans(NORTH, POT) == 22);
//    a.moveToPot(SOUTH, 4, SOUTH);
//    assert(a.beans(SOUTH, POT) == 5);
//    a.moveToPot(NORTH, 2, NORTH);
//    assert(a.beans(NORTH, POT) == 44);
//    a.moveToPot(NORTH, 3, SOUTH); // moving to opponent's pot
//    assert(a.beans(SOUTH, POT) == 27);
//
//    // board with 1 hole
//    Board c(1, 5);
//    assert(c.holes() == 1 && c.totalBeans() == 10 && c.beansInPlay(NORTH) == 5);
//
//    // board with 0 hole
//    Board d(0, 4);
//    assert(d.holes() == 1 && d.totalBeans() == 8);
//
//    // board with negative holes should act like 1
//    Board e(-1, 5);
//    assert(e.holes() == 1 && e.totalBeans() == 10);
//
//    // board with negative beans should act like 0
//    Board f(1, -3);
//    assert(f.holes() == 1 && f.totalBeans() == 0);
//
////    // Ayaan's Test Cases
////    Board b(3, 2);
////    assert(b.holes() == 3);
////    assert(b.totalBeans() == 12);
////    assert(b.beans(SOUTH, POT) == 0);
////    assert(b.beansInPlay(SOUTH) == 6);
////    b.setBeans(SOUTH, 1, 1);
////    b.moveToPot(SOUTH, 2, SOUTH);
////    assert(b.totalBeans() == 11);
////    assert(b.beans(SOUTH, 1) == 1);
////    assert(b.beans(SOUTH, 2) == 0);
////    assert(b.beans(SOUTH, POT) == 2);
////    assert(b.beansInPlay(SOUTH) == 3);
////
////    assert(b.totalBeans() == 11  &&  b.beans(SOUTH, 1) == 1  && b.beans(SOUTH, 2) == 0  &&  b.beans(SOUTH, POT) == 2  && b.beansInPlay(SOUTH) == 3);
////    Side es;
////    int eh;
////    b.sow(SOUTH, 3, es, eh);
////    assert(es == NORTH);
////    assert(eh == 3);
////    assert(b.beans(SOUTH, 3) == 0);
////    assert(b.beans(NORTH, 3) == 3);
////    assert(b.beans(SOUTH, POT) == 3);
////    assert(b.beansInPlay(SOUTH) == 1);
////    assert(b.beansInPlay(NORTH) == 7);
////
////    Board c(3, 2);
////    c.setBeans(SOUTH, 1, 8);
////    c.sow(SOUTH, 1, es, eh);
////    assert(es == SOUTH);
////    assert(eh == 2);
////    assert(c.beans(SOUTH, POT) == 1);
////    assert(c.beans(NORTH, 1) == 3);
////
////    Side essh;
////    int ehhh;
////    Side esh;
////    int ehh;
////    Board e(3, 2);
////    Board f(3, 2);
////    e.setBeans(SOUTH, 1, 8);
////    f.setBeans(NORTH, 1, 9);
////    e.sow(SOUTH, 1, esh, ehh);
////    f.sow(NORTH, 1, essh, ehhh);
////    assert(essh == SOUTH);
////    assert(esh == SOUTH);
////    assert(ehh == 2);
////    assert(ehhh == 1);
////    assert(e.beans(SOUTH, POT) == 1);
////    assert(e.beans(NORTH, 1) == 3);
////    Board d(3, 2);
////    d.setBeans(NORTH, 1, 16);
////    d.sow(NORTH, 1, es, eh);
////    assert(es == SOUTH);
////    assert(eh == 1);
////    assert(d.beans(SOUTH, POT) == 0);
////    assert(d.beans(NORTH, POT) == 3);
////
////    Board ross(3,2);
////    ross.setBeans(SOUTH, 1, 5);
////    ross.sow(SOUTH, 1, es, eh);
////    assert(eh == 2);
////    assert(es == NORTH);
////    assert(ross.beans(SOUTH, POT) == 1);
////    assert(ross.beans(NORTH, POT) == 0);
////    assert(ross.beans(NORTH, 2) == 3);
////    assert(ross.beans(NORTH, 3) == 3);
////
////    Board chad(6, 4);
////    chad.setBeans(SOUTH, 5, 10);
////    chad.sow(SOUTH, 5, es, eh);
////    assert(chad.beans(NORTH, 2) == 5);
////    assert(chad.beans(SOUTH, POT) == 1);
////    assert(chad.beans(NORTH, POT) == 0);
//}
//int main()
//{
//    doBoardTests();
//    cout << "Passed all tests" << endl;
//}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// BOARD TEST CASES //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//#include "Player.h"
//#include "Board.h"
//#include "Side.h"
//
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//void doPlayerTests()
//{
////        HumanPlayer hp("Marge");
////        assert(hp.name() == "Marge"  &&  hp.isInteractive());
////        BadPlayer bp("Homer");
////        assert(bp.name() == "Homer"  &&  !bp.isInteractive());
////        SmartPlayer sp("Lisa");
////        assert(sp.name() == "Lisa"  &&  !sp.isInteractive());
////        Board b(3, 2);
////        b.setBeans(SOUTH, 2, 0);
////        cout << "=========" << endl;
////        int n = hp.chooseMove(b, SOUTH);
////        cout << "=========" << endl;
////        assert(n == 1  ||  n == 3);
////        n = bp.chooseMove(b, SOUTH);
////        assert(n == 1  ||  n == 3);
////        n = sp.chooseMove(b, SOUTH);
////        assert(n == 1  ||  n == 3);
//
//    HumanPlayer hp("ME");
//    assert(hp.name() == "ME"  &&  hp.isInteractive());
//    BadPlayer bp("DUMMY");
//    assert(bp.name() == "DUMMY"  &&  !bp.isInteractive());
//    SmartPlayer sp("GENIUS");
//    assert(sp.name() == "GENIUS"  &&  !sp.isInteractive());
//
//
//    Board b(6, 4);
//    b.setBeans(SOUTH, 5, 0);
//    b.setBeans(NORTH, 3, 0);
//
//// HumanPlayer test (make sure it only chooses possible move and reprompts)
//    int n = hp.chooseMove(b, SOUTH);
//    assert(n == 1  ||  n == 2 || n == 3 || n == 4 || n == 6);
//
//// BadPlayer test (make sure it only chooses possible moves)
//    n = bp.chooseMove(b, NORTH);
//    assert(n == 1  ||  n == 2 || n == 4 || n == 5 || n == 6);
//
//// Smartplayer test (make sure it only choose possible moves and additional move if possible)
//    n = sp.chooseMove(b, NORTH);
//    assert(n == 4);
//}
//
//int main()
//{
//    doPlayerTests();
//    cout << "Passed all tests" << endl;
//}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////// PLAYER TEST CASES //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//
//#include "Game.h"
//#include "Player.h"
//#include "Board.h"
//#include "Side.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//void doGameTests()
//{
//    BadPlayer bp1("Bart");
//    BadPlayer bp2("Homer");
//    Board b(3, 0);
//    b.setBeans(SOUTH, 1, 2);
//    b.setBeans(NORTH, 2, 1);
//    b.setBeans(NORTH, 3, 2);
//    Game g(b, &bp1, &bp2);
//    bool over;
//    bool hasWinner;
//    Side winner;
//      //    Homer
//      //   0  1  2
//      // 0         0
//      //   2  0  0
//      //    Bart
//    g.status(over, hasWinner, winner);
//    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 0 &&
//    g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 2 &&
//    g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
//
//    g.move(SOUTH);
//      //   0  1  0
//      // 0         3
//      //   0  1  0
//    g.status(over, hasWinner, winner);
//    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
//    g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 0 &&
//    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);
//
//    g.move(NORTH);
//      //   1  0  0
//      // 0         3
//      //   0  1  0
//    g.status(over, hasWinner, winner);
//    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
//    g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
//    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);
//
//    g.move(SOUTH);
//      //   1  0  0
//      // 0         3
//      //   0  0  1
//    g.status(over, hasWinner, winner);
//    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
//    g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
//    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 1);
//
//    g.move(NORTH);
//      //   0  0  0
//      // 1         4
//      //   0  0  0
//    g.status(over, hasWinner, winner);
//    assert(over && g.beans(NORTH, POT) == 1 && g.beans(SOUTH, POT) == 4 &&
//    g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
//    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
//    assert(hasWinner && winner == SOUTH);

//}
//
//int main()
//{
//    doGameTests();
//    cout << "Passed all tests" << endl;
//}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// GAME TEST CASES //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//#include "Game.h"
//#include "Player.h"
//#include "Board.h"
//#include "Side.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//int main()
//{
//    HumanPlayer hp1("AYAAN");
//    HumanPlayer hp2("MAX");
//    Board b(3, 2);
//    Game g(b, &hp1, &hp2);
//    g.play();
//}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 2 HUMAN PLAYERS  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#include "Game.h"
#include "Player.h"
#include "Board.h"
#include "Side.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    BadPlayer bp1("BOT");
    HumanPlayer hp2("MAX");
    Board b(3, 2);
    Game g(b, &bp1, &hp2);
    g.play();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 1 HUMAN vs 1 BAD BOT  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//#include "Game.h"
//#include "Player.h"
//#include "Board.h"
//#include "Side.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//int main()
//{
//    BadPlayer bp1("Bart");
//    BadPlayer bp2("Homer");
//    Board b(3, 2);
//    Game g(b, &bp1, &bp2);
//    g.play();
//}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  2 BAD PLAYERS  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//#include "Game.h"
//#include "Player.h"
//#include "Board.h"
//#include "Side.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//int main()
//{
//    SmartPlayer sp("SMARTBOT");
//    BadPlayer bp("DUMBBOT");
//    Board b(6, 4);
//    Game g(b, &bp, &sp);
//    g.play();
//}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  1 SMART VS 1 BAD PLAYER //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//#include "Game.h"
//#include "Player.h"
//#include "Board.h"
//#include "Side.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//int main()
//{
//    SmartPlayer sp1("GENIUS 1");
//    SmartPlayer sp2("GENIUS 2");
//    Board b(6, 3);
//    Game g(b, &sp1, &sp2);
//    g.play();
//}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  1 SMART VS 1 SMART PLAYER //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//#include "Game.h"
//#include "Player.h"
//#include "Board.h"
//#include "Side.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//int main()
//{
//    HumanPlayer hp("MAX");
//    SmartPlayer sp("GENIUS 1");
//    Board b(3, 3);
//    Game g(b, &hp, &sp);
//    g.play();
//}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 1 HUMAN vs 1 SMART BOT  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
