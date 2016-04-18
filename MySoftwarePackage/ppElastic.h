/**
 * \file ppElastic.h
 *
 * \ingroup MySoftwarePackage
 * 
 * \brief Class def header for a class ppElastic
 *
 * @author erezcohen
 */

/** \addtogroup MySoftwarePackage

    @{*/
#ifndef PPELASTIC_H
#define PPELASTIC_H

#include <iostream>
#include "TPlots.h"
#include <math.h>

/**
   \class ppElastic
   User defined class ppElastic ... these comments are used to generate
   doxygen documentation!
 */
class ppElastic{

public:

    
    
    TRandom3 r;
    TPlots plot;
    vector<Double_t> pars;
    Double_t factor;
    TF1     *alpha[8] , *XsecTheta[6];
    TF1     *fTheta;
    TF2     *Xsec;
    TH2F    *XsecHist;
    TF12    *f12;
    
    
    
    /// Default constructor
    ppElastic(){};
    ~ppElastic(){};
    

    
    // cross-section for p-p elastic scattering in c.m. frame
    // following GSI ppElastic analysis [http://web-docs.gsi.de/~webhades/computing/pluto/NN/pp_elastic.html#ref*]
    void        CreateAlphas ();
    TCanvas *     DrawAlphas ();
    void          CreateXsec ();
    TCanvas *       DrawXsec ();
    Double_t             pol ( vector<Double_t> par , Double_t x );
    
    
    Double_t a0 (Double_t);
    Double_t a1 (Double_t);
    Double_t a2 (Double_t);
    Double_t a3 (Double_t);
    Double_t a4 (Double_t);
    Double_t a5 (Double_t);
    Double_t a6 (Double_t);
    Double_t a7 (Double_t);
    
    Double_t g_p (Double_t , Double_t);
    Double_t g_q (Double_t , Double_t);
    Double_t g_W (Double_t , Double_t);
    Double_t g_v (Double_t , Double_t);
    Double_t f_Theta_cm (Double_t , Double_t);
    
    
    Double_t RandomTheta (Double_t);


};

#endif
/** @} */ // end of doxygen group 

