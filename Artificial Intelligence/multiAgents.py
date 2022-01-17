# multiAgents.py
# --------------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


from util import manhattanDistance
from game import Directions
import random, util

from game import Agent

class ReflexAgent(Agent):
    """
    A reflex agent chooses an action at each choice point by examining
    its alternatives via a state evaluation function.

    The code below is provided as a guide.  You are welcome to change
    it in any way you see fit, so long as you don't touch our method
    headers.
    """


    def getAction(self, gameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some Directions.X for some X in the set {NORTH, SOUTH, WEST, EAST, STOP}
        """
        # Collect legal moves and successor states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best

        "Add more of your code here if you want to"

        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current and proposed successor
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (newFood) and Pacman position after moving (newPos).
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """
        # Useful information you can extract from a GameState (pacman.py)
        successorGameState = currentGameState.generatePacmanSuccessor(action)
        newPos = successorGameState.getPacmanPosition()
        newFood = successorGameState.getFood()
        newGhostStates = successorGameState.getGhostStates()
        newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]
        
        score = successorGameState.getScore()


        # The distance to nearest food of successor state
        foodCoe = float("inf");
        for f in newFood.asList():
            if manhattanDistance(f , newPos) < foodCoe :
                foodCoe = manhattanDistance(f, newPos)

        # If next state eat food, get rid of above impact
        if successorGameState.getFood().count() < currentGameState.getFood().count():
            foodCoe = 0
        

        score -= foodCoe

        # If no scared times, count ghost impact
        if (newScaredTimes[0] == 0):
            for ghost in newGhostStates:
                gPos = ghost.getPosition()
                # If collied with ghost, not valid state
                if manhattanDistance(gPos, newPos) <= 1:
                    return float("-inf");
                # The nearby ghost get more impact
                score -= 25.0 / manhattanDistance(gPos, newPos)
        return score

def scoreEvaluationFunction(currentGameState):
    """
    This default evaluation function just returns the score of the state.
    The score is the same one displayed in the Pacman GUI.

    This evaluation function is meant for use with adversarial search agents
    (not reflex agents).
    """
    return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
    """
    This class provides some common elements to all of your
    multi-agent searchers.  Any methods defined here will be available
    to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

    You *do not* need to make any changes here, but you can if you want to
    add functionality to all your adversarial search agents.  Please do not
    remove anything, however.

    Note: this is an abstract class: one that should not be instantiated.  It's
    only partially specified, and designed to be extended.  Agent (game.py)
    is another abstract class.
    """

    def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
        self.index = 0 # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)

def miniMaxSearch(state, depth, maxDepth, evaluationFunction, alpha = None, beta = None):
    """
    This function doing the miniMax search with alpha beta purning
    If the alpha is not provided the purning will not work.
    """
    # Check the search is end or not
    if depth == maxDepth or state.isWin() or state.isLose():
        return None, evaluationFunction(state)

    # Init varible
    resultAction = None
    value = 0
    agent = depth % state.getNumAgents()

    # Pacman - Max Node
    if agent == 0: 
        value = float('-inf')
        # append child nodes
        for action in state.getLegalActions(agent):
            succ = state.generateSuccessor(agent, action)
            _, newValue = miniMaxSearch(succ, depth+1, maxDepth, evaluationFunction, alpha, beta)

            # Got new max value
            if newValue > value:
                value = newValue
                resultAction = action
                # Check should it be purning
                if not alpha is None:
                    if value > beta:
                        break
                    if value > alpha:
                        alpha = value;
    
    # Ghost - Min node
    else:
        value = float('inf')
        # append child nodes
        for action in state.getLegalActions(agent):
            succ = state.generateSuccessor(agent, action)
            _, newValue = miniMaxSearch(succ, depth+1, maxDepth, evaluationFunction, alpha, beta);
            
            # Got new min value
            if newValue < value:
                value = newValue
                resultAction = action
                # Check should it be purning
                if not alpha is None:
                    if value < alpha:
                        break
                    if value < beta:
                        beta = value;
    
    # Return action and estimated score
    return resultAction, value

class MinimaxAgent(MultiAgentSearchAgent):
    """
    Your minimax agent (question 2)
    """

    def getAction(self, gameState):
        """
        Returns the minimax action from the current gameState using self.depth
        and self.evaluationFunction.
        """
        maxDepth = self.depth*gameState.getNumAgents()
        return miniMaxSearch(gameState,0,maxDepth,self.evaluationFunction)[0];

class AlphaBetaAgent(MultiAgentSearchAgent):
    """
    Your minimax agent with alpha-beta pruning (question 3)
    """

    def getAction(self, gameState):
        """
        Returns the minimax action using self.depth and self.evaluationFunction
        """
        maxDepth = self.depth*gameState.getNumAgents()
        return miniMaxSearch(gameState,0,maxDepth,self.evaluationFunction,float('-inf'),float("inf"))[0];

def expectiMaxSearch(state, depth, maxDepth, evaluationFunction):
    """
    This function doing the miniMax search with alpha beta purning
    If the alpha is not provided the purning will not work.
    """

    # Check the search is end or not
    if depth == maxDepth or state.isWin() or state.isLose():
        return None, evaluationFunction(state)

    # Init varible
    agent = depth % state.getNumAgents()
    resultAction = None
    value = 0
    
    # Pacman - Max Node
    if agent == 0:
        value = float('-inf')
        # append child nodes
        for action in state.getLegalActions(agent):
            succ = state.generateSuccessor(agent, action)
            _, newValue = expectiMaxSearch(succ, depth+1, maxDepth, evaluationFunction)

            # Got new max value
            if newValue > value:
                value = newValue
                resultAction = action
    
    # Ghost - Expect Node
    else:

        # append child nodes
        actions = state.getLegalActions(agent)
        for action in actions:
            succ = state.generateSuccessor(agent, action)
            _, newValue = expectiMaxSearch(succ, depth+1, maxDepth, evaluationFunction)
            value += newValue # Sum up values
        
        # Get average
        value /= float(len(actions))
    
    return resultAction, value

class ExpectimaxAgent(MultiAgentSearchAgent):
    """
      Your expectimax agent (question 4)
    """

    def getAction(self, gameState):
        """
        Returns the expectimax action using self.depth and self.evaluationFunction

        All ghosts should be modeled as choosing uniformly at random from their
        legal moves.
        """
        maxDepth = self.depth*gameState.getNumAgents()
        return expectiMaxSearch(gameState,0,maxDepth,self.evaluationFunction)[0]

def betterEvaluationFunction(currentGameState):
    """
    Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
    evaluation function (question 5).

    DESCRIPTION: <write something here so we know what you did>
    """
    "*** YOUR CODE HERE ***"
    myDistance = 0;
    minDistance = 0;
    score = currentGameState.getScore();

    for 

# Abbreviation
better = betterEvaluationFunction
