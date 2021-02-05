import cppyy
import numpy as np
import ctypes
import time
from bqplot import Graph, LinearScale, ColorScale, Figure, Tooltip
from ipywidgets import HBox,Label,IntSlider,Button,Layout,interact,dlink,interactive
import ipywidgets as widgets
from string import ascii_uppercase
import os

dir=os.path.dirname(__file__)

cppyy.include(dir+"/features.h")

cppyy.load_library(dir+"/libGraph")

###
# Modifie la coloeur du print
###
class color:
   PURPLE = '\033[95m'
   CYAN = '\033[96m'
   DARKCYAN = '\033[36m'
   BLUE = '\033[94m'
   GREEN = '\033[92m'
   PINK = '\033[80m'
   YELLOW = '\033[93m'
   RED = '\033[91m'
   BOLD = '\033[1m'
   UNDERLINE = '\033[4m'
   END = '\033[0m'

####
# Initialisation des var pour créer graphe (version pour les Nuls)
###
def initvar():
    global _type
    _type=''
    global _method
    _method=''
    global _tab
    _tab=[]
    global _som
    _som=[]
    global _result_easy
    _result_easy=[]
    return _type,_method,_som,_tab,_result_easy

def resetvar():
    _type=''
    _method=''
    _tab=[]
    _som=[]
    
def reset():
    _nbIter=0
    historic = []
    _Substep = []
    _NbSubstep = []
    _Subcolor = []
    _Subpipe = []
    coor=[]    

def allColor(graph):
    i=0
    tab=[]
    for color in cppyy.gbl.listColor(graph):
        if(color==0):
            tab.append([i,'White'])
        if(color==1):
            tab.append([i,'Yellow'])
        if(color==2):
            tab.append([i,'Green'])
        if(color==3):
            tab.append([i,'Red'])
        if(color==4):
            tab.append([i,'Pink'])
        i=i+1
    return tab
#print(allColor(g))

def allPipe(graph):
    tab=[]
    for sommet in graph.getSommets():
        for pipe in sommet.getTuyauEntrantes():
            tab.append([pipe.getDebut().getNum(),pipe.getFin().getNum(),pipe.getCapacite(),pipe.getFlot(),pipe.getSens()])
    return tab
#print(allPipe(g))

def SolverGraph(graph, fordfulkerson,_nbSommet,_nbTuyau,historic,_Substep,_NbSubstep,_Subcolor,_Subpipe):
    historic.append([_nbSommet,_nbTuyau,allColor(graph),allPipe(graph)])
    list_som = graph.getSommets()
    bottle =  0
    ref_sommet =-1    
    iterate=1
    modif_flot = -1    
    while(modif_flot!= fordfulkerson.getFlotStep().back()):        
        list_som = graph.getSommets()        
        bottle = 0        
        ref_sommet = -1        
        for som in list_som:
            for neighbours in som.getTuyauSortantes():
                if(neighbours.getCapacite() >= bottle):
                    bottle = neighbours.getCapacite()        
        modif_flot = fordfulkerson.getFlotStep().back()
        #print(modif_flot)
        fordfulkerson.findFlotMax(graph, ctypes.c_int(bottle), ctypes.c_int(ref_sommet))
        fordfulkerson.displayFlotStep(graph)
        ffstep=fordfulkerson.getPythonStep()
        ffstep.reverse()
        _NbSubstep.append(fordfulkerson.getPythonNbStep())
        k=0
        r=0
        temp=[]
        _Subcolor=[]
        _Subpipe=[]
        iteration = len(ffstep)
        while(r<iteration):            
            subgraph = ffstep.back()
            ffstep.pop_back()
            _Subcolor.append(allColor(subgraph))
            _Subpipe.append(allPipe(subgraph))
            r=r+1 
        temp.append([_nbSommet,_nbTuyau,_Subcolor,_Subpipe])    
        _Substep.append([r,temp.pop()])
        k=k+r
        _nbSommet = graph.get_nbSommet()
        _nbTuyau = graph.get_nbTuyau()
        historic.append([_nbSommet,_nbTuyau,allColor(graph),allPipe(graph)])        
        for reset in graph.getSommets():
            reset.setCouleur(cppyy.gbl.Couleur.White);               
        iterate=iterate+1
    _nbIter=iterate
    return 0
