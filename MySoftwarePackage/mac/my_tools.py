import os
from scipy.integrate import quad

# prints
def print_line():
    print '\033[92m' + '--------------------------------------------------------------' + '\033[0m'

def print_important(string):
    print '\033[94m' + '\033[1m' + string + '\033[0m' ; print_line

def print_filename(filename,action_on_file=""):
    print action_on_file + '\n' + '\033[91m' + filename + '\033[0m'



# ------------------------------------------------------------------------------- #
def stream_dataframe_to_file( df , filename ):
    # if file does not exist write header
    if not os.path.isfile(filename):
        df.to_csv(filename,header ='column_names' , index = False)
    else: # else it exists so append without writing the header
        df.to_csv(filename,mode = 'a', header=False , index = False)



# ------------------------------------------------------------------------------- #
def set_axes(ax , x_label , y_label , fontsize = 25 ):
    ax.set_xlabel(x_label,fontsize=fontsize)
    ax.set_ylabel(y_label,fontsize=fontsize)
    for tick in ax.xaxis.get_major_ticks():
        tick.label.set_fontsize(fontsize)
    for tick in ax.yaxis.get_major_ticks():
        tick.label.set_fontsize(fontsize)
    ax.set_aspect('auto')
    return ax


def Gaussian( x , mean , sigma ):
    return x**2


# ------------------------------------------------------------------------------- #
def Pval2varsAssumeGausDist( v1 , v1Err , v2 , v2Err):
    '''
        assume v1 was sampled from a Gaussian distribution of mean v1 and width v1Err
        and ask what is the probability of v2 to be sampled from the same distribution:
        the answer is the integral of the v1,v1Err Gaussian in the range [v2 , infty].
        In order to account for v2Err, we ask how v2Err influences v2' vicinity to v1' mean
        if v2-v2Err > v1, take the integral in the range [v2-v2Err , infty]
        else, if v2+v2Err > v1, take the integral in the range [v2+v2Err , infty]
        else, v2+v2Err < v1, take the integral in the range [-infty , v2+v2Err]
        
    '''
    if v2-v2Err > v1:
        xmin , xmax = v2-v2Err , infty
    elif v2+v2Err > v1:
        xmin , xmax = v2+v2Err , infty
    elif v2+v2Err < v1:
        xmin , xmax = -infty , v2+v2Err
    else:
        print 'not sure how to integrate...'
        exit(0)

    quad( integrand, xmin , xmax, args=(a,b))





        
        
        
        
        
        
        
        
        
        

