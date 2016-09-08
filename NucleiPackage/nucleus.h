/**
 * \file nucleus.h
 *
 * \ingroup NucleiPackage
 * 
 * \brief Class def header for a class nucleus
 *
 * @author erezcohen
 */

/** \addtogroup NucleiPackage

    @{*/
#ifndef NUCLEUS_H
#define NUCLEUS_H
#include "nucleon.h"

#include <iostream>

/**
   \class nucleus
   User defined class nucleus ... these comments are used to generate
   doxygen documentation!
 */
class nucleus{

public:

    /// Default constructor
    nucleus( TString fShortName , Int_t fA );
    ~nucleus(){}
    
    
    void          Print ();
    void     AddNucleon ( nucleon N );
    void  ClearNucleons ();
    
    
    // Getters
    Int_t       GetNpairs () {return (nucleons.size())*(nucleons.size()-1);};
    Int_t     GetNppPairs () {return (protons.size())*(protons.size()-1);};
    Int_t     GetNnnPairs () {return (neutrons.size())*(neutrons.size()-1);};
    Int_t     GetNpnPairs () {return protons.size()*neutrons.size();};
    
    
    
    Int_t       A;
    
    Float_t     mass;
    
    TVector3    position;
    
    TString     ShortName , Name , label;
    
    std::vector<nucleon> protons , neutrons , nucleons;
};

#endif
/** @} */ // end of doxygen group 

