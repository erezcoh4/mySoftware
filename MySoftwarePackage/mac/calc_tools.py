# imports...
import scipy.integrate as integrate
import numpy as np
from my_tools import *
from math import sqrt , exp
from scipy.stats import chisqprob

# globals
sqrt2pi = sqrt(2*3.1415)
infty = np.inf


# ------------------------------------------------------------------------------- #
def Gaussian( x , mean , sigma ):
    power = -0.5*((x - mean)*(x - mean))/(sigma*sigma)
    return (1/(sigma*sqrt2pi))*(exp(power))



# ------------------------------------------------------------------------------- #
def GaussianIntegral( xmin , xmax , args=(0,1)):
    return integrate.quad( Gaussian, xmin , xmax, args=args )


# ------------------------------------------------------------------------------- #
def Pval2varsAssumeGausDist( v1 , v1Err , v2 , v2Err , debug=0 , name=''):
    '''
        assume v1 was sampled from a Gaussian distribution of mean v1 and width v1Err
        and ask what is the probability of v2 to be sampled from the same distribution:
        the answer is the integral of the v1,v1Err Gaussian in the range [v2 , infty].
        In order to account for v2Err, we ask how v2Err influences v2' vicinity to v1' mean
        if v2-v2Err > v1, take the integral in the range [v2-v2Err , infty]
        else, if v2+v2Err > v1, take the integral in the range [v2+v2Err , infty]
        else, v2+v2Err < v1, take the integral in the range [-infty , v2+v2Err]
    '''
    if (v2-v2Err > v1):
        xmin , xmax = v2-v2Err , infty
    elif (v2+v2Err > v1):
        xmin , xmax = v2+v2Err , infty
    elif (v2+v2Err < v1):
        xmin , xmax = -infty , v2+v2Err
    else:
        if debug>3: print 'Pval2varsAssumeGausDist on ',name,' v1:',v1,' and v2:',v2,' - not sure how to integrate...'
        exit(0)

    integral , integral_err = GaussianIntegral( xmin , xmax , args=(v1,v1Err) )
    if (debug>3): print "Pval(%s) comparing %f+/-%f and %f+/-%f - got Pval=%f"%(name,v1 , v1Err , v2 , v2Err , integral)
    return integral




# ------------------------------------------------------------------------------- #
# p(val) combination - Fisher method [https://en.wikipedia.org/wiki/Fisher's_method]
# (adopted from a code by Arie Shaus, Nov 2016)
def Fisher_combination_Pvals(pvalues_array):

    if not pvalues_array:
        return 1.0

# I want to remove it and check if its ok (used to make a lot of problems in Fe56 and Al27 so I am not sure its a wise thing to do?)....
#    Pval_arr = np.array(pvalues_array)

    Pval_arr , NPval0 = [] , 0
    for pval in pvalues_array:
        if pval > 1e-8:
            Pval_arr.append(pval)
        else:
            NPval0 = NPval0+1

    if NPval0>(len(pvalues_array)-3):
        return 0.0
    Pval_arr = np.array(Pval_arr)


    # check if pvalues are too small
    k = len(Pval_arr)
    z = -2*sum(np.log(Pval_arr))
    combined_Pval = chisqprob(z,2*k)
    return combined_Pval



# ------------------------------------------------------------------------------- #
def Fisher_combination_Pvals_pandas(pvalues_array):
    if not pvalues_array:
        return 1.0
    pvalues_array = np.array(pvalues_array)
    # check if pvalues are too small
    k = len(pvalues_array)
    z = -2*sum(np.log(pvalues_array))
    combined_Pval = chisqprob(z,2*k)
    return combined_Pval





        
        
        
        
        
        
        
        