#SolverGraph(g,ff,_nbSommet,_nbTuyau)

def recupIterMain(iterate, historic,graph,_nbSommet):
    temp=0
    node_data=[]
    colors=[]
    link_data=[]
    _actualIter=iterate    
    while(temp<_nbSommet):
        if(graph.getSommet(temp).isSource()):
            node_data.append('Source')
            #temp=temp+1
        else:
            if(graph.getSommet(temp).isPit()):
                node_data.append('Puit')
                #temp=temp+1
            else: 
                node_data.append(ascii_uppercase[temp])
        colors.append(historic[_actualIter][1][temp][1])            
        temp=temp+1
    for pipe in historic[_actualIter][2]:
            link_data.append({'source': pipe[0], 'target': pipe[1]})
    return (node_data,link_data,colors)
#node_data,link_data,colors=recupIterMain(0,taball)

def recupIter(iterate):
    temp=0
    node_data=[]
    colors=[]
    link_data=[]
    _actualIter=iterate    
    while(temp<_nbSommet):
        if(g.getSommet(temp).isSource()):
            node_data.append('Source')
            #temp=temp+1
        else:
            if(g.getSommet(temp).isPit()):
                node_data.append('Puit')
                #temp=temp+1
            else: 
                node_data.append(ascii_uppercase[temp])
                colors.append(historic[_actualIter][2][temp][1])            
        temp=temp+1
    for pipe in historic[_actualIter][3]:
            link_data.append({'source': pipe[0], 'target': pipe[1]})
    return (node_data,link_data,colors)
#node_data,link_data,colors=recupIter(0)

def recupSubIter(step,iterate):    
    temp=0
    node_data=[]
    colors=[]
    link_data=[]
    _actualIter=iterate    
    while(temp<_nbSommet):
        if(g.getSommet(temp).isSource()):
            node_data.append('Source')
        else:
            if(g.getSommet(temp).isPit()):
                node_data.append('Puit')
            else: 
                node_data.append(ascii_uppercase[temp])
        colors.append(_Substep[step][1][2][iterate][temp][1])            
        temp=temp+1
    for pipe in _Substep[step][1][3][iterate]:
            link_data.append({'source': pipe[0], 'target': pipe[1]})
    return (node_data,link_data,colors)

def print_event(self, target):
    global coor
    coor.append({'name' : target['data']['label'], 'x' : target['data']['x'], 'y' : target['data']['y']})
    return 0

def graph_dynamic():
    node_data,link_data,colors=recupSubIter(0,0)
    graph = Graph(node_data=node_data, link_data=link_data, charge=-600, colors=colors, directed=True,link_color=['Red'])
    graph.selected
    graph.on_element_click(print_event)         
    return Figure(marks=[graph], layout=fig_layout)    
#graph_dynamic()

def graph_static():
    node_data,link_data,colors=recupSubIter(0,0)
    for pos in coor:
        i=0
        while(i<_nbSommet): 
            if(pos['name']==node_data[i]):
                _x[i]=pos['x']
                _y[i]=pos['y']
                i=_nbSommet
            i=i+1
    j=0
    while(j<_nbSommet):
        if(_x[j]==0):
            _x[j]=sum(_x[:])/_nbSommet
        if(_y[j]==0):
            _y[j]=sum(_y[:])/_nbSommet
        j=j+1
    graph2 = Graph(node_data=node_data, link_data=link_data, colors=colors,
                  x=_x, y=_y,
                  link_type='line',link_color=['red' for i in range(_nbSommet)])
    return Figure(marks=[graph2], layout=fig_layout)    
#graph_static()

def concatTab(hist,subhist,miter,subiter,python):
    res = []
    #for i in range(miter):
    #    if(i==0):
    #        res.append([i,hist[i][2],hist[i][3]])
    #    for j in range(subiter[i]):
    #        res.append([(i*subiter[i])+j+1,subhist[i][1][2][j],subhist[i][1][3][j]])
    if(python):        
        for i in range(len(subhist[len(subhist)-1][1][2])):
            res.append([i,subhist[len(subhist)-1][1][2][i],subhist[len(subhist)-1][1][3][i]])
    else:
        for i in range(len(subhist[len(subhist)-1][1][2])):
            res.append([i,subhist[len(subhist)-1][1][2][i],subhist[len(subhist)-1][1][3][i]])    
    return res
