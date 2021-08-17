4194303 THREAT_WINNER XXXXX

    100000 THREAT_4_CASE_A.XXXX .30000 THREAT_4_CASE_C OXXX.XO /
    OXX.XXO / OX.XXXO /
    O.XXXXO  // powinno byc .XXX.X / .XX.XX /.X.XXX / XXX.X. / XX.XX. / X.XXX.
    20000 THREAT_4_CASE_B OX.XXX /
    OXX.XX / OXXX.X / OXXXX./.XXXXO / X.XXXO / XX.XXO /
    XXX.XO

    2000 THREAT_3_CASE_A..XXX./
        .X.XX./.XX.X./.XXX..1500 THREAT_3_CASE_C.XXX./ X.X.X / X..XX / XX..X 1000 THREAT_3_CASE_B OXXX../ OXX.X./
    OX.XX./..XXXO /.X.XXO /
        .XX.XO !!brak OX..XX I OXX.
        .X

        200 THREAT_2_CASE_A.XX... /
        .X.X../.X..X./..XX../..X.X./ ... XX .150 THREAT_2_CASE_C.XX../.X.X./..XX .50 THREAT_2_CASE_B OXX... / OX.X../
    OX..X./ ... XXO /..X.XO /
        .X..XO

        {ThreatFinder::THREAT_WINNER, (new ThreatWinner()), THREAT_WINNER_SCORE},
    {ThreatFinder::THREAT_4_CASE_A, (new Threat4CaseA()), THREAT_4_CASE_A_SCORE},
    {ThreatFinder::THREAT_4_CASE_C, (new Threat4CaseC()), THREAT_4_CASE_C_SCORE},
    {ThreatFinder::THREAT_4_CASE_B, (new Threat4CaseB()), THREAT_4_CASE_B_SCORE},
    {ThreatFinder::THREAT_3_CASE_A, (new Threat3CaseA()), THREAT_3_CASE_A_SCORE},
    {ThreatFinder::THREAT_3_CASE_C, (new Threat3CaseC()), THREAT_3_CASE_C_SCORE},
    {ThreatFinder::THREAT_3_CASE_B, (new Threat3CaseB()), THREAT_3_CASE_B_SCORE},
    {ThreatFinder::THREAT_2_CASE_A, (new Threat2CaseA()), THREAT_2_CASE_A_SCORE},
    {ThreatFinder::THREAT_2_CASE_C, (new Threat2CaseC()), THREAT_2_CASE_C_SCORE},
    {ThreatFinder::THREAT_2_CASE_B, (new Threat2CaseB()), THREAT_2_CASE_B_SCORE},

    DISMISSAL : +ThreatFinder::THREAT_WINNER->x + ThreatFinder::THREAT_4_CASE_A->THREAT_4_CASE_B
    , +ThreatFinder::THREAT_4_CASE_C->THREAT_3_CASE_B
    , THREAT_2_CASE_B + ThreatFinder::THREAT_4_CASE_B->THREAT_3_CASE_B
    , THREAT_2_CASE_B + ThreatFinder::THREAT_3_CASE_A->THREAT_3_CASE_A
    , THREAT_3_CASE_B
    , THREAT_3_CASE_C
    , THREAT_2_CASE_B + ThreatFinder::THREAT_3_CASE_C->THREAT_2_CASE_B +
          ThreatFinder::THREAT_3_CASE_B->THREAT_2_CASE_B + ThreatFinder::THREAT_2_CASE_A->THREAT_2_CASE_A
    , THREAT_2_CASE_B
    , THREAT_2_CASE_C + ThreatFinder::THREAT_2_CASE_C->x +
          ThreatFinder::THREAT_2_CASE_B
              ->x

                  PROMOTION : +ThreatFinder::THREAT_WINNER->x +
          ThreatFinder::THREAT_4_CASE_A->THREAT_WINNER + ThreatFinder::THREAT_4_CASE_C->THREAT_WINNER +
          ThreatFinder::THREAT_4_CASE_B->THREAT_WINNER + ThreatFinder::THREAT_3_CASE_A->THREAT_4_CASE_A
    , THREAT_4_CASE_B
    , THREAT_4_CASE_C + ThreatFinder::THREAT_3_CASE_C->THREAT_4_CASE_B
    , THREAT_4_CASE_C + ThreatFinder::THREAT_3_CASE_B->THREAT_4_CASE_B + ThreatFinder::THREAT_2_CASE_A->THREAT_3_CASE_A
    , THREAT_3_CASE_B
    , THREAT_3_CASE_C + ThreatFinder::THREAT_2_CASE_C->THREAT_3_CASE_C
    , THREAT_3_CASE_B + ThreatFinder::THREAT_2_CASE_B->THREAT_3_CASE_B
    , THREAT_3_CASE_C

          THREAT_3_CASE_D.X.X.X..X..XX..XX..X
              .

      THREAT_4_CASE_D.XXX.X..X.XXX..XX.XX..X.XXX.
