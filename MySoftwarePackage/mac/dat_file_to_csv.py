'''
    usage:
    ---- - -- -- --
    python mac/dat_file_to_csv.py --infilename=RealParticles_Final_ALL --Nlines=10 -v2
    python mac/dat_file_to_csv.py --infilename=DoHIA_pert --Nevents=1 -v2
    python mac/dat_file_to_csv.py --infilename=DoHIA_pert --Nlines=10 -v2
'''
import sys, argparse
import matplotlib as mpl, pandas as pd , numpy as np
import input_flags , Initiation as init
from matplotlib import pyplot as plt
from my_tools import *

import ROOT
from ROOT import ReadDatFile

parser = argparse.ArgumentParser()
parser.add_argument('-path','--path', default='/Users/erezcohen/Desktop/GiBUU/release2017/NNtransparency/', type=str )
parser.add_argument('-infile','--infilename', default='RealParticles_Init_ALL', type=str )
parser.add_argument('-v','--verbose', default=0, type=int )
parser.add_argument('-Nlns','--Nlines', default=-1, type=int )
parser.add_argument('-Nevt','--Nevents', default=1, type=int )

path = parser.parse_args().path
infilename = parser.parse_args().infilename
verbose = parser.parse_args().verbose
Nlines = parser.parse_args().Nlines
Nevents = parser.parse_args().Nevents

datfilename = path + infilename + '.dat'
datfiletype = infilename
csvfilename = path + infilename + '.csv'

print 'reading\n',datfilename,'\nand converting to\n',csvfilename

rd = ReadDatFile (datfilename,csvfilename,datfiletype)

rd.ReadDatFromFile( Nlines , verbose , Nevents)

print_filename(csvfilename,'wrote to output file')
print 'done.'

