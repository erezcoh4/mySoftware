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
def set_float_precision(a,precision): #{
    exponent = np.power(10,precision)
    return np.ceil(a*exponent)/exponent
#}
# ------------------------------------------------------------------------------- #


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
#    if (v2-v2Err > v1 or v2+v2Err > v1):
#        xmin , xmax = v2-v2Err , infty
#    elif (v2+v2Err > v1):
#        xmin , xmax = v2+v2Err , infty
#    elif (v2+v2Err < v1):
#        xmin , xmax = -infty , v2+v2Err
#    else:
#        if debug>3: print 'Pval2varsAssumeGausDist on ',name,' v1:',v1,' and v2:',v2,' - not sure how to integrate...'
#        exit(0)
    if v2>v1:
        xmin , xmax = v2-v2Err , infty
    else:
        xmin , xmax = -infty , v2+v2Err

    integral , integral_err = GaussianIntegral( xmin , xmax , args=(v1,v1Err) )

#    if v2 - v2Err > v1:
#        integral_r , integral_r_err = GaussianIntegral( v2-v2Err , infty , args=(v1,v1Err) )
#        integral_l , integral_l_err = GaussianIntegral( -infty , v2+v2Err , args=(v1,v1Err) )
#
    if debug>3:
        print 'Pval(%s) comparing %f+/-%f and %f+/-%f'%(name,v1 , v1Err , v2 , v2Err)
        print "Pval = integral (",xmin,"to",xmax,") = ", integral
    return integral


# ------------------------------------------------------------------------------- #
def Pval2varsAssumeGausDist_pandas( v1 , v1Err , v2 , v2Err , debug=0 , name=''):
    '''
        assume v1 was sampled from a Gaussian distribution of mean v1 and width v1Err
        and ask what is the probability of v2 to be sampled from the same distribution:
        the answer is the integral of the v1,v1Err Gaussian in the range [v2 , infty].
        In order to account for v2Err, we ask how v2Err influences v2' vicinity to v1' mean
        if v2-v2Err > v1, take the integral in the range [v2-v2Err , infty]
        else, if v2+v2Err > v1, take the integral in the range [v2+v2Err , infty]
        else, v2+v2Err < v1, take the integral in the range [-infty , v2+v2Err]
        '''
    xmin , xmax = v2-v2Err , infty
    
    integral , integral_err = GaussianIntegral( xmin , xmax , args=(v1,v1Err) )
    return integral





# ------------------------------------------------------------------------------- #
# p(val) combination - Fisher method
# [https://en.wikipedia.org/wiki/Fisher's_method]
def FisherMethodPvals(pvalues_array):
    # (adopted from a code by Arie Shaus, Nov 2016)
    pvalues_array = np.array(pvalues_array)
    k = len(pvalues_array)
    z = -2*sum(np.log(pvalues_array))
    combined_Pval = chisqprob(z,2*k)
    return combined_Pval



# ------------------------------------------------------------------------------- #
# p(val) combination - only large Pvals
def FisherCombinationLargePvals(pvalues_array):
    
    if not pvalues_array: return 1.0
    
    Pval_arr = []
    for pval in pvalues_array:
        if pval > 1e-8:
            Pval_arr.append(pval)

    # check if pvalues are too small
    return FisherMethodPvals(Pval_arr)


# ------------------------------------------------------------------------------- #
def Fisher_combination_Pvals(pvalues_array):
    pvalues_array = np.array(pvalues_array)
    z=0
    for pval in pvalues_array:
        if pval > 1.e-20:
            z += -2*np.log(pval)
        else:
            z += -2*np.log(1.e-20)
    k = len(pvalues_array)
    combined_Pval = chisqprob(z,2*k)
    return combined_Pval
#
#    if not pvalues_array:
#        return 1.0
#
#    Pval_arr , NPval0 = [] , 0
#    for pval in pvalues_array:
#        if pval > 1e-8:
#            Pval_arr.append(pval)
#        else:
#            NPval0 = NPval0+1
#
#    if NPval0>1:
#        return 0.0
#
#    # check if pvalues are too small
#    return FisherMethodPvals(Pval_arr)



# ------------------------------------------------------------------------------- #
def Fisher_combination_Pvals_pandas(pvalues_array):
    if not pvalues_array: return 1.0
    return FisherMethodPvals(pvalues_array)





        
        
        
        
        
        
        
        

