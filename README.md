# wordsearch
Description: Finding a word in a letter matrix

Potential Solutions:
1. 
    -[hard find] i could hardcode a function to go over the whole matrix and then once it finds a letter, restart the loop and looks for adjacent and diagonal letters, then repeats.
    -however, how would i make sure that each path is taken?

2.
    -[graph theory] a depth-first-search (DFS) could be implemented. I think this might be the best choice