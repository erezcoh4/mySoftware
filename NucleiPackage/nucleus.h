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
    nucleus(){};
    nucleus( TString fShortName , Int_t fA );
    ~nucleus(){}
    
    
    void              Print ();
    void    PrintNoNucleons ();
    void         AddNucleon ( nucleon N );
    void      ClearNucleons ();
    void    CalcNNDistances ( Int_t debug = 0 );
    
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
    
    
    std::vector<Float_t> ppDistances , nnDistances , pnDistances , NNDistances;

    
    // service...
    std::vector<Float_t> GetDistancesBetweenNucleons(std::vector<nucleon> );
    std::vector<Float_t> GetDistancesBetweenNucleons(std::vector<nucleon>,std::vector<nucleon> );

};

#endif
/** @} */ // end of doxygen group 

