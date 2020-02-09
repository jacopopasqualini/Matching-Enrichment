import networkx as nx
import matplotlib.pyplot as plt
import numpy as np

class Match_Dict:
	""" A class that reads a file with two columns with format "id label" that
	identifies matched/ unmatched nodes in the network"""
	def __init__(self, filename):
		 
		f = open( filename, 'r')
		x = f.readlines()
		f.close()

		nn = len(x)

		self.n_nodes = nn

		match_dict ={}

		for i in range(0,nn) :

			q = x[i].split(" ")

			if q[1] == "1":
				match_dict[i] = 1

			if q[1] == "-1": 
				match_dict[i] = -1

		self.m_dict = match_dict


	def number_of_nodes(self):
		n = self.n_nodes
		return n

	def content(self):
		m = self.m_dict
		return m

class Links:

	def __init__(self,filename):

		b = open(filename, 'r')
		y = b.readlines()
		b.close()

		nl = len(y)

		self.n_links = nl

		ed = np.zeros(2*nl).reshape(nl,2)

		shift = 0
		print("Node labels start from 0 or 1?")
		l = input()

		if(int(l)==1):
			shift = 1

		for i in range(0,nl):
			q = y[i].split(" ")
			ed[i,0] = int(q[0])-shift
			ed[i,1] = int(q[1])-shift

		self.link_list = ed

	def number_of_links(self):
		l = self.n_links
		return l

	def content(self):
		e = self.link_list
		return e
