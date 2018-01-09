'''
    usage:
    ---- - -- -- --
    python mac/dat_file_to_csv.py --infilename=RealParticles_Init_ALL --Nlines=10 -v2
'''
import sys, argparse
import matplotlib as mpl, pandas as pd , numpy as np
import input_flags , Initiation as init
from matplotlib import pyplot as plt
from my_tools import *

import ROOT
from ROOT import ReadDatFile

parser = argparse.ArgumentParser()
parser.add_argument('-path','--path', default='/Users/erezcohen/Desktop/GiBUU/release2017/myGiBUUrun/', type=str )
parser.add_argument('-infile','--infilename', default='RealParticles_Init_ALL', type=str )
parser.add_argument('-v','--verbose', default=0, type=int )
parser.add_argument('-N','--Nlines', default=1, type=int )

path = parser.parse_args().path
infilename = parser.parse_args().infilename
verbose = parser.parse_args().verbose
Nlines = parser.parse_args().Nlines

datfilename = path + infilename + '.dat'
csvfilename = path + infilename + '.csv'

print 'reading\n',datfilename,'\nand converting to\n',csvfilename

rd = ReadDatFile (datfilename,csvfilename)

rd.ReadDatFromFile( Nlines , verbose )

print_filename(csvfilename,'wrote to output file')
print 'done.'

