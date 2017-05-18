import sys, pandas as pd, numpy as np , ast
import ROOT , time , os, sys , math , datetime
import matplotlib.pyplot as plt
import matplotlib as mpl
import seaborn as sns; sns.set(style="white", color_codes=True , font_scale=1)
sys.path.insert(0, '/Users/erezcohen/larlite/UserDev/CLASEG2DataMining/EG2DataMiningPackage/mac')
import matplotlib.patches as patches
from matplotlib.lines import Line2D
from mpl_toolkits.mplot3d import Axes3D
from scipy.interpolate import interp1d, Akima1DInterpolator,BarycentricInterpolator,splprep
from plot_tools import *
from my_tools import *
from calc_tools import *
from root_numpy import tree2array, root2array
from root_pandas import read_root
from scipy.optimize import curve_fit
from matplotlib.ticker import NullFormatter,MultipleLocator, FormatStrFormatter
from matplotlib.offsetbox import AnchoredText
from scipy.signal import savgol_filter
from scipy.stats import norm
from scipy import stats

