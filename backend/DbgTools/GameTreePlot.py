import re
import queue
import plotly
import chart_studio.plotly as py
import plotly.graph_objs as go
from matplotlib.font_manager import font_family_aliases
#from test.test_bufio import lengths
   
# Usefull definitions.
TREE_RECORD              = "MinMaxTreeRecord.txt"
BOARD_RECORD             = "MinMaxBoardRecord.txt"
FIGURE_OUTPUT_NAME       = "GameTree.html" 
ROW_COLUMN_FORMAT_RE     = "(\d+)+(_)"
LABEL_INDEX_RE           = "(_)+(\d+)"
LABEL_RE                 = "(\d+)+(_)+(\d+)"
MOVE_RE                  = "(\()+(\d+)+(,)+(\d+)+(\))"
SCORE_RE                 = "(\[)+(\-\d+|\d+)+(\])"
LOG_SEPARATOR            = "--"
NEW_LINE_DELIMITER       = "\n" 
HOVER_STYLE              = '''\n
<style type="text/css">
.hovertext text {
    font-size: 10px !important;
    font-family: "Ubuntu Mono", "DejaVu Sans Mono", "Roboto Mono", "Source Code Pro", "Courier New", monospace !important;
}

</style> \n'''


MARKER_SIZE              = 0.2
MARKER_SIZE_SPACING      = (0.1*MARKER_SIZE)
X_MAX                    = 100
Y_MAX                    = 10
DEPTH_MAX                = 6
BORAD_STATE_LINE_NUMBER  = 43

class Point:
    def __init__(self,x_init,y_init):
        self.m_X = x_init
        self.m_Y = y_init
        
    def SetX (self, x):
        self.m_X = x
        
    def SetY (self, y):
        self.m_Y = y

NodeInfo = {'Label': 'none', 'Move': 'none', 'Score': 'none'}

###############################################################################
#  CLASS NAME: Node
#
# @par Full Description
# Represents node in a tree. Keeps it m_X,m_Y location on figure.
#
###############################################################################
class Node:
    def __init__( self, x, y, move, score, label ):
        # Full path to node form root
        self.m_FullPath = []
        # label ex. 1_2
        self.m_Label = label
        # child associate with node
        self.m_Child = []
        # keeps m_X,m_Y location on figure
        self.m_Point = Point( x, y )
        # Move ex. (2,4)
        self.m_Move = move
        # score ex. [2685]
        self.m_Score = score
        
    def SetPoint( self, point ):
        self.m_Point = point
        
    def SetLabel( self, label ):
        self.m_Label = label
    
    def SetChild( self, child ):
        self.m_Child = child
        
    def AddChild( self, child ):
        self.m_Child.append( child )
        
    def SetScore( self, score ):
        self.m_Score = score
    
    def SetPath( self, path ):
        self.m_FullPath = path

###############################################################################
#  CLASS NAME: NodeLocator
#
# @par Full Description
# Provide m_X, location on figure for each vertex. Y location is equal current depth.
# Assumed m_X cordinates takes consequetively
#
###############################################################################
class NodeLocator:
    def __init__( self, treeDepth ):
        
        self.m_Depth = treeDepth
        
        #keep m_X corrdinates for each level;
        # level 0: [ 10, 20, 30 ]
        # level 1: [ 1, 2, 3, 4 ,5, 6, 7 ]
        #                     ^current index see: m_Coordinates[1]
        # etc.
        self.m_Coordinates = []
        
        # Keeps current coordinates to use for each level like:
        # [0]: keeps index for level 0
        # [1]: keeps index for level 1
        # etc.
        self.m_CoordinatesIndex = []
        
        # Initialize m_X coordinates
        for i in range( treeDepth ):
            verticesNo = self.GetNumberOfElements( i )
            markerSlice = float( X_MAX/float( verticesNo ) )
            
            # start index
            self.m_CoordinatesIndex.append( 0 )
            
            x = []
            for i in range( verticesNo ):
                x.append( i*markerSlice + markerSlice/2 )
            self.m_Coordinates.append( x )
            
    def GetCoordinateX(self, level):
        if not level < self.m_Depth:
            raise ValueError( "NodeLocator GetCoordinateX():Invalid input parameter." )
        try:
            index = self.m_CoordinatesIndex[ level ]
            # set to next index for future usegae.
            self.m_CoordinatesIndex[ level ] = index + 1
            
            retVal = self.m_Coordinates[ level ][index]
        except:
            raise ValueError( "NodeLocator GetCoordinateX():Index out of range." )
        
        return retVal
        
    def GetNumberOfElements( self, level ):
        cntr = 0
        hFile = open( TREE_RECORD, 'r' )
        for line in hFile:   
            if re.search( ROW_COLUMN_FORMAT_RE, line ):
                currentDepthExpr = re.search( ROW_COLUMN_FORMAT_RE, line  ).group()
                currentDepth = currentDepthExpr[ :len( currentDepthExpr ) - 1 ]
                currentDepth = strToInt( currentDepth )
                
                if currentDepth == level:
                    cntr = cntr + 1
                    
        hFile.close()
        return cntr

