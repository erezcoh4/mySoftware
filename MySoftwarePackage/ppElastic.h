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
#include <TPlots.h>
#include <math.h>

/**
   \class ppElastic
   User defined class ppElastic ... these comments are used to generate
   doxygen documentation!
 */
class ppElastic{

public:

    
    
    TPlots plot;
    vector<Double_t> pars;
    Double_t factor;
    
    
    
  /// Default constructor
    ppElastic();

  /// Default destructor
    ~ppElastic(){};
    
    
    
    // cross-section for p-p elastic scattering in c.m. frame
    // following GSI ppElastic analysis [http://web-docs.gsi.de/~webhades/computing/pluto/NN/pp_elastic.html#ref*]

    
    Double_t pol ( vector<Double_t> par , Double_t x );
    
    
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
    
//    void    Set_ppElastic ();


};

#endif
/** @} */ // end of doxygen group 

