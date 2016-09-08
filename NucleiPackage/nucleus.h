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

    Int_t       A;
    
    Float_t     mass;
    
    TVector3    position;
    
    TString     ShortName , Name , label;
    
    std::vector<nucleon> nucleons;
};

#endif
/** @} */ // end of doxygen group 

