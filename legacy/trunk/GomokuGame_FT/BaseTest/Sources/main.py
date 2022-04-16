###############################################################################
# @file GomokuGameContest.py
#
# @details Contest of Computer-Computer game to get GomokuGame.exe statistics.
#
# @if REVISION_HISTORY_INCLUDED
# @par Edit History
# @li zhalat  20-JAN-2017 Initial revision.             
# @endif
#
# @ingroup.
#
# @par non-Copyright (c) 2017 HalSoft
###############################################################################

#SYSTEM IMPORTS
import subprocess
import string
import re
from statemachine import StateMachine
import time

# Usefull definitions.
TERMINATOR_MSG          = "##"
WINNER_MSG              = "--->>Game over. You won."
LOOSER_MSG              = "--->>Game over. Computer won."
STALEMATE_MSG           = "--->>Game over. Stalemate."
CHOOSING_COLOR_MSG      = "--->>Choose your color: x or o."
YOUR_MOVE_MSG           = "--->>Your move:"
LAST_MOVE_MSG           = "--->>Last move:"
LAST_CPU_MOVE_MSG       = "--->>Last cpu move:"
LAST_HUMAN_MOVE_MSG     = "--->>Last human move:"
INVALID_MOVE_MSG        = "!--->>Invalid move."
INVALID_PARAMETER_MSG   = "!--->>Invalid parameter."

RE_ONLY_NUMBERS         = r'\d+'
EMPTY_LINE              = r''
NEW_LINE                = r'\r\n'

global LastWhiteMove
global LastBlackMove
global WhoNextMove

global WhiteWonStatistics
global BlackWonStatistics 
global StalemateStatistics

###############################################################################
#  METHOD NAME: GetMessage
#
# @par Full Description
# Gets message from stdout stream.
#
# @param pipe Pipe to read from.
###############################################################################
def GetMessage( pipe ):
    stdout = []
    while True:
        line = pipe.stdout.readline()
        stdout.append( line )
        if "##" in line: # or pipe.poll() != None:
            return stdout

###############################################################################
#  METHOD NAME: SkipMessage
#
# @par Full Description
# Retreive non important msg form pipe and throw i to thrash.
#
# @param pipe Pipe to read from.
###############################################################################
def ShowBoard( pipe ):
    boardStateList = GetMessage( pipe )
    stdout = []
    for el in boardStateList:
        #Remove new line form string, python's print adds it automatically.
        el = re.sub( NEW_LINE, EMPTY_LINE, el )
        print el
        stdout.append( el )
    return stdout
        
###############################################################################
#  METHOD NAME: GetLastMove
#
# @par Full Description
# Gets last move that has been put on the board.
#
# @param messageList Message received from the pipe.
###############################################################################
def GetLastMove( messageList, msgToFind ):
    index = 0
    for el in messageList:
        if el.find( msgToFind ) != -1:
            break
        else:
            index = index + 1
    try:
        lastMove = messageList[index+1]
        return re.findall( RE_ONLY_NUMBERS, str( lastMove ) )
    except:
        return None

###############################################################################
#  METHOD NAME: WaitForHumanMove
#
# @par Full Description
# Retreive non important msg form pipe and throw i to thrash unitl gets message
# HUMAN_MOVE_MSG
#
# @param pipe Pipe to read from.
###############################################################################
def WaitMove( pipe ):
    isContinue = True
    while isContinue:
        messageList = GetMessage( pipe )
        for el in messageList:
            if el.find( YOUR_MOVE_MSG ) != -1:
                isContinue = False
                break
    return None

###############################################################################
#  METHOD NAME: CheckWiner.
#
# @par Full Description
# Check if there is a winner.
#
# @param messageList Message received from the pipe.
###############################################################################
def CheckWiner( messageList ):
    for el in messageList:
        if el.find(WINNER_MSG) != -1:
            return WINNER_MSG
        elif el.find(LOOSER_MSG) != -1:
            return LOOSER_MSG
        elif el.find(STALEMATE_MSG) != -1:
            return STALEMATE_MSG
    return None

###############################################################################
#  METHOD NAME: State machine transistions
#
# @par Full Description
# Set of methods which define each state of gomoku game contest 
#
###############################################################################
def StartTrans():
    #First message is empty board. Skip it.
    GetMessage( pipeWhite )
    return ('GET_WHITE_MOVE', None )

def GetWhiteMoveTrans():
    global LastWhiteMove
    msgList = GetMessage( pipeWhite )    
    LastWhiteMove = GetLastMove( msgList, LAST_CPU_MOVE_MSG )
    return ('PUT_WHITE_MOVE_ON_BLACK_BOARD', None)

def PutWhiteMoveOnBlackBoardTrans():
    global LastWhiteMove
    global WhoNextMove
    WaitMove( pipeBlack )
    moveX = str( LastWhiteMove[0] )
    moveY = str( LastWhiteMove[1] )
    
    pipeBlack.stdin.write( moveX )
    pipeBlack.stdin.write( '\n' )
    pipeBlack.stdin.write( moveY )
    pipeBlack.stdin.write( '\n' )
    
    WhoNextMove = 'white'
    return ('GET_BLACK_MOVE', 'CHECK_WINNER')