#taball=concatTab(historic,_Substep,len(historic)-1,_NbSubstep)

def forSlider(x):
    node_data,link_data,colors=recupIter(x)
    graph = Graph(node_data=node_data, link_type='line', link_data=link_data, charge=-300, colors=colors, directed=True)
    return Figure(marks=[graph], layout=fig_layout)    
#interact(forSlider,x=(0,len(taball)-1))

def forSubSlider(x,y):
    node_data,link_data,colors=recupSubIter(x,y)
    graph = Graph(node_data=node_data,link_type='line', link_data=link_data, charge=-300, colors=colors, directed=True,link_color=['Red'])    
    return Figure(marks=[graph], layout=fig_layout)
#interact(forSubSlider,x=(0,len(_Substep[:])-1),y=(0,_NbSubstep[2]))

  
def forSliderMain(x,resultat):
    node_data,link_data,colors=recupIterMain(x,resultat)
    graphics.node_data = node_data
    graphics.link_data = link_data
    graphics.colors = colors 
    return Figure(marks=[graph])      
#interact(forSlider,x=(0,len(taball)-1))

def legendFlot():
    print("Légende : \n" +
           color.BOLD + "Le sommet blanc est le sommet pas encore traité \n" + color.END +
           color.YELLOW + "Le sommet jaune est le sommet traité (puisque c'est récursif nous pouvons traiter un sommet via un autre sommet) \n" + color.END + 
           color.PURPLE + "Le sommet rose est le sommet référence pour l'ajout du flot \n" + color.END +
           color.GREEN + "Le sommet vert est le sommet qui a été traité et terminer sur cette itération" + color.END)

def affichageFlot(resultat,etape,node_data):
    print("Flot dans le graphe à l'étape :", etape, sep=" ")
    for i in resultat[etape][2]:
        print(" flot entre", node_data[i[0]], "et", node_data[i[1]], ":", i[3], "/", i[2], sep = "  ")
    

def execute(graph, method, python=False ,initial_sommet=None):
    if(method=='FordFulkerson'):
        ff = cppyy.gbl.FordFulkerson(graph)
        _nbSommet = graph.get_nbSommet()
        _nbArete = graph.get_nbArete()
        _nbTuyau = graph.get_nbTuyau()
        _nbIter=0
        historic = []
        _Substep = []
        _NbSubstep = []
        _Subcolor = []
        _Subpipe = []
        coor=[]
        _x=[0 for i in range(_nbSommet)]
        _y=[0 for i in range(_nbSommet)]
        fig_layout = Layout(width='1000px', height='300px')
        
        SolverGraph(graph,ff,_nbSommet,_nbTuyau,historic,_Substep,_NbSubstep,_Subcolor,_Subpipe)
        result=concatTab(historic,_Substep,len(historic)-1,_NbSubstep,python)
        
        node_data,link_data,colors=recupIterMain(0,result,graph,_nbSommet)
        graphics = Graph(node_data=node_data,link_type='line', link_data=link_data, charge=-300, colors=colors, directed=True) 
                
        return result,graphics,_nbSommet,historic,_Substep


            ####################################################################
            ### FONCTIONS DE CONTROL DE CREATION DE GRAPHE PAR L'UTILISATEUR ###
            ####################################################################


# Vérifie qu'il n'y a pas 2 sommets identiques, qu'il y en a au moins 2 et moins de 30

def checkSommets(sommets):
    if(len(sommets) <= 1):
        print("error, you must have at least 2 nodes")
        return False
    elif(len(sommets) >= 30):
        print("error, too many nodes")
        return False
    else:
        for i in range(0, len(sommets)):
            for j in range(i+1, len(sommets)):
                if(sommets[i] == sommets[j]):
                    print("error, node {} already exists".format(j))
                    return False
    return True


#####################################
### Pour n'importe quel edge/pipe ###
#####################################

# Vérifie que les sommets entrants de chaque arete/tuyau existent dans l'ensemble des sommets

def checkStartEdges(sommets, edges):
    for i in range(0, len(edges)):
        flag = False
        for j in range(0, len(sommets)):
            if(edges[i][0] == sommets[j]):
                flag = True
                break
        if(flag == False):
            print("error, starting node of edge {} is unknown".format(i))
            return False
    return True

