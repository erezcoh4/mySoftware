import ROOT , argparse
#form ROOT import *

def get_args():
    
    parser = argparse.ArgumentParser()
    parser.add_argument('-v','--verbose', default='1', type=int , help='\n0 - quiet,\n1 - major functionality,\n2 - print out all sorts of shit')
    parser.add_argument('-p','--print_mod', default='1000', type=int , help='print every how many entries')
    parser.add_argument('-evf','--evnts_frac', default='1', type=float , help='fraction of events to run over')
    parser.add_argument('-ff','--files_frac', default='0.01', type=float , help='fraction of files to process')
    parser.add_argument('-w','--worker', default='erez', type=str )
    parser.add_argument('-A','--atomic_mass', default=12, type=int )
    parser.add_argument('-o','--option', default='', type=str )
    parser.add_argument('-var','--variable', default='', type=str , help='variable to draw...')
    parser.add_argument('-data','--DataType', default='data', type=str )
    parser.add_argument('-scheme','--SchemedType', default='SRCPmissXb', type=str )
    parser.add_argument('--cut', default='', type=ROOT.TCut , help='root TCut' )
    parser.add_argument('--Nbins', default='50', type=int , help='number of bins' )
    parser.add_argument('--Ev', default='0', type=float , help='neutrino energy [GeV]' )
    parser.add_argument('-r','--run', default='0', type=int , help='run number' )
    parser.add_argument('-nruns', '--NumberOfRuns', default=0, type=int , help='number of runs to run...' )
    parser.add_argument('-core','--i_core', default=0, type=int , help='start the counting from i_core=0' )
    parser.add_argument('-mccv','--MCCversion', default=7, type=int , help='MCC version 7/8/...' )
    parser.add_argument('-mA', default=0.99, type=float , help='QE axial mass' )

    
    debug       = parser.parse_args().verbose
    print_mod   = parser.parse_args().print_mod
    worker      = parser.parse_args().worker
    atomic_mass = parser.parse_args().atomic_mass
    evnts_frac  = parser.parse_args().evnts_frac
    variable    = parser.parse_args().variable
    operation   = parser.parse_args().option
    DataType    = parser.parse_args().DataType
    SchemedType = parser.parse_args().SchemedType
    files_frac  = parser.parse_args().files_frac
    cut         = parser.parse_args().cut
    Nbins       = parser.parse_args().Nbins
    Ev          = parser.parse_args().Ev
    run         = parser.parse_args().run
    i_core      = parser.parse_args().i_core
    Nruns       = parser.parse_args().NumberOfRuns
    MCCversion  = parser.parse_args().MCCversion
    mA          = parser.parse_args().mA
    
    if debug>0: print "flags: ", parser.parse_args()
    
    return parser.parse_args()