def GetBlackMoveTrans():
    global LastBlackMove
    msgList = GetMessage( pipeBlack )
    LastBlackMove = GetLastMove( msgList, LAST_CPU_MOVE_MSG )
    return ('PUT_BLACK_MOVE_ON_WHITE_BOARD', None)

def PutBlackMoveOnWhiteBoardTrans():
    global LastBlackMove
    global WhoNextMove
    WaitMove( pipeWhite )
    moveX = str( LastBlackMove[0] )
    moveY = str( LastBlackMove[1] )
    
    pipeWhite.stdin.write( moveX )
    pipeWhite.stdin.write( '\n' )
    pipeWhite.stdin.write( moveY )
    pipeWhite.stdin.write( '\n' )

    WhoNextMove = 'black'
    return ('GET_WHITE_MOVE', 'CHECK_WINNER')

def CheckWinnerTrans():
    global WhiteWonStatistics
    global BlackWonStatistics 
    global StalemateStatistics
    
    Winner = None
    if WhoNextMove is 'white':
        boardState = ShowBoard( pipeBlack )
        result = CheckWiner( boardState )
        if result is WINNER_MSG:
            WhiteWonStatistics +=1 
            Winner = 'White'
        elif result is LOOSER_MSG:
            BlackWonStatistics +=1
            Winner = 'Black'
        elif result is STALEMATE_MSG:
            StalemateStatistics +=1
            Winner = 'Stalemate'
            
    elif WhoNextMove is 'black':
        boardState = ShowBoard( pipeWhite )
        result = CheckWiner( boardState )
        if result is WINNER_MSG:
            BlackWonStatistics +=1
            Winner = 'Black'
        elif result is LOOSER_MSG:
            WhiteWonStatistics +=1
            Winner = 'White'
        elif result is STALEMATE_MSG:
            StalemateStatistics +=1
            Winner = 'Stalemate'
    
    if Winner is None:
        time.sleep(.250)
        return( None, None )
    else:
        print "============="
        print  'Winner:' + Winner
        print "============="
        return ('END', None)
    
###############################################################################
# 
#  MAIN()
#
###############################################################################
if __name__ == "__main__":
    
    print '--->>GAME_START'
    #------------------------------------------------------------------------
    WhiteWonStatistics = 0
    BlackWonStatistics = 0
    StalemateStatistics= 0
    
    for el in range(0,30):
        gmokuContestSM = StateMachine()
        LastMove = None
        
        #Make connection with exec. 
        # Args: 
        # 1. Size of board
        # 2. Human color
        # 3. Level: [LEVEL_NONE = 0, BEGINNER = 1, INTERMEDIATE = 2, ADVANCED = 3]
        # 4. Randomize: [0 - randomize disabeld, 1 - randomize enabled ] 
        # 5. MaxTime (s). 0 - not specified
        #pipeWhite = subprocess.Popen( ['GomokuWhite.exe', '15', 'o', '3', '0'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE )
        pipeWhite = subprocess.Popen( ['GomokuWhite.exe', '15', 'o', '3', '1', '0'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE )
        pipeBlack = subprocess.Popen( ['GomokuBlack.exe', '15', 'x', '3', '1', '0'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE )
        #pipeBlack = subprocess.Popen( ['GomokuBlack.exe', '15', 'x', '3', '0'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE )
            
        #Add transitions to state machine.
        gmokuContestSM.AddState( 'START', StartTrans )
        gmokuContestSM.AddState( 'GET_WHITE_MOVE', GetWhiteMoveTrans )
        gmokuContestSM.AddState( 'PUT_WHITE_MOVE_ON_BLACK_BOARD', PutWhiteMoveOnBlackBoardTrans )
        gmokuContestSM.AddState( 'GET_BLACK_MOVE', GetBlackMoveTrans )
        gmokuContestSM.AddState( 'PUT_BLACK_MOVE_ON_WHITE_BOARD', PutBlackMoveOnWhiteBoardTrans )
        gmokuContestSM.AddState( 'CHECK_WINNER', CheckWinnerTrans )
        gmokuContestSM.AddState( 'GET_WHITE_MOVE', GetWhiteMoveTrans )
        gmokuContestSM.AddState( 'END', None, 1 ) # set end transition. Not reachable.
        gmokuContestSM.SetStart( 'START' ) # set start transition
        
    
        gmokuContestSM.Run()
        #pipeWhite.close()
        #pipeWhite.close()
        print '[ ' + str(el) + ':' + 'white-won: ' + str(WhiteWonStatistics) + ' ]'  
        time.sleep(5)
    
    #------------------------------------------------------------------------
    print "================================================================="
    print   'WhiteWonStatistics:' + str(WhiteWonStatistics)
    print   'BlackWonStatistics:' + str(BlackWonStatistics)
    print   'StalemateStatistics:' + str(StalemateStatistics)
    try:
        print   'White Won[%]:' + str(100 * WhiteWonStatistics/(BlackWonStatistics+WhiteWonStatistics))
    except:
        print   'White Won[%]: 0'
        
    print "================================================================="
    print '--->>GAME_END'

###############################################################################
#http://eyalarubas.com/python-subproc-nonblock.html