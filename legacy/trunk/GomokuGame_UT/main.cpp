//============================================================================
// Name        : GomokuGame.cpp
// Author      : zhalat
// Version     : 001 - start at 04-01-2015
// Version     :
// Version     :
// Copyright   : Your copyright notice
// Description : Gomoku game tests
//============================================================================

#include <iostream>

#ifdef VECTORUNIQUE_TEST
#include "VectorUniqueTest.hpp"
int main() {

using namespace std;

#ifdef UNIT_TEST
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( VectorUniqueTest::suite() );

    cout<<"Testing start:.."<<endl;
    runner.run();
    cout<<"Testing end:.."<<endl;
#endif

    return 0;
}
#endif

#ifdef STATE_EVALUATION_TEST
#include "StateEvaluationTest.hpp"
int main() {

using namespace std;

#ifdef UNIT_TEST
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( StateEvaluationTest::suite() );

    cout<<"Testing start:.."<<endl;
    runner.run();
    cout<<"Testing end:.."<<endl;
#endif

    return 0;
}
#endif

#ifdef OPEN_BOOK_TEST
#include "OpenBookTest.hpp"
int main() {

using namespace std;

#ifdef UNIT_TEST
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( OpenBookTest::suite() );

    cout<<"Testing start:.."<<endl;
    runner.run();
    cout<<"Testing end:.."<<endl;
#endif

    return 0;
}
#endif

#ifdef BOARDSCORE_TEST
#include "BoardScoreTest.hpp"
int main() {

using namespace std;

#ifdef UNIT_TEST
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( BoardScoreTest::suite() );

    cout<<"Testing start:.."<<endl;
    runner.run();
    cout<<"Testing end:.."<<endl;
#endif

    return 0;
}
#endif

#ifdef SPOTTER_TEST
#include "SpotterTest.hpp"
int main() {

using namespace std;

#ifdef UNIT_TEST
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( SpotterTest::suite() );

    cout<<"Testing start:.."<<endl;
    runner.run();
    cout<<"Testing end:.."<<endl;
#endif

    return 0;
}
#endif

#ifdef SINGLELIST_TEST
#include "SingleListTest.hpp"
int main() {

using namespace std;

#ifdef UNIT_TEST
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( SingleListTest::suite() );

    cout<<"Testing start:.."<<endl;
    runner.run();
    cout<<"Testing end:.."<<endl;
#endif

    return 0;
}
#endif

#ifdef VECTORLIGHT_TEST
#include "VectorLightTest.hpp"
int main() {

using namespace std;

#ifdef UNIT_TEST
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( VectorLightTest::suite() );

    cout<<"Testing start:.."<<endl;
    runner.run();
    cout<<"Testing end:.."<<endl;
#endif

    return 0;
}
#endif

#ifdef GOMOKUGAMEUI_TEST
#include "GomokuGameTest.hpp"
int main() {

using namespace std;

#ifdef UNIT_TEST
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( GomokuGameTest::suite() );

    cout<<"Testing start:.."<<endl;
    runner.run();
    cout<<"Testing end:.."<<endl;
#endif

    return 0;
}
#endif

#ifdef ALPHA_BETA_TEST
#include "AlphaBetaTest.hpp"
int main() {

using namespace std;

#ifdef UNIT_TEST
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( AlphaBetaTest::suite() );

    cout<<"Testing start:.."<<endl;
    runner.run();
    cout<<"Testing end:.."<<endl;
#endif

    return 0;
}
#endif

#ifdef MINMAX_TEST
#include "MinMaxTest.hpp"
int main() {

using namespace std;

#ifdef UNIT_TEST
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( MinMaxTest::suite() );

    cout<<"Testing start:.."<<endl;
    runner.run();
    cout<<"Testing end:.."<<endl;
#endif

    return 0;
}
#endif

#ifdef SCORE_TEST
#include "ScoreTest.hpp"
int main() {

using namespace std;

#ifdef UNIT_TEST
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( ScoreTest::suite() );

    cout<<"Testing start:.."<<endl;
    runner.run();
    cout<<"Testing end:.."<<endl;
#endif

    return 0;
}
#endif

#ifdef THREAT_WINNER_TEST
#include "ThreatWinnerTest.hpp"
int main() {

using namespace std;

#ifdef UNIT_TEST
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( ThreatWinnerTest::suite() );

    cout<<"Testing start:.."<<endl;
    runner.run();
    cout<<"Testing end:.."<<endl;
#endif

    return 0;
}
#endif

#ifdef THREAT_2_CASE_C_TEST
#include "Threat2CaseCTest.hpp"
int main() {

using namespace std;

#ifdef UNIT_TEST
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( Threat2CaseCTest::suite() );

    cout<<"Testing start:.."<<endl;
    runner.run();
    cout<<"Testing end:.."<<endl;
#endif

    return 0;
}
#endif