###############################################################################
#  CLASS NAME: Tree
#
# @par Full Description
# Tree connection based on provided MinMaxTreeRecord.txt file. 
#
###############################################################################
class Tree:
    def __init__( self, name ):
        self.m_Name = name
        self.m_Vertices = []
        self.m_MainQ = queue.Queue()
        self.m_TreeBeginLabel = '0_1'
        self.m_CurrentPath = []
        self.m_TreeDepth = self.GetTreeDepth()
        # Provide m_X coordinate for each vertex
        self.m_NodeLocator = NodeLocator( self.m_TreeDepth +1 )

        # Create list of index container class.
        self.m_labelLevel = []
        for i in range( DEPTH_MAX ):
            self.m_labelLevel.append( IndexListContainer( i ) )
            
        if self.m_TreeDepth > DEPTH_MAX:
            raise ValueError( "Tree__init__():Tree too deep." )
            
    def MadeConnections( self ):
        zeroLevelNo = self.GetNumberOfElements( 0 )
        for i in range( zeroLevelNo ):
            label = '0_' + str( i + 1 )
            self.m_MainQ.put( label )
            
        while not self.m_MainQ.empty():
            del self.m_CurrentPath[:]
            self.ProcessQueue()
            
    def ProcessQueue(self):
        label = self.m_MainQ.get()
        labelLevel = self.GetLabelLevel( label )
        
        isNewLevel = self.m_labelLevel[ labelLevel ].IsEmpty()
        self.m_labelLevel[ labelLevel ].PutData( label )
        
        if isNewLevel:
            #Reset parent indexer if going to a new level
            self.SetAncestorToBase( labelLevel - 1 )
        self.AdjustIndex( labelLevel )
        
        # Set current path 
        for i in range( DEPTH_MAX ):
            if not self.m_labelLevel[i].IsEmpty():
                label = self.m_labelLevel[i].GetData()
                self.m_CurrentPath.append( label )
            else:
                break
        
        # Basing on current path, add its children 
        childrenLevel = self.GetLabelLevel( self.m_CurrentPath[ -1 ] ) + 1
        childrenNo = self.GetNumberOfChildrens( self.m_CurrentPath )
        childrenLabels = []
        
        # If there are children add them to queue.
        if childrenNo > 0:
            for i in range( childrenNo ):
                childrenLabel = str( childrenLevel ) + "_" + str( i + 1 )
                #print childrenLabel
                self.m_MainQ.put( childrenLabel )
                childrenLabels.append( childrenLabel )
        
        # Get all info needed to crate vertex node
        xLocation = self.m_NodeLocator.GetCoordinateX( labelLevel )
        yLocation = self.m_TreeDepth - labelLevel
        info = self.GetVertexInfo( self.m_CurrentPath )
        node = Node( xLocation, yLocation, info['Move'], info['Score'], info['Label'] )
        node.m_Child = childrenLabels
        fullNodePath = list(self.m_CurrentPath)
        node.SetPath( fullNodePath ) 

        # Add vertex/node to tree.
        self.m_Vertices.append( node )
                
    def SetAncestorToBase( self, ContainerId ):
        if ContainerId >= 0:
            self.m_labelLevel[ ContainerId ].SetIndexToBase()
            self.SetAncestorToBase( ContainerId - 1 )
    
    def AdjustIndex( self, ContainerId ):
        #print ContainerId
        if not self.m_labelLevel[ ContainerId ].IsDataRise() and ContainerId > 0:
            # index doesnt grow - it means parent changed to next like 1_1 -> 1_2 -> 1_3
            self.m_labelLevel[ ContainerId-1 ].IncrementIndex()
            self.AdjustIndex( ContainerId-1 )
        
    def GetTreeDepth( self ):
        hFile = open( TREE_RECORD, 'r' )
        
        deepest = 0
        # Find depth of leaves.   
        for line in hFile:
            if re.search( ROW_COLUMN_FORMAT_RE, line ):
                depthLeafExpr = re.search( ROW_COLUMN_FORMAT_RE, line  ).group()
                depthLeaf = depthLeafExpr[ :len( depthLeafExpr ) - 1 ]
                depthLeaf = strToInt( depthLeaf )
                
                if depthLeaf > deepest:
                    deepest = depthLeaf
        
        hFile.close()
        return deepest
    
    def GetLabelLevel( self, label ):
        currentDepthExpr = re.search( ROW_COLUMN_FORMAT_RE, label  ).group()
        currentDepth = currentDepthExpr[ :len( currentDepthExpr ) - 1 ]
        currentDepth = strToInt( currentDepth )
        return currentDepth
    
    def GetNumberOfElements( self, level ):
        cntr = 0
        hFile = open( TREE_RECORD, 'r' )
        for line in hFile:   
            if re.search( ROW_COLUMN_FORMAT_RE, line ):
                currentDepthExpr = re.search( ROW_COLUMN_FORMAT_RE, line  ).group()
                currentDepth = currentDepthExpr[ :len( currentDepthExpr ) - 1 ]
                currentDepth = strToInt( currentDepth )
                
                if currentDepth == level:
                    cntr = cntr + 1
                    
        hFile.close()
        return cntr
    
    def FindIndex( self, tag, content ):
        index = 0
        found = False
        
        for el in content:
            if tag in el:
                found = True
                break
            else:
                index = index + 1
        
        if found:
            return index
        else:
            return -1

    def GetVertexInfo( self, path ):
        fileString = open( TREE_RECORD, 'r' ).read()
        fileList = fileString.split( NEW_LINE_DELIMITER )
        
        buffer1 = fileList
        buffer2 = []
        
        vertexIndex = 0
        
        for el in path:
            #check if its' the last 
            if el == path[-1]:
                vertexIndex = self.FindIndex( el, buffer1 )
                break
                
            #Find index of vertex
            downIndex =  self.FindIndex( el, buffer1 ) - 1
            if downIndex < 0:
                # no children found
                return 0
             
            #Copy to the another buffer 
            parentDepthExpr = re.search( ROW_COLUMN_FORMAT_RE, el  ).group()
            parentDepth = parentDepthExpr[ :len( parentDepthExpr ) - 1 ]
            parentDepthInt = strToInt( parentDepth )
            cntr = downIndex
            while True:
                line = buffer1[cntr]
                if line == LOG_SEPARATOR:
                    break
                
                # Copy up to you encounter another level/depth
                depthExpr = re.search( ROW_COLUMN_FORMAT_RE, line  ).group()
                depth = depthExpr[ :len( depthExpr ) - 1 ]
                
                try:
                    depth = strToInt( depth )
                    if not (depth > parentDepthInt):
                        break
                except:
                    break
                # Insert line to front of the list
                buffer2.insert( 0, line )
                cntr = cntr - 1 
                
            buffer1 = buffer2
            buffer2 = []
            
        vertexData = buffer1[vertexIndex]
        
        vertexInfo = NodeInfo
        
        vertexInfo['Label'] = re.search( LABEL_RE, vertexData  ).group()
        vertexInfo['Move'] = re.search( MOVE_RE, vertexData  ).group()
        vertexInfo['Score'] = re.search( SCORE_RE, vertexData  ).group()
        
        return vertexInfo

    def GetVertexXY( self, path ):
        point = Point(-1,-1)
        
        # finds thru all self.m_Vertices and return its Point location x y 
        for node in self.m_Vertices:
            if node.m_FullPath == path:
                point = node.m_Point
                
        return point

    def GetNumberOfChildrens( self, vertexLabel ):
        fileString = open( TREE_RECORD, 'r' ).read()
        fileList = fileString.split( NEW_LINE_DELIMITER )
        
        buffer1 = fileList
        buffer2 = []
        
        for el in vertexLabel:
            #Find index of vertex
            downIndex =  self.FindIndex( el, buffer1 ) - 1
            if downIndex < 0:
                # no children found
                return 0
             
            #Copy to the another buffer 
            parentDepthExpr = re.search( ROW_COLUMN_FORMAT_RE, el  ).group()
            parentDepth = parentDepthExpr[ :len( parentDepthExpr ) - 1 ]
            parentDepthInt = strToInt( parentDepth )
            cntr = downIndex
            while True:
                line = buffer1[cntr]
                if line == LOG_SEPARATOR:
                    break
                
                # Copy up to you encounter another level/depth
                depthExpr = re.search( ROW_COLUMN_FORMAT_RE, line  ).group()
                depth = depthExpr[ :len( depthExpr ) - 1 ]
                
                try:
                    depth = strToInt( depth )
                    if not (depth > parentDepthInt):
                        break
                except:
                    break
                # Insert line to front of the list
                buffer2.insert( 0, line )
                cntr = cntr - 1 
                
            buffer1 = buffer2
            buffer2 = []
        
        # Find out parent depth. ex ['0_2' '1_1' '2_3'] parent is 2
        parentDepth = vertexLabel[-1]
        parentDepthExpr = re.search( ROW_COLUMN_FORMAT_RE, parentDepth  ).group()
        parentDepth = parentDepthExpr[ :len( parentDepthExpr ) - 1 ]
        parentDepthInt = strToInt( parentDepth )
        
        childrenDepthInt = parentDepthInt + 1
        
        # Count children
        childCntr = 0
        for el in buffer1:
            expr = re.search( ROW_COLUMN_FORMAT_RE, el  ).group()
            exprDepth = expr[ :len( expr ) - 1 ]
            exprDepthInt = strToInt( exprDepth )
            
            if exprDepthInt == childrenDepthInt:
                childCntr = childCntr + 1
        
        return childCntr
    
    # Get board state associated with provided path. See file MinMaxBoardRecord.txt
    def GetBoardState( self, path ):
        fileString = open( BOARD_RECORD, 'r' ).read()
        fileList = fileString.split( NEW_LINE_DELIMITER )
        
        buffer1 = fileList
        buffer2 = []
        
        for el in path:
            #Find index of vertex
            index =  self.FindIndex( el, buffer1 )
            if index < 0:
                raise ValueError( "TreeGetBoardState():Path doesn't exist" )
            
            # If we reach the end of path copy the data below. It is what we want. If not copy up- up to reach data of our neighbour 
            # ex. 0_1 is neighbour of 0_2 and vice versa (the same level)
            copyDataUp = True
            if el == path[-1]:
                copyDataUp = False
                index = index + 1
            else:
                index = index - 1 
                
            # Extract current depth level.
            parentDepthExpr = re.search( ROW_COLUMN_FORMAT_RE, el  ).group()
            parentDepth = parentDepthExpr[ :len( parentDepthExpr ) - 1 ]
            
            # Starting point.
            cntr = index            
            if copyDataUp:
                # copy data up.
                while True:
                    # Copy up to you encounter another level/depth or Log separator. 0_, ect 
                    onExitLabel = parentDepth + '_'
                    
                    line = buffer1[cntr]
                    if line == LOG_SEPARATOR or onExitLabel in line :
                        break
                    
                    # Insert line to front of the list
                    buffer2.insert( 0, line )
                    cntr = cntr - 1 
            else:
                lineLimit = cntr + BORAD_STATE_LINE_NUMBER
                # copy data down.
                while cntr < lineLimit:
                    # Insert line to front of the list
                    line = buffer1[cntr]
                    buffer2.insert( 0, line )
                    cntr = cntr + 1 
                buffer2.reverse()
                retVal = list( buffer2 )
                return retVal
                    
            buffer1 = buffer2
            buffer2 = []

