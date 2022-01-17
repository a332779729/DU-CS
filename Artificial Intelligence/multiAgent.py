# multiAgents.py
# --------------
# Licensing Information: Please do not distribute or publish solutions to this
# project. You are free to use and extend these projects for educational
# purposes. The Pacman AI projects were developed at UC Berkeley, primarily by
# John DeNero (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# For more info, see http://inst.eecs.berkeley.edu/~cs188/sp09/pacman.html

from util import manhattanDistance
from game import Directions
import random, util, math

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
    some Directions.X for some X in the set {North, South, West, East, Stop}
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
    newFood = successorGameState.getFood().asList()

    minDist = 999999
    for point in newFood:
      minDist = min(minDist, manhattanDistance(newPos, point))

    ghostDanger = 0
    for ghost in successorGameState.getGhostPositions():
      dist = max(4 - manhattanDistance(newPos, ghost), 0)
      ghostDanger += dist*dist

    return successorGameState.getScore() + 10.0/minDist - ghostDanger

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

class MinimaxAgent(MultiAgentSearchAgent):
  """
    Your minimax agent (question 2)
  """

  def getAction(self, gameState):
    """
      Returns the minimax action from the current gameState using self.depth
      and self.evaluationFunction.

      Here are some method calls that might be useful when implementing minimax.

      gameState.getLegalActions(agentIndex):
        Returns a list of legal actions for an agent
        agentIndex=0 means Pacman, ghosts are >= 1

      Directions.STOP:
        The stop direction, which is always legal

      gameState.generateSuccessor(agentIndex, action):
        Returns the successor game state after an agent takes an action

      gameState.getNumAgents():
        Returns the total number of agents in the game
    """
    return self.minimax(gameState, Directions.STOP, self.depth*gameState.getNumAgents(), 0)[0]

  def minimax(self, gameState, action, depth, agentID):
    if depth is 0 or gameState.isLose() or gameState.isWin():
      return (action, self.evaluationFunction(gameState))
    if agentID is 0:
      bestAction = (Directions.STOP,  -999999)
      for legalAction in gameState.getLegalActions(agentID):
        currAction = self.minimax(gameState.generateSuccessor(agentID, legalAction),
          (legalAction if depth is self.depth*gameState.getNumAgents() else action), depth - 1, (agentID + 1) % gameState.getNumAgents())
        if currAction[1] > bestAction[1]:
          bestAction = currAction
      return bestAction
    else:
      bestAction = (Directions.STOP, 999999)
      for legalAction in gameState.getLegalActions(agentID):
        currAction = self.minimax(gameState.generateSuccessor(agentID, legalAction),
          action, depth - 1, (agentID + 1) % gameState.getNumAgents())
        if currAction[1] < bestAction[1]:
          bestAction = currAction
      return bestAction

class AlphaBetaAgent(MultiAgentSearchAgent):
  """
    Your minimax agent with alpha-beta pruning (question 3)
  """

  def getAction(self, gameState):
    """
      Returns the minimax action using self.depth and self.evaluationFunction
    """

    return self.alphaBeta(gameState, Directions.STOP, self.depth*gameState.getNumAgents(), 0, -999999, 999999)[0]

  def alphaBeta(self, gameState, action, depth, agentID, alpha, beta):
    if depth is 0 or gameState.isLose() or gameState.isWin():
      return (action, self.evaluationFunction(gameState))
    if agentID is 0:
      bestAction = (action, alpha)
      for legalAction in gameState.getLegalActions(agentID):
        currAction = self.alphaBeta(gameState.generateSuccessor(agentID, legalAction),
          (legalAction if depth is self.depth*gameState.getNumAgents() else action), depth - 1, 1, alpha, beta)
        if currAction[1] > bestAction[1]:
          bestAction = currAction
        elif currAction[1] is bestAction[1]:
          random.choice([bestAction, currAction])
          if beta <= alpha:
            break
      return bestAction
    else:
      bestAction = (Directions.STOP, beta)
      for legalAction in gameState.getLegalActions(agentID):
        currAction = self.alphaBeta(gameState.generateSuccessor(agentID, legalAction),
          action, depth - 1, (agentID + 1) % gameState.getNumAgents(), alpha, beta)
        if currAction[1] < bestAction[1]:
          bestAction = currAction
        if beta <= alpha:
          break
      return bestAction

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
    return self.expectimax(gameState, Directions.STOP, self.depth*gameState.getNumAgents(), 0)[0]

  def expectimax(self, gameState, action, depth, agentID):
    if depth is 0 or gameState.isLose() or gameState.isWin():
      return (action, self.evaluationFunction(gameState))
    if agentID is 0:
      bestAction = (Directions.STOP,  -999999)
      for legalAction in gameState.getLegalActions(agentID):
        currAction = self.expectimax(gameState.generateSuccessor(agentID, legalAction),
          (legalAction if depth is self.depth*gameState.getNumAgents() else action), depth - 1, (agentID + 1) % gameState.getNumAgents())
        if currAction[1] > bestAction[1]:
          bestAction = currAction
      return bestAction
    else:
      average = 0;
      for legalAction in gameState.getLegalActions(agentID):
        currAction = self.expectimax(gameState.generateSuccessor(agentID, legalAction),
          action, depth - 1, (agentID + 1) % gameState.getNumAgents())
        average += currAction[1] / len(legalAction)
      return (action, average)

def betterEvaluationFunction(currentGameState):
  """
    Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
    evaluation function (question 5).

    DESCRIPTION:
      Sum the distance to all food pellets.  This will ultimately be subtracted
        from the score to attempt to keep Pacman relatively close to all food.
      Find the distance to all ghosts and weight this distances by relative
        danger (only ghosts within 4 tiles of Pacman arte considered to be
        an active threat).  This value is then squared and added to a cumulative
        ghostDanger score which is later subtracted from the utility score.
      Additional factors are then taken into account.  First, a penalty is subtracted
        for every dot of food still present on the board.  Then, a large value of
        +/- 5000 is added based on whether or not a given state is a win/lose state.
      Finally, these terms are summed together and the result is returned as the
        utility score for that state.
  """
  position = currentGameState.getPacmanPosition()
  food = currentGameState.getFood().asList()

  foodDist = 0
  for dot in food:
    foodDist += 2.5*manhattanDistance(position, dot)

  ghostDanger = 0
  for ghost in currentGameState.getGhostPositions():
    dist = max(4 - manhattanDistance(position, ghost), 0)
    ghostDanger += math.pow(dist, 3)

  additionalFactors = -10*len(food) # penalty for amount of food remaining
  if currentGameState.isLose(): additionalFactors -= 5000
  elif currentGameState.isWin(): additionalFactors += 5000
  additionalFactors += random.randint(-5, 5) # prevent paralysis due to ties

  return currentGameState.getScore() - foodDist - ghostDanger + additionalFactors

# Abbreviation
better = betterEvaluationFunction

class ContestAgent(MultiAgentSearchAgent):
  """
    Your agent for the mini-contest
  """

  def getAction(self, gameState):
    """
      Returns an action.  You can use any method you want and search to any depth you want.
      Just remember that the mini-contest is timed, so you have to trade off speed and computation.

      Ghosts don't behave randomly anymore, but they aren't perfect either -- they'll usually
      just make a beeline straight towards Pacman (or away from him if they're scared!)
    """
    return Directions.STOP
