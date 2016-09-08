import sys
from ROOT import gSystem
gSystem.Load("libmySoftware_NucleiPackage")
from ROOT import sample

try:

    print "PyROOT recognized your class %s" % str(sample)

except NameError:

    print "Failed importing NucleiPackage..."

sys.exit(0)

