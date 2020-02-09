import networkx as nx
import matplotlib.pyplot as plt
import numpy as np

class Visualization_Setup:

	def __init__(self, filename, match_dict, sep):

		unmatched_color = "#0066CC"
		matched_color   = "#66CC00"

		c = []
		angle = []
		angle_dict = {}
		names_dict ={}
		pos = {}

		h = open(filename, 'r') 
		z = h.readlines()
		h.close()

		j = 0
		n_nodes = len(match_dict)

		for node in range(0,n_nodes):

			q = z[ node ].split(sep)

			if match_dict[node] == 1:

				theta = 2.0*np.pi*j/n_nodes

				angle.append((np.cos(theta),np.sin(theta)))
				c.append(matched_color)

				angle_dict[j] = theta
				names_dict[j] = q[1]

				j = j + 1

		for node in range(0,n_nodes):

			q = z[ node ].split(sep)

			if match_dict[ node ] == -1:

				theta = 2.0*np.pi*j/n_nodes

				angle.append((np.cos(theta),np.sin(theta)))
				c.append(unmatched_color)

				angle_dict[j] = theta
				names_dict[j] = q[1]

				j = j + 1

		for node in range(0,n_nodes):
			pos[node] = angle[node]

		self.colors    = c
		self.positions = pos
		self.an_dict   = angle_dict
		self.na_dict   = names_dict

	def get_color_list(self):
		c = self.colors
		return c

	def get_positions_list(self):
		p = self.positions
		return p;

	def get_angles_dict(self):
		ad = self.an_dict
		return ad

	def get_names_dict(self):
		nd = self.na_dict
		return nd


def Visualize( G, names_dict, colors, pos, angle_dict ):
	
	ns = 50
	edge_col = "#B2FF66"
	margin=0.01

	fig, ax = plt.subplots(figsize=(13,13))
	fig.subplots_adjust(margin, margin, 1.-margin, 1.-margin)
	ax.axis('equal')

	nx.draw_networkx_nodes(G, pos, node_size = ns, node_color=colors, with_labels = False )

	print("Do you want to plot the links? Type 'Y'. Otherwise they will not be plotted ")

	if( input() == "Y"):
		nx.draw_networkx_edges(G,pos,node_size= ns, arrowstyle='->',arrowsize=10, edge_color = edge_col)

	description = nx.draw_networkx_labels(G,pos, labels=names_dict,font_size = 5)

	r = fig.canvas.get_renderer()
	trans = plt.gca().transData.inverted()

	for node, t in description.items():

		bb = t.get_window_extent(renderer=r)
		bbdata = bb.transformed(trans)
    
		radius = 1.05 +bbdata.width/1.5
		position = (radius*np.cos(angle_dict[node]),radius* np.sin(angle_dict[node]))

		t.set_position(position)
		t.set_rotation(angle_dict[node]*360.0/(2.0*np.pi))
		t.set_clip_on(False)

	plot_description = " E.Coli tanscription factors network \n blue: driver nodes \n green: controlled nodes"

	plt.text(0.8,0.9,plot_description, fontsize = 13)

	plt.show()

	print("insert the string 'close'  \n")
	visual_switch = input()

	if(visual_switch == "close"):
		plt.close('all')