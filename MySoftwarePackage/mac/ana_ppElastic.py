import sys , ROOT
from ROOT import TPlots , ppElastic
plot = TPlots()
pp_elastic = ppElastic()
from rootpy.interactive import wait
sys.path.insert(0, '/Users/erezcohen/larlite/UserDev/mySoftware/MySoftwarePackage/mac')
import Initiation as init
init.createnewdir()
ROOT.gStyle.SetOptStat(0000)


DoDrawAlphas    = False
DoDrawXsec      = False
DoRuffleTheta   = True


pp_elastic.CreateAlphas()
pp_elastic.CreateXsec()

if DoDrawAlphas:
    c = pp_elastic.DrawAlphas()
    c.Update()
    wait()
    c.SaveAs(init.dirname()+"/ppElasticAlphas.pdf")

if DoDrawXsec:
    c = pp_elastic.DrawXsec()
    c.Update()
    wait()
    c.SaveAs(init.dirname()+"/ppElasticXsec.pdf")


if DoRuffleTheta:
    Mpp = 2.8 # GeV/c2
    N = 5e4
    h = ROOT.TH1F("h3","Mp = %.2f GeV/c ^{2} ; #theta [deg.]"%Mpp,100 , 0  , 180)
    for i in range(0,int(N)):
        theta = pp_elastic.RandomTheta(Mpp)
        h.Fill(theta)
        if (i%(N/10)==0):
            print "%.0f%%, m(pp) = %.1f GeV/c2, theta = %.1f"%(100*i/N,Mpp,theta)
    h.Draw("hist")
    wait()





