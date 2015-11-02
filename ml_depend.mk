ML_OBJS = \
	srcs/solver/EventHandler.cmx \
	srcs/solver/GenericInterfaces.cmx \
	srcs/solver/solver.cmx \
	srcs/solver/Grid.cmx \
	srcs/solver/BatHeap.cmx \
	srcs/solver/Algorithms/AStar.cmi \
	srcs/solver/Algorithms/IDAStar.cmx \
	srcs/solver/Algorithms/GreedySearch.cmx \
	srcs/solver/Algorithms/GreedySearch.cmi \
	srcs/solver/Algorithms/AStar.cmx \
	srcs/solver/Algorithms/IDAStar.cmi \
	srcs/solver/Heuristics/DPatternDBInit.cmx \
	srcs/solver/Heuristics/ManhattanDistanceHeuristic.cmi \
	srcs/solver/Heuristics/DPatternDBCompute.cmx \
	srcs/solver/Heuristics/DPatternDB.cmx \
	srcs/solver/Heuristics/DPatternDBHeuristic.cmx \
	srcs/solver/Heuristics/ManhattanDistanceHeuristic.cmx \
	srcs/solver/Heuristics/UniformCostHeuristic.cmx \
	srcs/solver/Heuristics/UniformCostHeuristic.cmi \
	srcs/solver/Heuristics/DPatternDBHeuristic.cmi \
	srcs/solver/Heuristics/LinearConflictHeuristic.cmi \
	srcs/solver/Heuristics/LinearConflictHeuristic.cmx \
	srcs/solver/BatHeap.cmi \
	srcs/solver/EventHandler.cmi \
	srcs/solver/Grid.cmi \
	srcs/solver/npuzzle.cmi

OCAML_DIR = srcs/solver

srcs/solver/EventHandler.cmo : srcs/solver/EventHandler.cmi
srcs/solver/EventHandler.cmx : srcs/solver/EventHandler.cmi
srcs/solver/GenericInterfaces.cmo :
srcs/solver/GenericInterfaces.cmx :
srcs/solver/solver.cmo :
srcs/solver/solver.cmx :
srcs/solver/Grid.cmo : srcs/solver/Grid.cmi
srcs/solver/Grid.cmx : srcs/solver/Grid.cmi
srcs/solver/BatHeap.cmo : srcs/solver/BatHeap.cmi
srcs/solver/BatHeap.cmx : srcs/solver/BatHeap.cmi
srcs/solver/Algorithms/AStar.cmi :
srcs/solver/Algorithms/IDAStar.cmo : srcs/solver/Algorithms/IDAStar.cmi
srcs/solver/Algorithms/IDAStar.cmx : srcs/solver/Algorithms/IDAStar.cmi
srcs/solver/Algorithms/GreedySearch.cmo : \
    srcs/solver/Algorithms/GreedySearch.cmi
srcs/solver/Algorithms/GreedySearch.cmx : \
    srcs/solver/Algorithms/GreedySearch.cmi
srcs/solver/Algorithms/GreedySearch.cmi :
srcs/solver/Algorithms/AStar.cmo : srcs/solver/Algorithms/AStar.cmi
srcs/solver/Algorithms/AStar.cmx : srcs/solver/Algorithms/AStar.cmi
srcs/solver/Algorithms/IDAStar.cmi :
srcs/solver/Heuristics/DPatternDBInit.cmo :
srcs/solver/Heuristics/DPatternDBInit.cmx :
srcs/solver/Heuristics/ManhattanDistanceHeuristic.cmi :
srcs/solver/Heuristics/DPatternDBCompute.cmo :
srcs/solver/Heuristics/DPatternDBCompute.cmx :
srcs/solver/Heuristics/DPatternDB.cmo :
srcs/solver/Heuristics/DPatternDB.cmx :
srcs/solver/Heuristics/DPatternDBHeuristic.cmo : \
    srcs/solver/Heuristics/DPatternDBHeuristic.cmi
srcs/solver/Heuristics/DPatternDBHeuristic.cmx : \
    srcs/solver/Heuristics/DPatternDBHeuristic.cmi
srcs/solver/Heuristics/ManhattanDistanceHeuristic.cmo : \
    srcs/solver/Heuristics/ManhattanDistanceHeuristic.cmi
srcs/solver/Heuristics/ManhattanDistanceHeuristic.cmx : \
    srcs/solver/Heuristics/ManhattanDistanceHeuristic.cmi
srcs/solver/Heuristics/UniformCostHeuristic.cmo : \
    srcs/solver/Heuristics/UniformCostHeuristic.cmi
srcs/solver/Heuristics/UniformCostHeuristic.cmx : \
    srcs/solver/Heuristics/UniformCostHeuristic.cmi
srcs/solver/Heuristics/UniformCostHeuristic.cmi :
srcs/solver/Heuristics/DPatternDBHeuristic.cmi :
srcs/solver/Heuristics/LinearConflictHeuristic.cmi :
srcs/solver/Heuristics/LinearConflictHeuristic.cmo : \
    srcs/solver/Heuristics/LinearConflictHeuristic.cmi
srcs/solver/Heuristics/LinearConflictHeuristic.cmx : \
    srcs/solver/Heuristics/LinearConflictHeuristic.cmi
srcs/solver/BatHeap.cmi :
srcs/solver/EventHandler.cmi :
srcs/solver/Grid.cmi :
srcs/solver/npuzzle.cmi :
