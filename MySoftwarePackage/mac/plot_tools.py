import sys, pandas as pd, numpy as np, ast
import matplotlib.pyplot as plt
from scipy.stats import norm
import matplotlib.mlab as mlab
#import ROOT
import matplotlib as mpl , seaborn as sns; sns.set(style="white", color_codes=True , font_scale=1)
#import GeneralPlot as gp , Initiation as init 
from math import sqrt , exp
from my_tools import *
from matplotlib.colors import LogNorm
generic = lambda x: ast.literal_eval(x)


# --------------------------------
def hist_with_errors( x , bins=30 ,
                     x_label=None , figsize=(16,10), label=None, ticks_color='black'):

    ax , h , bins , patches = plot_1d_hist( x , bins=bins , xlabel=x_label , figsize=figsize, ticks_color=ticks_color);
    mid = 0.5*(bins[1:] + bins[:-1])
    ax.bar( mid , h, yerr=np.sqrt(h), linewidth=0,error_kw=dict(ecolor='black', lw=2, capsize=5, capthick=2),label=label)
    ax.set_ylim(0,1.02*np.max(h+np.sqrt(h)))
    return ax , h , bins , mid

# --------------------------------
def normed_hist( x , bins=50 , weights=None ,
                label = None,
                histtype='bar',alpha = 0.5):
    h , edges = np.histogram( x , bins=bins , weights=weights );
    integral = sum(h)
    if weights is None:
        integral_weights = [1./integral for i in range(len(x))]
    else:
        integral_weights = [weights[i]/integral for i in range(len(x))]
    print "integral:",integral
    h , bins , patches = plt.hist( x , bins=bins , histtype=histtype ,
                                  weights = integral_weights,
                                  label=label , alpha=alpha );
    return h , bins , patches


# --------------------------------
def plot_1d_hist( x , bins=50 ,
                 histtype='bar', xlabel='' , ylabel='' ,
                 figsize=(10,10) , fontsize=25 , weights=None , label=None ,
                 normed=None , ticks_color='black'):
    fig,ax = plt.subplots(figsize=figsize)
    h , bins , patches = plt.hist( x , bins=bins , histtype=histtype , weights=weights , label=label , normed=normed );
    set_axes( ax , xlabel , ylabel , fontsize=fontsize , ticks_color=ticks_color)
    ax.set_ylim(0,1.05*h.max())
    return ax , h , bins , patches



# --------------------------------
def plot_1d_withoutandwithweight( x, weights, weighting_labels,
                                 bins = 50 , histtype='bar', xlabel='', ylabel='', figsize=(10,10) , fontsize=25,
                                 alpha = 0.5,legend_loc='upper left',
                                 x_range=None , y_range=None):
    fig,ax = plt.subplots(figsize=figsize)
    vars = [x for i in range(len(weights))]
    histograms, bins, patches = plt.hist( vars, bins=bins, weights=weights, label=weighting_labels , histtype='bar' , normed=1)
    set_axes( ax , xlabel , ylabel , fontsize=fontsize )
    if x_range is not None:
        ax.set_xlim(x_range)
    if y_range is not None:
        ax.set_ylim(y_range)
    if legend_loc!='none':
        if legend_loc=='bbox':
            plt.legend(bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0. , fontsize=fontsize)
        else:
            plt.legend(fontsize=fontsize,loc=legend_loc)
    return histograms , bins


# --------------------------------
def plot_2d_hist( x , y , bins=(50,50) , cmap='hot_r', xlabel='' , ylabel='' , figsize=(10,10) , fontsize=25 , weights=None, ticks_color='black', norm='log',ax=None):
    
    if ax is None:
        fig,ax = plt.subplots( figsize=figsize )
    
    if 'log' not in norm and 'Log' not in norm:
        counts, xedges, yedges, Image = plt.hist2d( x , y , bins=bins , cmap=cmap , weights=weights);
    else:
        counts, xedges, yedges, Image = plt.hist2d( x , y , bins=bins , cmap=cmap , weights=weights, norm=LogNorm());
    set_axes( ax , xlabel , ylabel , fontsize=fontsize, ticks_color=ticks_color )

    return counts, xedges, yedges, Image, ax




# --------------------------------
def acceptace_1d( xgen , xrec , x_label='momentum [GeV/c]',
                 bins=np.linspace(0,2,30) ,
                 figsize=(10,10),fontsize=20,
                 legend_loc='lower left',
                 y_label='reconstructed fraction',
                 y_lim=None,
                 do_print=False):
    
    x = [bins[i] for i in range(len(bins)-1)]
    if do_print: print 'x:',x
    fig = plt.figure(figsize=figsize)
    ax=fig.add_subplot(211)
    h_gen,edges=np.histogram(xgen,bins=bins)
    h_gen_err = np.sqrt(h_gen)
    h_rec,edges=np.histogram(xrec,bins=bins)
    h_rec_err = np.sqrt(h_rec)
    plt.errorbar(x, h_gen, yerr=h_gen_err, fmt='o',markersize=4,label='generated')
    plt.errorbar(x, h_rec, yerr=h_rec_err, fmt='s',markersize=4,label='reconstructed')
    if do_print:
        print 'h_gen:\n',h_gen
        print 'h_rec:\n',h_rec

    plt.legend(fontsize=fontsize,loc=legend_loc)
    set_axes(ax,'','')
    acceptance = [float(h_rec[i])/h_gen[i] if h_gen[i]>0 else 0 for i in range(len(h_gen))]
    acceptance_err = [sqrt(1./h_rec[i]+1./h_gen[i]) if h_gen[i]>50 and h_rec[i]>50 else 0 for i in range(len(h_gen))]
    
    ax=fig.add_subplot(212)
    plt.errorbar(x, acceptance, yerr=acceptance_err, fmt='o')
    plt.plot(x,acceptance,color='r',marker='s')
    if do_print:
        print 'acceptance:\n',acceptance

    if y_lim is None:
        ax.set_ylim(0,np.max([1.,1.2*np.max(acceptance+acceptance_err)]))
    else:
        ax.set_ylim(y_lim)
    set_axes(ax,x_label,y_label)
    return x , acceptance



# --------------------------------
def plot_distplot( x , bins , label , x_label ,  xmin , xmax ,
                  DoSetLogY = False):
    g = sns.distplot( x , bins=bins, kde=False , label=label)
    g.set_xlabel(x_label,fontsize=25)
    if DoSetLogY:g.set( yscale="log" )



