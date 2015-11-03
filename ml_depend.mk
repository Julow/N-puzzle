ML_OBJS = \
	srcs/solver/batteries-included/src/BatHeap.cmi \
	srcs/solver/GenericInterfaces.cmx \
	srcs/solver/npuzzle.cmi \
	srcs/solver/Grid.cmi \
	srcs/solver/Grid.cmx \
	srcs/solver/EventHandler.cmi \
	srcs/solver/EventHandler.cmx \
	srcs/solver/batteries-included/src/BatHeap.cmx \
	srcs/solver/Algorithms/IDAStar.cmi \
	srcs/solver/Algorithms/IDAStar.cmx \
	srcs/solver/Algorithms/GreedySearch.cmi \
	srcs/solver/Algorithms/GreedySearch.cmx \
	srcs/solver/Algorithms/AStar.cmi \
	srcs/solver/Algorithms/AStar.cmx \
	srcs/solver/Heuristics/DPatternDB.cmx \
	srcs/solver/Heuristics/DPatternDBCompute.cmx \
	srcs/solver/Heuristics/DPatternDBHeuristic.cmi \
	srcs/solver/Heuristics/DPatternDBInit.cmx \
	srcs/solver/Heuristics/LinearConflictHeuristic.cmi \
	srcs/solver/Heuristics/ManhattanDistanceHeuristic.cmi \
	srcs/solver/Heuristics/UniformCostHeuristic.cmi \
	srcs/solver/Heuristics/UniformCostHeuristic.cmx \
	srcs/solver/Heuristics/ManhattanDistanceHeuristic.cmx \
	srcs/solver/Heuristics/LinearConflictHeuristic.cmx \
	srcs/solver/Heuristics/DPatternDBHeuristic.cmx \
	srcs/solver/solver.cmx

OCAML_DIR = srcs/solver
ML_MAX_LEN = 53

srcs/solver/Algorithms/AStar.cmo : srcs/solver/GenericInterfaces.cmi \
    srcs/solver/Algorithms/AStar.cmi srcs/solver/Algorithms/AStar.ml
srcs/solver/Algorithms/AStar.cmx srcs/solver/Algorithms/AStar.o : \
    srcs/solver/GenericInterfaces.cmi srcs/solver/GenericInterfaces.cmx \
    srcs/solver/Algorithms/AStar.cmi srcs/solver/Algorithms/AStar.ml
srcs/solver/Algorithms/AStar.cmi : srcs/solver/GenericInterfaces.cmi
srcs/solver/Algorithms/GreedySearch.cmo : srcs/solver/GenericInterfaces.cmi \
    srcs/solver/Algorithms/GreedySearch.cmi \
    srcs/solver/Algorithms/GreedySearch.ml
srcs/solver/Algorithms/GreedySearch.cmx \
    srcs/solver/Algorithms/GreedySearch.o : srcs/solver/GenericInterfaces.cmi \
    srcs/solver/GenericInterfaces.cmx srcs/solver/Algorithms/GreedySearch.cmi \
    srcs/solver/Algorithms/GreedySearch.ml
srcs/solver/Algorithms/GreedySearch.cmi : srcs/solver/GenericInterfaces.cmi
srcs/solver/Algorithms/IDAStar.cmo : srcs/solver/GenericInterfaces.cmi \
    srcs/solver/Algorithms/IDAStar.cmi srcs/solver/Algorithms/IDAStar.ml
srcs/solver/Algorithms/IDAStar.cmx srcs/solver/Algorithms/IDAStar.o : \
    srcs/solver/GenericInterfaces.cmi srcs/solver/GenericInterfaces.cmx \
    srcs/solver/Algorithms/IDAStar.cmi srcs/solver/Algorithms/IDAStar.ml
srcs/solver/Algorithms/IDAStar.cmi : srcs/solver/GenericInterfaces.cmi
srcs/solver/batteries-included/src/BatHeap.cmo : \
    srcs/solver/batteries-included/src/BatHeap.cmi \
    srcs/solver/batteries-included/src/BatHeap.ml
srcs/solver/batteries-included/src/BatHeap.cmx \
    srcs/solver/batteries-included/src/BatHeap.o : \
    srcs/solver/batteries-included/src/BatHeap.cmi \
    srcs/solver/batteries-included/src/BatHeap.ml
srcs/solver/batteries-included/src/BatHeap.cmi :
srcs/solver/EventHandler.cmo : srcs/solver/GenericInterfaces.cmi \
    srcs/solver/EventHandler.cmi srcs/solver/EventHandler.ml
srcs/solver/EventHandler.cmx srcs/solver/EventHandler.o : \
    srcs/solver/GenericInterfaces.cmi srcs/solver/GenericInterfaces.cmx \
    srcs/solver/EventHandler.cmi srcs/solver/EventHandler.ml
srcs/solver/EventHandler.cmi : srcs/solver/GenericInterfaces.cmi
srcs/solver/GenericInterfaces.cmo srcs/solver/GenericInterfaces.cmi : \
    srcs/solver/GenericInterfaces.ml
srcs/solver/GenericInterfaces.cmx srcs/solver/GenericInterfaces.o \
    srcs/solver/GenericInterfaces.cmi : srcs/solver/GenericInterfaces.ml
srcs/solver/Grid.cmo : srcs/solver/npuzzle.cmi \
    srcs/solver/GenericInterfaces.cmi srcs/solver/Grid.cmi \
    srcs/solver/Grid.ml
srcs/solver/Grid.cmx srcs/solver/Grid.o : srcs/solver/npuzzle.cmi \
    srcs/solver/GenericInterfaces.cmi srcs/solver/GenericInterfaces.cmx \
    srcs/solver/Grid.cmi srcs/solver/Grid.ml
