import ROOT , sys , os , time
from ROOT import TPlots

#from rootpy.interactive import wait
sys.path.insert(0, '/Users/erezcohen/larlite/UserDev/mySoftware/MySoftwarePackage/mac')
#import Initiation as init
#init.createnewdir()
ROOT.gStyle.SetOptStat(0000)


PmissTit        = "|#vec{p}_{miss}| [GeV/c]"
PrecTit         = "|#vec{p}_{recoil}| [GeV/c]"
PcmTit          = "|#vec{p} (c.m.)| [GeV/c]"
Q2Tit           = "Q^{2} (GeV/c) ^{2}"
XbTit           = "Bjorken x"
qp1p2Tit        = "#sqrt{|q - p_{1} - p_{2}|^{2} } [GeV/c ^{2}]"
WeTit           = "W_{e} ~ #sqrt{|M^{2}_{p} + 2M_{p}#omega - Q^{2}|} [GeV/c ^{2}]"
We2Tit          = "W^{2}_{e} ~ M^{2}_{p} + 2M_{p}#omega - Q^{2} (GeV/c ^{2}) ^{2}"
Wseely2Tit      = "W^{2}_{seely} = (#omega+M_{p})^{2} - |#vec{q}|^{2} (GeV/c ^{2}) ^{2}"
WmissTit        = "#sqrt{|3M_{N} + q - p_{1} - p_{2}|^{2} } [GeV/c ^{2}]"
WmCmTit         = "#sqrt{ |(3M_{N},#vec{k}_{cm}) + q - p_{1} - p_{2}|^{2} } [GeV/c ^{2}]"
WmEpsTit        = "#sqrt{ |(3M_{N}-#varepsilon,#vec{k}_{cm}) + q - p_{1} - p_{2}|^{2} } [GeV/c ^{2}]"
PmqTit          = "|#vec{p}_{miss} #hat{q}|"
PrecqTit        = "#vec{p}_{rec} #hat{q}"
ThetaPrecTit    = "#theta(#vec{p}_{rec} = #vec{p}_{1} + #vec{p}_{2}) [deg.]"
ThetaPrctTit    = "#theta(#vec{q} - #vec{p}_{1} - #vec{p}_{2}) [deg.]"

def pTit(i):
    return "|#vec{p}(%d)| [GeV/c]"%i

def ThetaTit(name):
    return "#theta_{%s} [deg.]"%name

def cosThetaTit(name):
    return "cos ( #theta_{%s} )"%name




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
#    c.SaveAs(init.dirname()+"/"+name+".pdf")

    return c