# Vérifie que les sommets sortants de chaque arete/tuyau existent dans l'ensemble des sommets

def checkEndEdges(sommets, edges):
    for i in range(0, len(edges)):
        flag = False
        for j in range(0, len(sommets)):
            if(edges[i][1] == sommets[j]):
                flag = True
                break
        if(flag == False):
            print("error, ending node of edge {} is unknown".format(i))
            return False
    return True

# Vérifie qu'il n'y ait pas d'arete/tuyau qui n'ait pas le même sommet en entrée et sortie

def checkCycleEdges(sommets, edges):
    for i in range(0, len(edges)):
        if(edges[i][0] == edges[i][1]):
            print("error, cycle are not allowed in edge {}".format(i))
            return False
    return True

# Vérifie qu'une arête/tuyau est unique

def checkUniqEdges(edges):
    for i in range(0, len(edges)):
        for j in range(i+1, len(edges)):
            if(edges[i][0] == edges[j][0]):
                if(edges[i][1] == edges[j][1]):
                    print("error, edge {} already exists".format(j))
                    return False
    return True

# Vérifie que le bon nombre de paramètre est donné lors de la création d'une arete/tuyau

def checkSizeEdges(edges, typeGraphe):
    if(typeGraphe == "Graph Flot"):
        for i in range(len(edges)):
            if(len(edges[i]) != 4):
                print("error, in edge {}, expected 4 parameters".format(i))
                return False
    else:
        for i in range(len(edges)):
            if(len(edges[i]) != 3):
                print("error, in edge {}, expected 3 parameters".format(i))
                return False
    return True    
      
                
#########################################
### Pour les tuyaux de Graph de flots ###
#########################################

# Vérifie que le flot ne dépasse pas la capacité, et que la capacité et le flot est positif

def checkFlotsValuesEdges(edges):
    for i in range(0, len(edges)):
        if(edges[i][2] < 0):
            print("error, negative capacity in edge {}".format(i))
            return False
        
        if(edges[i][3] < 0):
            print("error, negative flow in edge {}".format(i))
            return False
            
        if(edges[i][3] > edges[i][2]):
            print("error, flow value is above its own capacity in edge {}".format(i))
            return False
    return True

        
#####################
### Pour Dijkstra ###
#####################

# Vérifie qu'il n'y a pas d'aretes de poids négatif

def checkDijkstraNegatifEdges(edges):
    for i in range(0, len(edges)):
        if(edges[i][2] < 0):
            print("error, negative value in edge {}".format(i))
            return False
    return True



                ##########################################################################
                ### DOUANE, IMMIGRATION INTERDITE POUR LES FUTURS GRAPHS NON CONFORMES ###
                ##########################################################################

def prepreDouane(sommets, edges, typeGraphe, typePcc):
    if(preDouane(sommets, edges, typeGraphe, typePcc)):
        if(wid.value == "Graph Flot"):
            g = cppyy.gbl.createYourGraph(typeGraphe, sommets, edges)
            return g
        else:
            g = cppyy.gbl.createYourGraph(typePcc, sommets, edges)
            return g
    return None


def preDouane(sommets, edges, typeGraphe, typePcc):
    if(typeGraphe == "Graph Flot"):
        if(douane(sommets, edges, typeGraphe)):
            return True
    elif(typeGraphe == "Graph PCC"):        
        if(douane(sommets, edges, typePcc)):
            return True
    return False



def douane(sommets, edges, typeGraphe):
    if(checkSommets(sommets)):
        if(checkStartEdges(sommets, edges) and checkEndEdges(sommets, edges) and checkCycleEdges(sommets, edges) and checkUniqEdges(edges) and checkSizeEdges(edges, typeGraphe)):
            if(typeGraphe == "Dijkstra" and checkDijkstraNegatifEdges(edges)):
                return True
            elif(typeGraphe == "BellmanFord" or typeGraphe == "FloydWarshall"):
                return True
            elif(typeGraphe == "Graph Flot" and checkFlotsValuesEdges(edges)):
                return True
            else:
                return False
        else:
            return False
    else:
        return False


def createNodesPCC(g):
    som = []
    for s in g.getSommets():
        som.append(str(s.getVal()))
    return som

