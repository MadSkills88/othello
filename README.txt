Anthony's contribution: Worked on Heuristic solution by fixing some segmentation
faults and getting it to run with detection and weighting of corner tiles and tiles
adjacent to corners. Helped improve the performance of the bot. Helped plan out
the minimax solution, and did debugging with print statements to fix some errors

Samuel Owen's Contribution: Changed heuristic to account for adjacent to corners, kat_corner to corners, corners, sides, mobility, and side stabilization. Wrote minimax and adjusted minimax to work better. Adjusted minimax values and process in order to avoid seg faulting. Changed get moves from giving a vector of moves to a vector of pointers to moves (helped reduce seg faults) and then worked on memory. Messed with values of heuristic in order to beat better player, and constant time player. 
===============================================================================
Roadmap of changes:

Initially, the heuristic only took into account corners and adjacent pieces to corners. This was changed to account for corners, adjacent to corners, katty corner pieces (katty corner to the corners), and side pieces. These values were tested to maximize our winning. Stability of the sides is also taken into account, but I find it rarely does too much since it is only taken into affect a few times a game. Mobility was taken into account and is a significant amount of the score for our heuristic. Again, values were changed in order to try to maximize winnings.

Initially, I wanted to make minimax such that it is similar to alpha-beta pruning (except I didn't know what this was at the time)m however, the code just didn't work out. Instead, I did the classic minimax. One thing that was helpful was changing the getMoves to return a vector of pointers. This reduced a significant amount of the errors that came up during the game trying to do moves which were not available/not on the board. Also, the heuristic needed to be changed in order to calculate the score based on side. Thus, when we calculate the score for our opponent, we can now just look at the negative of it (which would be our score in that case). Our minimax works best with a depth of 4. Otherwise, it takes too long. 


The minimax solution: After implementing the minimax solution, we discovered
that depth 4 gave us optimal performance.


Optimizations: Experimented with the weighting of different tile locations
(corners, tiles adjacent to corners), as well as the weighting of side
stability and mobility. We also optimized the compiler with optimization level
-O3, which made the bot run faster with minimax depth 4.
