# Cannibals And Missionaries

Small C++ code that solves [Cannibals and missionaries riddle](https://en.wikipedia.org/wiki/Missionaries_and_cannibals_problem).

## The problem
Three missionaries and three cannibals are trying to cross the river in a boat. To do so, some rules must be obeyed:
 - At least one person (cannibal or missionary) must be in a boat while crossing the river.
 - Boat cannot carry more than three persons.
 - Number of missionaries on each riverbank or in the boat, must always be equal or greater than number of cannibals  
 
## The solution
Program presents step by step solution of river crossing. 
Output for 3 cannibals `(C)`, 3 missionaries `(M)` and boat `(*)` with capacity of 3 is as follows:

- `Source: 3C:3M* Destination 0C:0M` 3 cannibals and 3 missionaries are on source riverbank, with boat
- `Source: 0C:3M Destination 3C:0M*` 3 cannibals crossed the river and are now on destination bank
- `Source: 1C:3M* Destination 2C:0M`
- `Source: 1C:0M Destination 2C:3M*`
- `Source: 2C:0M* Destination 1C:3M`
- `Source: 0C:0M Destination 3C:3M*`

It is possible to variate number of cannibals, missionaries and boat capacity by changing variables missioanriesCount, cannibalsCount and boatCapacity. However, some problems do not have a solution and there is also build in maximum combination limit.
