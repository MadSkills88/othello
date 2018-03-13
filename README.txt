Anthony's contribution: Worked on Heuristic solution by fixing some segmentation
faults and getting it to run with detection and weighting of corner tiles and tiles
adjacent to corners. Helped improve the performance of the bot. Helped plan out
the minimax solution, and did debugging with print statements to fix some errors


===============================================================================
Roadmap of changes:

The heuristic solution gets all the possible moves on the board for each turn, and
checks which move will return the highest possible score. The heuristic solution
prioritizes corner tiles as potential moves and de-prioritizes tiles adjacent
to the corners. This is because corner tiles are highly preferred moves that
can convert a large number of the opponent's pieces, while tiles adjacent to
the corners are vulnerable.
Our heuristic solution also takes into account side stability and mobility.
Mobility describes the number of moves available to our bot versus the number
of moves available to the opponent. The higher the mobility, the better the move
and therefore we prioritize mobility.


The minimax solution: After implementing the minimax solution, we discovered
that depth 4 gave us optimal performance.


Optimizations: Experimented with the weighting of different tile locations
(corners, tiles adjacent to corners), as well as the weighting of side
stability and mobility. We also optimized the compiler with optimization level
-O3, which made the bot run faster with minimax depth 4.