def createEdgesPCC(g):
    ar = []
    for s in g.getSommets():
        for a in s.getAretesSortantes():
            ar.append({'source': a.getDepart().getNum(), 'target': a.getArrivee().getNum()})
    return ar


def modifColor(graph, algo, typePcc, x):
    res = ['white'] * len(graph.getSommets())
    

    if(typePcc == "FloydWarshall"):
        res[algo.getHistorique()[x].getJ().getNum()] = 'green'
        res[algo.getHistorique()[x].getI().getNum()] = 'red'
    else:
        res[algo.getHistorique()[x].getSommetCible().getNum()] = 'green'
        res[algo.getHistorique()[x].getSommetActuel().getNum()] = 'red'

    return res



def displayCommentPCC(d, x, typePcc, som):
    if(typePcc == "Dijkstra"):

        commentaire = d.getHistorique()[x].getCommentaire()

        distances = []
        dist = d.getHistorique()[x].getDist()
        for i in dist:
            distances.append(i)
                        
        sommetsRestants = []
        h = d.getHistorique()[x].getLeft()
        for i in h:
            sommetsRestants.append(i.getNum())

        print("Commentaire : {}".format(commentaire))
        print("Sommets restants : {}".format(sommetsRestants))
        #print("Distances : {}".format(distances))
        print("Distances : ")
        for i in range(len(som)):
            if(i == 0):
                print("Sommet source {} : {}".format(som[i], distances[i]))
            else:
                print("Sommet {} : {}".format(som[i], distances[i]))


    elif(typePcc == "BellmanFord"):
        commentaire = d.getHistorique()[x].getCommentaire()

        distances = []
        dist = d.getHistorique()[x].getDist()
        for i in dist:
            distances.append(i)

        ite = d.getHistorique()[x].getIteration()

        print("Commentaire : {}".format(commentaire))
        print("Itération : {}".format(ite))
        #print("Distances : {}".format(distances))
        print("Distances : ")
        for i in range(len(som)):
            if(i == 0):
                print("Sommet source {} : {}".format(som[i], distances[i]))
            else:
                print("Sommet {} : {}".format(som[i], distances[i]))


    elif(typePcc == "FloydWarshall"):
        commentaire = d.getHistorique()[x].getCommentaire()
        print("Commentaire : {}".format(commentaire))
        print("K : {}".format(d.getHistorique()[x].getK().getNum()))
        print("J : {}".format(d.getHistorique()[x].getI().getNum()))
        print("I : {}".format(d.getHistorique()[x].getJ().getNum()))

        for i in range(len(d.getHistorique()[x].getDist())):
            for j in range(len(d.getHistorique()[x].getDist()[i])):
                print(d.getHistorique()[x].getDist()[i][j], end=', ')
            print("")



    else:
        commentaire = d.getHistorique()[x].getCommentaire()
        print(commentaire)


def createAlgoPcc(a, g):
    if(a == "Dijkstra"):
        res = cppyy.gbl.Dijkstra(g, g.getSommet(0))
        return res
    elif(a == "BellmanFord"):
        res = cppyy.gbl.BellmanFord(g, g.getSommet(0))
        return res
    elif(a == "FloydWarshall"):
        res = cppyy.gbl.FloydWarshall(g)
        return res
    else:
        return "error"


def prepreDouane(sommets, edges, typeGraphe, typePcc):
    if(preDouane(sommets, edges, typeGraphe, typePcc)):
        if(wid.value == "Graph Flot"):
            g =  cppyy.gbl.createYourGraph(typeGraphe, sommets, edges)
            return g
        else:
            g = cppyy.gbl.createYourGraph(typePcc, sommets, edges)
            return g
    return None   

################################################
# Partie code création de graphe pour les nuls!!
################################################

wid=widgets.RadioButtons(    
    options=['Graph PCC', 'Graph Flot'],
    value='Graph PCC',
    disabled=False,
)

nb_sommit=widgets.IntSlider(
    value=5,
    min=2,
    max=30,
    step=1,
    disabled=False,
    continuous_update=False,
    orientation='horizontal',
    readout=True,
    readout_format='d'
)

nb_link=widgets.IntSlider(
    value=1,
    min=1,
    max=100,
    step=1,
    disabled=False,
    continuous_update=False,
    orientation='horizontal',
    readout=True,
    readout_format='d'
)