#ifdef THREAT_2_CASE_B_TEST
#include "Threat2CaseBTest.hpp"
int main() {

using namespace std;

#ifdef UNIT_TEST
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( Threat2CaseBTest::suite() );

    cout<<"Testing start:.."<<endl;
    runner.run();
    cout<<"Testing end:.."<<endl;
#endif

    return 0;
}
#endif

#ifdef THREAT_2_CASE_AA_TEST
#include "Threat2CaseAATest.hpp"
int main() {

using namespace std;

#ifdef UNIT_TEST
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( Threat2CaseAATest::suite() );

    cout<<"Testing start:.."<<endl;
    runner.run();
    cout<<"Testing end:.."<<endl;
#endif

    return 0;
}
#endif

#ifdef THREAT_2_CASE_A_TEST
#include "Threat2CaseATest.hpp"
int main() {

using namespace std;

#ifdef UNIT_TEST
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( Threat2CaseATest::suite() );

    cout<<"Testing start:.."<<endl;
    runner.run();
    cout<<"Testing end:.."<<endl;
#endif

    return 0;
}
#endif

#ifdef THREAT_3_CASE_C_TEST
#include "Threat3CaseCTest.hpp"
int main() {

using namespace std;

#ifdef UNIT_TEST
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( Threat3CaseCTest::suite() );

    cout<<"Testing start:.."<<endl;
    runner.run();
    cout<<"Testing end:.."<<endl;
#endif

    return 0;
}
#endif

#ifdef THREAT_3_CASE_B_TEST
#include "Threat3CaseBTest.hpp"
int main() {

using namespace std;

#ifdef UNIT_TEST
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( Threat3CaseBTest::suite() );

    cout<<"Testing start:.."<<endl;
    runner.run();
    cout<<"Testing end:.."<<endl;
#endif

    return 0;
}
#endif

#ifdef THREAT_3_CASE_AA_TEST
#include "Threat3CaseAATest.hpp"
int main() {

using namespace std;

#ifdef UNIT_TEST
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( Threat3CaseAATest::suite() );

    cout<<"Testing start:.."<<endl;
    runner.run();
    cout<<"Testing end:.."<<endl;
#endif

    return 0;
}
#endif

#ifdef THREAT_3_CASE_A_TEST
#include "Threat3CaseATest.hpp"
int main() {

using namespace std;

#ifdef UNIT_TEST
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( Threat3CaseATest::suite() );

    cout<<"Testing start:.."<<endl;
    runner.run();
    cout<<"Testing end:.."<<endl;
#endif

    return 0;
}
#endif

#ifdef THREAT_FOUR_CASE_AA_TEST
#include "Threat4CaseAATest.hpp"
int main() {

using namespace std;

#ifdef UNIT_TEST
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( Threat4CaseAATest::suite() );

    cout<<"Testing start:.."<<endl;
    runner.run();
    cout<<"Testing end:.."<<endl;
#endif

    return 0;
}
#endif

#ifdef THREAT_FOUR_CASE_A_TEST
#include "Threat4CaseATest.hpp"
int main() {

using namespace std;

#ifdef UNIT_TEST
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( Threat4CaseATest::suite() );

    cout<<"Testing start:.."<<endl;
    runner.run();
    cout<<"Testing end:.."<<endl;
#endif

    return 0;
}
#endif

#ifdef THREAT_FOUR_CASE_C_TEST
#include "Threat4CaseCTest.hpp"
int main() {

using namespace std;

#ifdef UNIT_TEST
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( Threat4CaseCTest::suite() );

    cout<<"Testing start:.."<<endl;
    runner.run();
    cout<<"Testing end:.."<<endl;
#endif

    return 0;
}
#endif

#ifdef THREAT_FOUR_CASE_B_TEST
#include "Threat4CaseBTest.hpp"
int main() {

using namespace std;

#ifdef UNIT_TEST
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( Threat4CaseBTest::suite() );

    cout<<"Testing start:.."<<endl;
    runner.run();
    cout<<"Testing end:.."<<endl;
#endif

    return 0;
}
#endif

#ifdef GOMOKUBOARDTEST
#include "GomokuBoardTest.hpp"
int main() {

using namespace std;

#ifdef UNIT_TEST
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( GomokuBoardTest::suite() );

    cout<<"Testing start:.."<<endl;
    runner.run();
    cout<<"Testing end:.."<<endl;
#endif

    return 0;
}
#endif

#ifdef SINGLELISTTEST
#include "Test_SingleList.hpp"
int main() {

using namespace std;

#ifdef UNIT_TEST
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( Test_SingleList::suite() );

    cout<<"Testing start:.."<<endl;
    runner.run();
    cout<<"Testing end:.."<<endl;
#endif

    return 0;
}
#endif