###############################################################################
#  CLASS NAME: IndexListContainer
#
# @par Full Description
# Helper container for tree cration. 
#
###############################################################################
class IndexListContainer:
    def __init__(self, id):
        self.m_Id = id
        self.m_Array = []
        self.m_CurrentIndex = 0
        
    def SetIndexToBase(self):
        self.m_CurrentIndex = 0
    
    def PutData(self, data):
        self.m_Array.append( data )
        self.m_CurrentIndex = len( self.m_Array ) - 1
    
    def GetData(self):
        if  self.m_CurrentIndex < 0:
            raise ValueError( "IndexListContainer::GetData():Invalid index." )
        return self.m_Array[self.m_CurrentIndex]
    
    def IncrementIndex(self):
        self.m_CurrentIndex = self.m_CurrentIndex + 1
        
    def ClearContainer(self):
        self.SetIndexToBase()
        del self.m_Array[:]
        
    def IsEmpty(self):
        if not self.m_Array:
            return True
        else:
            return False
        
    def GetId(self):
        return self.m_Id
    
    def GetLabelIndex( self, label ):
        currentIndexExpr = re.search( LABEL_INDEX_RE, label  ).group()
        currentIndex = currentIndexExpr[ 1:len( currentIndexExpr ) ]
        currentIndex = strToInt( currentIndex )
        return currentIndex
    
    def IsDataRise(self):
        retVal = True
        if (self.m_CurrentIndex ) > 1:
            # if there is no raising data
            lastElement = self.m_Array[ self.m_CurrentIndex ]
            beforeLastElement = self.m_Array[ self.m_CurrentIndex - 1 ]
            
            lastElement = self.GetLabelIndex( lastElement )
            beforeLastElement = self.GetLabelIndex( beforeLastElement )
            
            if lastElement - beforeLastElement != 1:
                retVal = False
        return retVal

