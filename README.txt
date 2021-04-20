NetworK.c, Tree.c, Network.h
These 3 create a networks of location by first reading the location file and create tree of all location
then read the flights file to create network with location as vertex and flights as edges

## Usage
network(); ->

createTree(); # create the tree from location file
traverseInOrder(pTree->root,&addVertex); # add vertex with information from tree
createFlights(pTree->root); # create flight from flight file