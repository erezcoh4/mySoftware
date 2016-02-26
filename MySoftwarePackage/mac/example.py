import sys
from ROOT import gSystem
gSystem.Load("libMySoftware_MySoftwarePackage")
from ROOT import sample

try:

    print "PyROOT recognized your class %s" % str(sample)

except NameError:

    print "Failed importing MySoftwarePackage..."

sys.exit(0)

