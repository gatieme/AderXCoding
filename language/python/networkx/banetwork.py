#coding:utf-8#coding:utf-8
import networkx as nx
import matplotlib.pyplot as plt
from networkx.generators.classic import empty_graph, path_graph, complete_graph
#from networkx.random_graphs import *
import sys
import random
#
def _random_subset(seq,m):
    """ Return m unique elements from seq.

    This differs from random.sample which can return repeated
    elements if seq holds repeated elements.
    """
    targets = set()
    while len(targets)<m:
        x = random.choice(seq)
        targets.add(x)
    return targets

# ceraete count random numbers which sum  is  count
def _random_subsum(sum, count):
    targets = set( )

    while len(targets) < count - 1:
        num = random.uniform(0, sum)
        targets.add(num)
        sum -= num

    targets.add(sum)

    return targets;




#in D:\SoftwareEngineer\Python\Python2\Lib\site-packages\networkx\generators\random_graphs.py
def barabasi_albert_graph(n, m, seed=None):

    if m < 1 or  m >=n:
        raise nx.NetworkXError("Barabási–Albert network must have m >= 1"
                               " and m < n, m = %d, n = %d" % (m, n))
    if seed is not None:
        random.seed(seed)

    # Add m initial nodes (m0 in barabasi-speak)
    G=nx.empty_graph(n, create_using = nx.DiGraph())
    G.name="barabasi_albert_graph(%s,%s)"%(n,m)
    # Target nodes for new edges
    targets=list(range(m))
    print targets
    # List of existing nodes, with nodes repeated once for each adjacent edge
    repeated_nodes=[]
    # Start adding the other n-m nodes. The first node is m.
    source = m
    print "NODES : ", G.nodes( )

    #  add edges
    while source < n:
        # Add edges to m nodes from the source.

        #G.add_edges_from(zip([source] * m,targets))
        G.add_weighted_edges_from(zip([source] * m,targets, [-1]))
        
        print "ADD EDGES : ", zip([source] * m, targets, [-1])

        # Add one node to the list for each new edge just created.
        repeated_nodes.extend(targets)
        # And the new node "source" has m edges to add to the list.
        repeated_nodes.extend([source]*m)
        # Now choose m unique nodes from the existing nodes
        # Pick uniformly from repeated_nodes (preferential attachement)
        targets = _random_subset(repeated_nodes,m)
        source += 1

    # add weight
    print "NODES : ", G.number_of_edges(), G.nodes( )    
    print "EDGES : ", G.out_edges( )

                                    
    print "DEGREEE : ", G.out_degree( )

    for node in G.nodes( ):                             # each node
        weights = _random_subsum(1, G.out_degree(node))     # random node's all degress edges, create degree weight which sum is 1
        print node, G.edges(node), weights
        for ((x, y), weight) in zip(G.edges(node), weights):
            #print x, y, weight
            G[x][y]['weight'] = weight

            print "EDGE = ", (x, y), G.get_edge_data(x, y)
    return G
    

def show_barabasi_albert_graph(G):
    fp = open("bagragh.txt", "w")    
    for n,nbrs in G.adjacency_iter():
        for nbr,eattr in nbrs.items():
            data=eattr['weight']
            line = str(n) + "\t" + str(nbr) + "\t" + str(data) + "\n"
            print line
            fp.writelines(line)
    fp.close( )
        
if __name__ == '__main__':
    reload(sys)
    sys.setdefaultencoding("utf-8")
    #BA= nx.random_graphs.barabasi_albert_graph(20,1)  #生成n=20、m=1的BA无标度网络
    BA = barabasi_albert_graph(77, 1)
    
    show_barabasi_albert_graph(BA)

    pos = nx.spring_layout(BA)          #定义一个布局，此处采用了spring布局方式
    nx.draw(BA, pos, with_labels = False, node_size = 30)
    plt.show()


