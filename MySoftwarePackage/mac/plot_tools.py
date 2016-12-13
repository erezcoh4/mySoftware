import sys, pandas as pd, numpy as np
import matplotlib.pyplot as plt
import ROOT
import matplotlib as mpl , seaborn as sns; sns.set(style="white", color_codes=True , font_scale=1)
import GeneralPlot as gp , Initiation as init 
from math import sqrt , exp
generic = lambda x: ast.literal_eval(x)



# --------------------------------
def set_axes(ax , xlabel , ylabel , fontsize=25):
    ax.set_xlabel(xlabel,fontsize=fontsize)
    ax.set_ylabel(ylabel,fontsize=fontsize)
    for tick in ax.xaxis.get_major_ticks():
        tick.label.set_fontsize(fontsize)
    for tick in ax.yaxis.get_major_ticks():
        tick.label.set_fontsize(fontsize)

# --------------------------------
def plot_1d_hist( x , bins=50 , histtype='bar', xlabel='' , ylabel='' , figsize=(10,10) , fontsize=25 , weights=None):
    fig,ax = plt.subplots(figsize=figsize)
    h , bins , patches = plt.hist( x , bins=bins , histtype=histtype , weights=weights)
    set_axes( ax , xlabel , ylabel , fontsize=fontsize )
    return h , bins , patches

# --------------------------------
def plot_2d_hist( x , y , bins=(50,50) , cmap='hot_r', xlabel='' , ylabel='' , figsize=(10,10) , fontsize=25 , weights=None)):
    fig,ax = plt.subplots( figsize=figsize )
    counts, xedges, yedges, Image = plt.hist2d( x , y , bins=bins , cmap=cmap , weights=weights)
    set_axes( ax , xlabel , ylabel , fontsize=fontsize )
    return counts, xedges, yedges, Image



# --------------------------------
def plot_distplot( x , bins , label , x_label ,  xmin , xmax ,
                  DoSetLogY = False):
    g = sns.distplot( x , bins=bins, kde=False , label=label)
    g.set_xlabel(x_label,fontsize=25)
    if DoSetLogY:g.set( yscale="log" )



# --------------------------------
def plot_hist2d_ppp( var_x , xmin , xmax , nbinsx , x_label , var_y, ymin , ymax , nbinsy , y_label ):
    
    binsx = np.linspace(xmin,xmax,nbinsx)
    binsy = np.linspace(ymin,ymax,nbinsy)
    fig = plt.figure(figsize = [10,8])
    ax = plt.subplot(111)
    plt.scatter(all_events[var_x], all_events[var_y] , color='blue')
    plt.scatter(all_ppp[var_x], all_ppp[var_y] , color='green')
    plt.scatter(ppp_src[var_x], ppp_src[var_y] , color='red')
    ax.set_xlim(xmin,xmax)
    ax.set_ylim(ymin,ymax)
    ax.set_xlabel(x_label,fontsize=25)
    ax.set_ylabel(y_label,fontsize=25)
    for tick in ax.xaxis.get_major_ticks():
        tick.label.set_fontsize(25)
    for tick in ax.yaxis.get_major_ticks():
        tick.label.set_fontsize(25)

    plt.show()
    fig.savefig( dirname + "/ppp_" + var_x + "_vs_" + var_y + ".png" )

# --------------------------------
def plot_col2d( var_x , xmin , xmax , nbinsx , x_label , var_y, ymin , ymax , nbinsy , y_label , ana ):
    fig = plt.figure(figsize=[10,5])
    fig, ax = plt.subplots(1,1, figsize=(10,10), subplot_kw={'aspect':'equal'})
    h = ana.H2( var_x , var_y ,ROOT.TCut(),'',nbinsx,xmin,xmax,nbinsy,ymin,ymax)
    H = np.ones((nbinsx,nbinsy))
    for bin_x in range(nbinsx):
        for bin_y in range(nbinsy):
            H[bin_x][bin_y]= float(h.GetBinContent(bin_x,bin_y))
    extent = [xmin,xmax,ymin,ymax]
    im = plt.imshow(H,interpolation='none', cmap='CMRmap_r',origin='lower', extent=extent)
    im = ax.imshow(np.ma.masked_where(H==0, H), cmap='CMRmap_r', interpolation='none', origin='lower', extent=extent)
    ax.set_xlabel(x_label,fontsize=25)
    ax.set_ylabel(y_label,fontsize=25)
    for tick in ax.xaxis.get_major_ticks():
        tick.label.set_fontsize(25)
    for tick in ax.yaxis.get_major_ticks():
        tick.label.set_fontsize(25)
    ax.set_aspect('auto')
    cb = plt.colorbar()
    for t in cb.ax.get_yticklabels():
        t.set_fontsize(20)
    fig.savefig( dirname + "/ppp_" + var_x + "_vs_" + var_y + ".png" )

