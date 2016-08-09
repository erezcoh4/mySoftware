import argparse

def get_args():
    
    parser = argparse.ArgumentParser()
    parser.add_argument('-v','--verbose', default='1', type=int , help='\n0 - quiet,\n1 - major functionality,\n2 - print out all sorts of shit')
    parser.add_argument('-p','--print_mod', default='1000', type=int , help='print every how many entries')
    parser.add_argument('-evf','--evnts_frac', default='1', type=float , help='fraction of events to run over')
    parser.add_argument('-w','--worker', default='erez', type=str )
    parser.add_argument('-A','--atomic_mass', default=12, type=int )
    
    
    debug = parser.parse_args().verbose
    print_every_entry = parser.parse_args().print_mod
    worker = parser.parse_args().worker
    atomic_mass = parser.parse_args().atomic_mass
    evnts_frac = parser.parse_args().evnts_frac
    
    if debug>0: print "flags: ", parser.parse_args()
    
    return parser.parse_args()