###############################################################################
#  METHOD NAME: strToInt
#
# @par Full Description
# Convert string to int. 
#
# @retval Intiger value.
###############################################################################
def strToInt( strVal ):
    try:
        return int( strVal )
    except: 
        ValueError( "strToInt():: can't convert string to int" )
        
###############################################################################
#  METHOD NAME: SetHoverStyle
#
# @par Full Description
# Because plotly does not support setting font style for hover
# it must be done by css style  after html is generated.
###############################################################################        
def SetHoverStyle():
    try:
        # it should be added inside 
        hFile = open( FIGURE_OUTPUT_NAME, 'a' )
        hFile.seek(0)
        hFile.write( HOVER_STYLE )
    except: 
        ValueError( "SetHoverStyle():: can't find file:" +  FIGURE_OUTPUT_NAME )

###############################################################################
# 
#  MAIN()
#
###############################################################################
if __name__ == "__main__":
    
    #======== CREATE TREE: ==========:  
    
    tree = Tree( "Game Tree" )
    tree.MadeConnections()
 
    #======== VERTICES DEPLOY: ==========:  
 
    # Make a Xn, Yn vectrs to locate each tree vertices.
    Xn = []
    Yn = []
    # Make a Xe, Ye vectrs to locate each tree vertices.
    Xe = []
    Ye = []
    # Vertex description location x y, and vertex information showed in the center of node.
    VertexInfoPosition = {}
    VertexInfoText = {}
    # Text shown when hoover mouse on the vertex.
    HoverText = []
     
    cntr1 = 0
    for el in tree.m_Vertices:
        # Create xy locaton vector
        x = el.m_Point.m_X
        y = el.m_Point.m_Y
        Xn.append( x )
        Yn.append( y )
         
        infoText = el.m_Score + "<br>" + el.m_Move
        VertexInfoPosition[ cntr1 ] =  [ x, y ]
        VertexInfoText[ cntr1 ]= infoText  
        
        # Hover text.
        hoverTextList = tree.GetBoardState( el.m_FullPath ) 
        fullPathStr = '<br> Full path: ' + '--'.join( el.m_FullPath )
        hoverTextList.append( fullPathStr )
        hoverText =  '<br>'.join( hoverTextList )
        HoverText.append( hoverText ) 
         
        # Create line vector
        for el_child in el.m_Child:
            fullPathChild = list(el.m_FullPath)
            fullPathChild.append(el_child)
             
            point = tree.GetVertexXY( fullPathChild )
            #parent xy
            Xe.append( x )
            Ye.append( y )
            #children xy
            Xe.append( point.m_X )
            Ye.append( point.m_Y )
            #line type
            Xe.append( None )
            Ye.append( None )
         
        cntr1 = cntr1 + 1
