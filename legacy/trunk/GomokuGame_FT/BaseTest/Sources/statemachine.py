class StateMachine:
    def __init__(self):
        self.m_Handlers = {}
        self.m_StartState = None
        self.m_EndStates = []

    def AddState(self, name, handler, endState=0):
        name = name.upper()
        self.m_Handlers[name] = handler
        if endState:
            self.m_EndStates.append(name)

    def SetStart(self, name):
        self.m_StartState = name.upper()

    def Run(self):
        try:
            handler = self.m_Handlers[self.m_StartState]
        except:
            print "Must call SetStart() before .Run()"
            raise IOError
        
        if not self.m_EndStates:
            print "At least one state must be an m_EndStates"
            raise IOError
    
        while True:
            (newState, tempState) = handler()
            
            #Firstly if None, run tempState.
            if tempState is not None:
                tempHandler = self.m_Handlers[tempState.upper()]
                ( state, nonUsedState ) = tempHandler()
                if state is not None and state.upper() in self.m_EndStates:
                    break 
            #Then choose regular state.
            if newState.upper() in self.m_EndStates:
                break 
            else:
                handler = self.m_Handlers[newState.upper()]      