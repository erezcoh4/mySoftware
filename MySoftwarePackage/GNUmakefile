# my software package

# specific names for this package
DICT  = MySoftware_MySoftwarePackageDict
SHLIB = libMySoftware_MySoftwarePackage.so
SOURCES = $(filter-out $(DICT).cxx, $(wildcard *.cxx))
FMWK_HEADERS = LinkDef.h $(DICT).h
HEADERS = $(filter-out $(FMWK_HEADERS), $(wildcard *.h))
OBJECTS = $(SOURCES:.cxx=.o)

# include options for this package
INCFLAGS  = -I.                       #Include itself

# platform-specific options
OSNAME          = $(shell uname -s)
HOST            = $(shell uname -n)
OSNAMEMODE      = $(OSNAME)

# call kernel specific compiler setup
include $(LARLITE_BASEDIR)/Makefile/Makefile.${OSNAME}

# set linker flags
LDFLAGS += -L$(shell root-config --libdir) -lEG -lSpectrum -lHist 
# this i had to add since i have RooFit only on root-5 installation, and i don’t want to ruin my root-6 installation by accident when trying to also install RooFit on it…
LDFLAGS += -L /Users/erezcohen/root-v5-34/lib/root -lRooFit -lRooFitCore -lRooStats


# call the common GNUmakefile
include $(LARLITE_BASEDIR)/Makefile/GNUmakefile.CORE