srcs/solver/Grid.cmi : srcs/solver/npuzzle.cmi \
    srcs/solver/GenericInterfaces.cmi
srcs/solver/Heuristics/DPatternDB.cmo srcs/solver/Heuristics/DPatternDB.cmi \
    : srcs/solver/Grid.cmi srcs/solver/Heuristics/DPatternDB.ml
srcs/solver/Heuristics/DPatternDB.cmx srcs/solver/Heuristics/DPatternDB.o \
    srcs/solver/Heuristics/DPatternDB.cmi : srcs/solver/Grid.cmi \
    srcs/solver/Grid.cmx srcs/solver/Heuristics/DPatternDB.ml
srcs/solver/Heuristics/DPatternDBCompute.cmo \
    srcs/solver/Heuristics/DPatternDBCompute.cmi : srcs/solver/Grid.cmi \
    srcs/solver/Heuristics/DPatternDBCompute.ml
srcs/solver/Heuristics/DPatternDBCompute.cmx \
    srcs/solver/Heuristics/DPatternDBCompute.o \
    srcs/solver/Heuristics/DPatternDBCompute.cmi : srcs/solver/Grid.cmi \
    srcs/solver/Grid.cmx srcs/solver/Heuristics/DPatternDBCompute.ml
srcs/solver/Heuristics/DPatternDBHeuristic.cmo : srcs/solver/Grid.cmi \
    srcs/solver/Heuristics/DPatternDBHeuristic.cmi \
    srcs/solver/Heuristics/DPatternDBHeuristic.ml
srcs/solver/Heuristics/DPatternDBHeuristic.cmx \
    srcs/solver/Heuristics/DPatternDBHeuristic.o : srcs/solver/Grid.cmi \
    srcs/solver/Grid.cmx srcs/solver/Heuristics/DPatternDBHeuristic.cmi \
    srcs/solver/Heuristics/DPatternDBHeuristic.ml
srcs/solver/Heuristics/DPatternDBHeuristic.cmi : srcs/solver/Grid.cmi
srcs/solver/Heuristics/DPatternDBInit.cmo \
    srcs/solver/Heuristics/DPatternDBInit.cmi : srcs/solver/Grid.cmi \
    srcs/solver/Heuristics/DPatternDBInit.ml
srcs/solver/Heuristics/DPatternDBInit.cmx \
    srcs/solver/Heuristics/DPatternDBInit.o \
    srcs/solver/Heuristics/DPatternDBInit.cmi : srcs/solver/Grid.cmi \
    srcs/solver/Grid.cmx srcs/solver/Heuristics/DPatternDBInit.ml
srcs/solver/Heuristics/LinearConflictHeuristic.cmo : srcs/solver/Grid.cmi \
    srcs/solver/Heuristics/LinearConflictHeuristic.cmi \
    srcs/solver/Heuristics/LinearConflictHeuristic.ml
srcs/solver/Heuristics/LinearConflictHeuristic.cmx \
    srcs/solver/Heuristics/LinearConflictHeuristic.o : srcs/solver/Grid.cmi \
    srcs/solver/Grid.cmx srcs/solver/Heuristics/LinearConflictHeuristic.cmi \
    srcs/solver/Heuristics/LinearConflictHeuristic.ml
srcs/solver/Heuristics/LinearConflictHeuristic.cmi : srcs/solver/Grid.cmi
srcs/solver/Heuristics/ManhattanDistanceHeuristic.cmo : srcs/solver/Grid.cmi \
    srcs/solver/Heuristics/ManhattanDistanceHeuristic.cmi \
    srcs/solver/Heuristics/ManhattanDistanceHeuristic.ml
srcs/solver/Heuristics/ManhattanDistanceHeuristic.cmx \
    srcs/solver/Heuristics/ManhattanDistanceHeuristic.o : \
    srcs/solver/Grid.cmi srcs/solver/Grid.cmx \
    srcs/solver/Heuristics/ManhattanDistanceHeuristic.cmi \
    srcs/solver/Heuristics/ManhattanDistanceHeuristic.ml
srcs/solver/Heuristics/ManhattanDistanceHeuristic.cmi : srcs/solver/Grid.cmi
srcs/solver/Heuristics/UniformCostHeuristic.cmo : srcs/solver/Grid.cmi \
    srcs/solver/Heuristics/UniformCostHeuristic.cmi \
    srcs/solver/Heuristics/UniformCostHeuristic.ml
srcs/solver/Heuristics/UniformCostHeuristic.cmx \
    srcs/solver/Heuristics/UniformCostHeuristic.o : srcs/solver/Grid.cmi \
    srcs/solver/Grid.cmx srcs/solver/Heuristics/UniformCostHeuristic.cmi \
    srcs/solver/Heuristics/UniformCostHeuristic.ml
srcs/solver/Heuristics/UniformCostHeuristic.cmi : srcs/solver/Grid.cmi
srcs/solver/npuzzle.cmi :
srcs/solver/solver.cmo srcs/solver/solver.cmi : srcs/solver/Grid.cmi \
    srcs/solver/GenericInterfaces.cmi srcs/solver/EventHandler.cmi \
    srcs/solver/solver.ml
srcs/solver/solver.cmx srcs/solver/solver.o srcs/solver/solver.cmi : \
    srcs/solver/Grid.cmi srcs/solver/Grid.cmx \
    srcs/solver/GenericInterfaces.cmi srcs/solver/GenericInterfaces.cmx \
    srcs/solver/EventHandler.cmi srcs/solver/EventHandler.cmx \
    srcs/solver/solver.ml