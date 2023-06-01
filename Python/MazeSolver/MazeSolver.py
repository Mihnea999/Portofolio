from array import *
import copy

#Creating Maze

_maze = [
    [0,1,0,0,0,0,0,0,0,0],
    [0,1,0,0,0,0,1,0,0,0],
    [1,1,1,1,0,1,1,1,1,0],
    [0,1,0,1,0,0,1,0,0,0],
    [0,1,0,1,0,0,1,0,0,0],
    [1,1,1,1,1,1,1,1,0,0],
    [0,0,1,0,1,0,0,1,0,0],
    [0,1,0,0,0,0,0,1,0,0],
    [1,1,1,1,1,1,1,1,0,0],
    [0,1,0,0,0,0,0,0,0,0],
]

nullroute = [0,0,0,0]

bifurcationCount = 0
maze = copy.deepcopy(_maze)
#Array for the directions
#[step][x,y] example: step 0 mover is x = 0 y = 0
direction = []
#bifurcations = [step,left,right,up,down]
bifurcations = []


#Specify the first position
while True:
    try:
        position = int(input("First Pos X: "))
        break
    except ValueError:
        print("Please enter a valid position (0-9): ")

#Finding how deep is the maze
rows = len(maze)
#Searching on the last row the exit
exitPos = maze[rows-1].index(1)


#Setting Up the first position
pos = [position, 0]
direction.append(pos)
#Searching next Coordonate (left right up down)
def SearchRoutes(step):
    routePrev = []
        # 0 ---- x axis
        # 1 ---- y axis
    if(direction[step][0] != 0): #if the mover is not on left edge
        if(maze[direction[step][1]][direction[step][0] -1] == 1): #search in left direction for a route
            routePrev.append(1)
        else:
            routePrev.append(0)
    else:
        routePrev.append(0)
    
    if(direction[step][0] != 9): #if the mover is not on the right edge
        if(maze[direction[step][1]][direction[step][0] +1] == 1): #Search in right direction for a route
            routePrev.append(1)
        else:
            routePrev.append(0)
    else:
        routePrev.append(0)

    if(direction[step][1] != 0): #if the mover is not on the first row
        if(maze[direction[step][1] -1][direction[step][0]] == 1): # search for a route up
            routePrev.append(1)
        else:
            routePrev.append(0)
    else:
        routePrev.append(0)
    
    if(direction[step][1] != rows-1): #if the mover in not at the end
        if(maze[direction[step][1] +1][direction[step][0]] == 1): #Search for a direction down
            routePrev.append(1)
        else:
            routePrev.append(0)
    else:
        return 0
    return routePrev
        
def AnalyzeAndMove(routePrev):
    global step
    global bifurcationCount
    global direction
    #Check if there are more routes
    routes = routePrev.count(1)

    if(routes > 1): #if there are more than one rout add the step and the coordonates
        _routePrev = copy.deepcopy(routePrev)
        _routePrev.insert(0,step)
        bifurcations.append(_routePrev)
        #Detect the first disponible Route
        directionID = routePrev.index(1)
        bifurcationID = _routePrev.index(1)
        #Go on the route So delete it
        bifurcations[bifurcationCount].pop(bifurcationID)
        bifurcations[bifurcationCount].insert(bifurcationID, 0)
        bifurcationCount +=1
        routes = 0
    elif(routes == 0):
       if(bifurcations == list()): #if there are no bifurcations
           print("Maze is imposible!")
           exit()
       else:
            step = bifurcations[bifurcationCount-1][0] +1
            temp = copy.deepcopy(bifurcations)
            if(len(temp[bifurcationCount -1]) != 4):
                temp[bifurcationCount -1].pop(0)
            bifurcationCount -=1
            bifurcations.pop(bifurcationCount)
            maze[direction[step][1]].pop(direction[step][0])
            maze[direction[step][1]].insert(direction[step][0],0)
            for i in range(step,len(direction)):
                direction.pop(step)
            step -=2
            return
    else:
        directionID = routePrev.index(1)
    maze[direction[step][1]].pop(direction[step][0])
    maze[direction[step][1]].insert(direction[step][0],0)
    

    def nextPosition(directionID, direction):

        nPos = direction[step].copy()
        if(directionID == 0):
            nPos[0] -=1
        if(directionID == 1):
            nPos[0] +=1
        if(directionID == 2):
            nPos[1] -=1
        if(directionID == 3):
            nPos[1] +=1
        return nPos
    direction.append(nextPosition(directionID, direction))




step = 0
finishPoint = [maze[exitPos-1].index(1),exitPos-1]
while True:
    route = SearchRoutes(step)
    if(route == 0):
        #direction.append(finishPoint)
        break
    AnalyzeAndMove(route)
    step += 1
    if(step == 40):
        break

for p in _maze:
    print(p)
print(direction)
print("Finish")
        


