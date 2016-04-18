import sys , ROOT
from ROOT import TPlots , ppElastic
plot = TPlots()
pp_elastic = ppElastic()
from rootpy.interactive import wait
sys.path.insert(0, '/Users/erezcohen/larlite/UserDev/mySoftware/MySoftwarePackage/mac')
import Initiation as init
init.createnewdir()
ROOT.gStyle.SetOptStat(0000)





pp_elastic.CreateXsec()

c = pp_elastic.DrawXsec()
c.Update()
wait()
c.SaveAs(init.dirname()+"/ppElasticXsec.pdf")






