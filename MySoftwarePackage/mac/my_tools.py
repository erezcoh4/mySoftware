import os , gc

# prints
def print_line():
    print '\033[92m' + '--------------------------------------------------------------' + '\033[0m'

def print_xline():
    print '\033[96m' + 'xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx' + '\033[0m'

def print_important(string):
    print '\033[94m' + '\033[1m' + string + '\033[0m' ; print_line

def print_filename(filename,action_on_file=""):
    print action_on_file + '\n' + '\033[91m' + filename + '\033[0m'



# ------------------------------------------------------------------------------- #
# Feb-23,2017
def delete_file(filename,debug=0):
    # if file does not existreturn
    if not os.path.isfile(filename):
        if debug: print filename,"does not exist, there is nothing to delete"
    else:
        os.remove( filename )
        if debug: print "removed",filename
# ------------------------------------------------------------------------------- #


# ------------------------------------------------------------------------------- #
def filesize_in_MB(filename):
    return float(os.path.getsize(filename)/1048576.0)
# ------------------------------------------------------------------------------- #





# ------------------------------------------------------------------------------- #
def stream_dataframe_to_file( df , filename , float_format='%g' ):
    df.fillna(0, inplace=True)
    # if file does not exist write header
    if not os.path.isfile(filename):
        df.to_csv( filename, header ='column_names' , index = False , float_format=float_format )
    else: # else it exists so append without writing the header
        df.to_csv( filename, mode = 'a', header=False , index = False , float_format=float_format )

    del [ df ]
    gc.collect()
# ------------------------------------------------------------------------------- #




# ------------------------------------------------------------------------------- #
def set_axes(ax , x_label , y_label='' , fontsize = 25 , ticks_color='black' , nticklabels=4
             , xticks=None, yticks=None, xlim=None, ylim=None
             , do_add_grid=False, alpha_grid=0.75
             , title=None
             , do_add_legend=False, legend_loc='best'
             , z_label=None , zticks=None
             , remove_ticks_x=False, remove_ticks_y=False):
    
    ax.set_xlabel(x_label,fontsize=fontsize)
    ax.set_ylabel(y_label,fontsize=fontsize)
    for tick in ax.xaxis.get_major_ticks():
        tick.label.set_fontsize(fontsize)
    for tick in ax.yaxis.get_major_ticks():
        tick.label.set_fontsize(fontsize)
    ax.set_aspect('auto')
    ax.tick_params(axis='x', colors=ticks_color)
    ax.xaxis.label.set_color(ticks_color)
    ax.tick_params(axis='y', colors=ticks_color)
    ax.yaxis.label.set_color(ticks_color)
#    ax.xaxis.set_major_locator(LinearLocator(nticklabels));ax.yaxis.set_major_locator(LinearLocator(nticklabels))
    if xticks is not None:
        ax.xaxis.set_ticks(xticks)
    if yticks is not None:
        ax.yaxis.set_ticks(yticks)
    if do_add_grid:
        ax.grid(linestyle='--',alpha=alpha_grid)
    if title is not None:
        ax.set_title(title,y=1.02,fontsize=fontsize)
    if z_label is not None: #{
        ax.set_zlabel(z_label,fontsize=fontsize)
        for tick in ax.zaxis.get_major_ticks(): tick.label.set_fontsize(fontsize)
    if zticks is not None: ax.zaxis.set_ticks(zticks)
    #}
    if xlim is not None: ax.set_xlim(xlim)
    if ylim is not None: ax.set_ylim(ylim)
    if do_add_legend==True:#{
        ax.legend(loc=legend_loc,fontsize=fontsize)
    #}
    if remove_ticks_x:
        from matplotlib.ticker import NullFormatter
        ax.get_xaxis().set_major_formatter(NullFormatter())
    if remove_ticks_y:
        from matplotlib.ticker import NullFormatter
        ax.get_yaxis().set_major_formatter(NullFormatter())
    return ax





        
        
        
        
        
        
        
        
        

