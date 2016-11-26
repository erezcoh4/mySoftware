from my_tools import *
from math import sqrt , exp
import scipy.integrate as integrate
import numpy as np
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
def Pval2varsAssumeGausDist( v1 , v1Err , v2 , v2Err , debug=0):
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
        print 'not sure how to integrate...'
        exit(0)

    integral , integral_err = GaussianIntegral( xmin , xmax , args=(v1,v1Err) )
    if (debug>1): print "comparing %f+/-%f and %f+/-%f - got Pval=%f"%(v1 , v1Err , v2 , v2Err , integral)
    return integral





        
        
        
        
        
        
        
        
        
        

