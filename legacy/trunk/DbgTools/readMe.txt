Draws game tree useful while debbuging MimMax algorythm.

Needs data input:
TREE_RECORD              = "MinMaxTreeRecord.txt"
BOARD_RECORD             = "MinMaxBoardRecord.txt"
You can get this data by enabling followng flags in MinMax.cpp
static bool PrintBoard1 = false;
static bool LogStart = false;

Be aware that it produce a lot of data, so restrict move - candidates as minimal as posibble or reduce depth.



Output:
FIGURE_OUTPUT_NAME       = "GameTree.html" 