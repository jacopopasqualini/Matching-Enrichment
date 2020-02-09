import networkx as nx
import matplotlib.pyplot as plt
import numpy as np

from VisualUtilities import Visualization_Setup
from VisualUtilities import Visualize

from NetworkUtilities import Match_Dict
from NetworkUtilities import Links

print("\n \n \n				*** V I S U A L I Z A T I O N ***			 \n \n \n")



# create a nx directed graph
G = nx.DiGraph();

print(" Insert data directory path: \n")
directory = input()

print("\n						--- MATCH DATA EXTRACTION \n \n \n")
print("Insert file name:")

# upload of match/unmatch dictionary - for labeling - and add them to the network
md = Match_Dict( directory + input() )
match_dict = md.content()
G.add_nodes_from( match_dict )

print("\n						--- LINKS DATA EXTRACTION \n \n \n")
print("Insert file name:")

# upload of link couples - for labeling - and add them to the network
lk = Links( directory + input() )
G.add_edges_from( lk.content() )

print("\n						--- NAMES DATA EXTRACTION \n \n \n")
print("Insert file name:")
names_file = directory + input()

print("Insert separation format : ")
sep = input()

# build all visualization items, feed them into vilualization
V = Visualization_Setup( names_file , match_dict, sep)

Visualize(G,V.get_names_dict(),V.get_color_list(),V.get_positions_list(),V.get_angles_dict())