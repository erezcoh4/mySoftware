'''
    usage:
    --------
    Energy2Momentum -particle=proton -KE=0.1
    in GeV and GeV/c
'''

import argparse ,os, sys , math
#sys.path.insert(0, '/Users/erezcohen/larlite/UserDev/mySoftware/MySoftwarePackage/mac')
#import input_flags
#flags = input_flags.get_args()

print 'usage:\n-------\nEnergy2Momentum -particle=proton -KE=0.1'

parser = argparse.ArgumentParser()
parser.add_argument('--particle', default='proton', type=str , help='particle type')
parser.add_argument('-p','--Momentum', default=-1, type=float , help='in GeV/c')
parser.add_argument('-E','--Energy', default=-1, type=float , help='in GeV')
parser.add_argument('-KE','--KineticEnergy', default=-1, type=float , help='in GeV')

particle = parser.parse_args().particle


if particle=="proton":
    mass = 0.938
elif particle=="neutron":
    mass = 0.939
if particle=="electron":
    mass = 0.000511
if particle=="muon":
    mass = 0.1056
if particle=="pion":
    mass = 0.139

if parser.parse_args().Momentum<0 and parser.parse_args().Energy<0 and parser.parse_args().KineticEnergy<0:
    print "\n\nusage:\n--------\nEnergy2Momentum -particle=proton -KE=0.1 \n[in GeV and GeV/c]\n\n"
    exit(0)

if parser.parse_args().Momentum<0:
    KineticEnergy = parser.parse_args().KineticEnergy
    energy = KineticEnergy + mass
    Momentum = math.sqrt( energy*energy - mass*mass )

elif parser.parse_args().Energy<0 or parser.parse_args().KineticEnergy<0:
    Momentum = parser.parse_args().Momentum
    energy = math.sqrt( Momentum*Momentum + mass*mass )
    KineticEnergy = energy - mass


print 'particle type: ', particle
print 'momentum = %.3f GeV/c'%Momentum
print 'kinetic energy = %.3f GeV'%KineticEnergy
print 'energy = %.3f GeV'%energy
print 'mass = %.3f GeV/c2'%mass
