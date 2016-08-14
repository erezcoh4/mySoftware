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
    parser.add_argument('-o','--option', default=12, type=str )
    parser.add_argument('-var','--variable', default=12, type=str , help='variable to draw...')
    parser.add_argument('-mc','--MCmode', default='0', type=int )
    parser.add_argument('--cut', default='', type=ROOT.TCut , help='root TCut' )

    
    debug       = parser.parse_args().verbose
    print_mod   = parser.parse_args().print_mod
    worker      = parser.parse_args().worker
    atomic_mass = parser.parse_args().atomic_mass
    evnts_frac  = parser.parse_args().evnts_frac
    variable    = parser.parse_args().variable
    operation   = parser.parse_args().option
    MCmode      = parser.parse_args().MCmode
    files_frac  = parser.parse_args().files_frac
    cut         = parser.parse_args().cut
    
    if debug>0: print "flags: ", parser.parse_args()
    
    return parser.parse_args()

