import ROOT , sys , os , time
from ROOT import TPlots

from rootpy.interactive import wait
sys.path.insert(0, '/Users/erezcohen/larlite/UserDev/mySoftware/MySoftwarePackage/mac')
import Initiation as init
init.createnewdir()
ROOT.gStyle.SetOptStat(0000)

def plot(ana , name, plot_args):
    
    c = ana.CreateCanvas(name)
    
    if len(plot_args) < 9:
        ana.H1(plot_args[0] , plot_args[1] , "hist" , plot_args[2] , plot_args[3] , plot_args[4] , "" ,plot_args[5] , "" ,38)
        var = plot_args[0]

    else:
        ana.H2(plot_args[0] , plot_args[1], plot_args[2] , "colz" , plot_args[3] , plot_args[4] , plot_args[5], plot_args[6] , plot_args[7] , plot_args[8] , "" ,plot_args[9] , plot_args[10] , 1, 20 , 3 )
        var = plot_args[0] + "_vs_" + plot_args[1]
    
    print "ploting " + var + " from " + name
    c.Update()
    wait()
    c.SaveAs(init.dirname()+"/"+name+".pdf")

    return