#         if cntr1 == 5:
#             break
    
    #======== CREATE PLOTLY LAYOUT: ==========:  
     
    # Vertices marker. Text can be added and shown when hoover a mouse (see text list below).
    dots = go.Scatter( x = Xn,
                       y = Yn,
                       mode = 'markers',
                       name = '',
                       marker = dict( symbol = 'square-dot', size = 36, color = '#6175c1', line = dict( color = 'rgb(50,50,50)', width = 1 ) ),
                       text = HoverText,
                       textfont = dict( family = 'Consolas', size = 18, color = '#1f77b4' ), # it doesnt set font of hoover text. Must be set by css in html.
                       hoverinfo = 'text',
                       opacity = 0.8 )
     
    # Lines bettween vertices. 
    lines = go.Scatter( x = Xe,
                        y = Ye,
                        mode = 'lines',
                        line = dict( color = 'rgb(210,210,210)', width = 1 ),
                        hoverinfo = 'none',
                        textfont = dict( family = 'Calibri', size = 38, color = '#1f77b4' ) )
     
    # Provide description of each vertices.
    def make_annotations( pos, info, font_size = 8, font_color = 'rgb(0,0,0)' ):
        L = len( pos )
        if len( info ) != L:
            raise ValueError( 'make_annotations()::The lists pos and info must have the same len' )
         
        annotations = go.Annotations()
        for k in range( L ):
            item = go.Annotation( text = info[k] , # text to be shown within the node  
                                  x = pos[k][0], y = pos[k][1],
                                  xref = 'x1', yref = 'y1',
                                  font = dict( color = font_color, size = font_size ),
                                  showarrow = False )
            annotations.append( item )
             
        return annotations  
       
    axis = dict( showline = False, # hide axis line, grid, ticklabels and  title
                 zeroline = False,
                 showgrid = False,
                 showticklabels = False )
          
    layout = dict( title = 'Gomoku Game Tree',  
                   annotations = make_annotations( VertexInfoPosition, VertexInfoText ),
                   font = dict(size=12),
                   showlegend = False,
                   xaxis = go.XAxis(axis),
                   yaxis = go.YAxis(axis),          
                   margin = dict(l=40, r=40, b=85, t=100),
                   hovermode = 'closest',
                   plot_bgcolor = 'rgb(248,248,248)' )
     
    # Default layout - grid etc.  
    # layout = go.Layout( showlegend=False )
      
    #======== PLOT A FIGURE ==========: 
    
    data=go.Data([lines, dots])
    fig=dict(data=data, layout=layout)
    fig['layout'].update( annotations = make_annotations( VertexInfoPosition, VertexInfoText ) )
    plotly.offline.plot(fig, filename=FIGURE_OUTPUT_NAME)
     
    #======== PLOT A FIGURE ==========: 

    SetHoverStyle()