pcc=widgets.RadioButtons(    
    options=['Dijkstra', 'BellmanFord', 'FloydWarshall'],
    value='Dijkstra',
    disabled=False,
)

flot=widgets.RadioButtons(    
    options=['FordFulkerson'],
    value='FordFulkerson',
    disabled=False,
)

check=widgets.Checkbox(
    value=False,
    description='Fini?',
    disabled=False,
    indent=False
)

choosemethod=widgets.RadioButtons(    
    options=['Easy_Method', 'Coding_Method'],
    value='Easy_Method',
    disabled=False,
)

def fin_init(b):
    check.disabled=True
    flot.disabled=True
    pcc.disabled=True
    nb_link.disabled=True
    nb_sommit.disabled=True
    wid.disabled=True
    choosemethod.disabled=True
        
check.observe(fin_init)

def choosealgo(wid):
    if(wid.value=='Graph PCC'):
        return pcc
    else:
        return flot

easy=widgets.VBox([widgets.Label('Choose your number of nodes:'),nb_sommit,
                   #widgets.Label('Choose your number of edges:'),nb_link,
                   check
                 ])

add=widgets.Button(
    description='Add edge',
    disabled=False,
    button_style='', # 'success', 'info', 'warning', 'danger' or ''
    tooltip='Add edge',
    icon='' # (FontAwesome names without the `fa-` prefix)
)

def on_button_clicked(b):
    if(wid.value=='Graph PCC'):        
        if(pcc.value=='Dijkstra'):            
            _tab.append([accordion.children[0].value,accordion.children[1].value,accordion.children[2].value])
            print(_tab)
        else:
            _tab.append([accordion.children[0].value,accordion.children[1].value,accordion.children[2].value])
            print(_tab)
    else:
            _method=flot.value
            _tab.append([accordion.children[0].value,accordion.children[1].value,accordion.children[2].value,
                     accordion.children[3].value])     
            print(_tab)
    add.description='Added (wait 2sec)'
    add.tooltip='Added (wait 2sec)'
    add.button_style='success'
    add.icon='check'
    add.disabled=True
    time.sleep(2)
    add.description='Add edge'    
    add.button_style=''
    add.tooltip='Add edge'
    add.icon=''
    add.disabled=False   

def createvertice(accordion,_tab):
    if(check.value):        
        print('Create your edge:')
        if(wid.value=='Graph PCC'):
            if(pcc.value=='Dijkstra'):
                return widgets.VBox([accordion,add])
            else:                
                return widgets.VBox([accordion,add])
        else:                        
            return widgets.VBox([accordion,add]) 
        
fin=widgets.Button(
    description='Finish?',
    disabled=False,
    button_style='', # 'success', 'info', 'warning', 'danger' or ''
    tooltip='Finish?',
    icon='' # (FontAwesome names without the `fa-` prefix)
)

def on_button_fin(b):
    fin.description='Step1 finish'
    fin.tooltip='Step1 finish'
    fin.button_style='success'
    fin.icon='check'
    fin.disabled=True
    add.description='NotActive'
    add.tooltip='NotActive'
    add.disabled=True
    erase.description='NotActive'
    erase.tooltip='NotActive'
    erase.disabled=True
    clear.description='NotActive'
    clear.tooltip='NotActive'
    clear.disabled=True
    sommet=0    
    while(sommet<nb_sommit.value):
        _som.append(sommet)
        sommet=sommet+1
    _type=wid.value
    if(wid.value=='Graph PCC'):
        _method=pcc.value
    else:
        _method=flot.value
    _result_easy.append(_som)
    _result_easy.append(_tab)
    _result_easy.append(_type)
    _result_easy.append(_method)
    
def pro_mode(_som,_tab):
    _result_easy[:]=[]
    _type=wid.value
    if(wid.value=='Graph PCC'):
        _method=pcc.value
    else:
        _method=flot.value  
    _result_easy.append(_som)
    _result_easy.append(_tab)
    _result_easy.append(_type)
    _result_easy.append(_method)    
    
normal_sommet=widgets.Textarea(
    value='example : [0,1,2,3]',
    placeholder='Type something',
    description='Sommet :',
    disabled=False
)

