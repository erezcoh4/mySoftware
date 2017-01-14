import os

# prints
def print_line():
    print '\033[92m' + '--------------------------------------------------------------' + '\033[0m'

def print_important(string):
    print '\033[94m' + '\033[1m' + string + '\033[0m' ; print_line

def print_filename(filename,action_on_file=""):
    print action_on_file + '\n' + '\033[91m' + filename + '\033[0m'



# ------------------------------------------------------------------------------- #
def stream_dataframe_to_file( df , filename , float_format='%g' ):
    # if file does not exist write header
    if not os.path.isfile(filename):
        df.to_csv(filename,header ='column_names' , index = False , float_format=float_format )
    else: # else it exists so append without writing the header
        df.to_csv(filename,mode = 'a', header=False , index = False , float_format=float_format )



# ------------------------------------------------------------------------------- #
def set_axes(ax , x_label , y_label='' , fontsize = 25 , ticks_color='black'):
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

    return ax





        
        
        
        
        
        
        
        
        