normal_edge=widgets.Textarea(
    value='example : \n PCC: [[0,1,10], [1,2,5.8]] \n Flot : [[0,1,10,5] , [0,3,20,8] ]',
    placeholder='Type something',
    description='Edge :',
    disabled=False
)

fin.on_click(on_button_fin)

check_normal=widgets.Button(
    value=False,
    description='Fini?',
    disabled=False,
    indent=False
)

def fin_init_normal(b):    
    check_normal.disabled=True
    check_normal.description='Go_to_Next_Step'
    check_normal.button_style='success'
    flot.disabled=True
    pcc.disabled=True
    normal_sommet.disabled=True
    normal_edge.disabled=True
    wid.disabled=True
    choosemethod.disabled=True
    _type=wid.value
    _method=pcc.value
    _result_easy.append(normal_sommet.value)
    _result_easy.append(normal_edge.value)
    _result_easy.append(_type)
    _result_easy.append(_method)
    
        
check_normal.on_click(fin_init_normal)

erase=widgets.Button(
    description='Supprime',
    disabled=False,
    button_style='', # 'success', 'info', 'warning', 'danger' or ''
    tooltip='erase edge',
    icon='' # (FontAwesome names without the fa- prefix)
)

clear=widgets.Button(
    description='Clear',
    disabled=False,
    button_style='', # 'success', 'info', 'warning', 'danger' or ''
    tooltip='clear edges',
    icon='' # (FontAwesome names without the fa- prefix)
)
def on_eraseButton_clicked(b):
    if(len(_tab) > 0):
        _tab.pop()
        print(_tab)

def on_clearButton_clicked(b):
    _tab[:] = []
    print(_tab)


normal=widgets.VBox([normal_sommet,normal_edge,check_normal])

def chooseTypeGraph():
    return widgets.VBox([widgets.Label('Choose your type of graph:'),
                  wid,
                  widgets.Label('Choose your solver algorithm:'),
                  choosealgo(wid),
                  #widgets.Label('Choose your way to create your graph:'),
                  #choosemethod,
                 ])

def EasyGraphNbNodes():
    if(choosemethod.value=='Easy_Method'):
        return easy
    else:
        return normal

def EasyGraph(tab):
    if(choosemethod.value=='Easy_Method'):
        global accordion
        if(wid.value=='Graph PCC'):        
            if(pcc.value=='Dijkstra'):
                accordionD = widgets.Accordion(children=[widgets.Dropdown(options=range(nb_sommit.value)), widgets.Dropdown(options=range(nb_sommit.value)),widgets.IntSlider()], titles=('SommetDebut','SommetFin','Distance'))
                accordionD.set_title(0, 'SommetDebut')
                accordionD.set_title(1, 'SommetFin')
                accordionD.set_title(2, 'Distance')
                accordion=accordionD
            else:
                accordionPCC = widgets.Accordion(children=[widgets.Dropdown(options=range(nb_sommit.value)), widgets.Dropdown(options=range(nb_sommit.value)),widgets.IntSlider(min= -50,max=50)], titles=('SommetDebut','SommetFin','Distance'))
                accordionPCC.set_title(0, 'SommetDebut')
                accordionPCC.set_title(1, 'SommetFin')
                accordionPCC.set_title(2, 'Distance')
                accordion=accordionPCC
        else:
            accordionFlot = widgets.Accordion(children=[widgets.Dropdown(options=range(nb_sommit.value)), widgets.Dropdown(options=range(nb_sommit.value)),widgets.IntSlider(),widgets.IntSlider()], titles=('SommetDebut','SommetFin','Capacite','Flot'))
            accordionFlot.set_title(0, 'SommetDebut')
            accordionFlot.set_title(1, 'SommetFin')
            accordionFlot.set_title(2, 'Capacite')
            accordionFlot.set_title(3, 'Flot')
            accordion=accordionFlot
    

        add.on_click(on_button_clicked)
        erase.on_click(on_eraseButton_clicked)
        clear.on_click(on_clearButton_clicked)
        return widgets.VBox([createvertice(accordion,tab), erase, clear, fin])
    else:
        return normal    

def Mode_confirmer():
    sommet= eval(input("Tableaux de sommet : "))
    edge= eval(input("Tableaux d'arête/tuyau : "))
    return sommet,edge